/*******************************************************
* @����: �ƾ���
* @Date: 2020-10-08 02:04:58
* @LastEditTime: 2020-10-08 03:17:28
* @����д��: �ƾ���
* @����: �������������������ݻ�ȡͨ�������ݽ�����ʹ��˫�˶���ʵ�ֻ���
* @FilePath: /Harb_Device/device/src/Deque_Buffer.cpp
* @���۱�ע:
*******************************************************/
#include "Deque_Buffer.h"
#include "DataChain.h"

// ��ȡ��ѹ�����ݺ� ����popFront_FromdequeBuffEmpty������һ���洢���飬����������ݺ�pushBackTo_dequeBuffUse
// ����ʱ��ѭ������popFront_FromdequeBuffUse����Ϊ�ǿ�ʱ�������ݷ��ͳ�ȥ������������ָ��pushBackTo_dequeBuffEmpty
// ��ע��Ҳ�����ȵ������ٷ��ͣ���Ϊָ�벻�䣬����֮��ֻҪ����û�б��ϳ����Ͳ���������ݸ��ǣ�
// ��ǰ����Ϊ256������ѭ�������Դ洢60K���ҵ�ͼ�񻺴棬��Լ����10֡���ϵĻ�������
/*******************************************************
* ����:    DequeBuffObject
* ������:  DequeBuffObject
* ��������
* ���ܣ�   DequeBuffObject���캯��
* ��ע��
*******************************************************/


/*******************************************************
* ����:    DequeBuffObject
* ������:  popFrontFrom_dequeBuffEmpty
* ��������
* ���ܣ�   ������buff�����׸���Ԫ
* ��ע��
*******************************************************/
uint8_t *Deque_Buffer::popFrontFrom_dequeBuffEmpty()
{
	std::lock_guard<std::mutex> lg(dequeBuffEmptyMutex);
	//QMutexLocker locker(&dequeBuffEmptyMutex);
	if (dequeBuffEmpty.empty())
	{
		return NULL;
	}
	uint8_t *data = dequeBuffEmpty.front();
	dequeBuffEmpty.pop_front();
	return data;
}

/*******************************************************
* ����:    DequeBuffObject
* ������:  pushBackTo_dequeBuffEmpty
* �������� uint8_t *a                  uint8_t����ָ��
* ���ܣ�   ��һ����Ԫѹ���buff����
* ��ע��
*******************************************************/
void Deque_Buffer::pushBackTo_dequeBuffEmpty(uint8_t *a)
{
	std::lock_guard<std::mutex> lg(dequeBuffEmptyMutex);
	//QMutexLocker locker(&dequeBuffEmptyMutex);
	dequeBuffEmpty.push_back(a);
}

/*******************************************************
* ����:    DequeBuffObject
* ������:  popFrontFrom_dequeBuffUse
* ��������
* ���ܣ�   ����ʹ�õ�buff�����׸���Ԫ
* ��ע��
*******************************************************/
uint8_t *Deque_Buffer::popFrontFrom_dequeBuffUse()
{
	std::lock_guard<std::mutex> lg(dequeBuffUseMutex);
	//QMutexLocker locker(&dequeBuffUseMutex);
	if (dequeBuffUse.empty())
	{
		return NULL;
	}
	uint8_t *data = dequeBuffUse.front();
	dequeBuffUse.pop_front();
	return data;
}

/*******************************************************
* ����:    DequeBuffObject
* ������:  pushBackTo_dequeBuffUse
* �������� uint8_t *a                  uint8_t����ָ��
* ���ܣ�   ��һ����Ԫѹ��ʹ�õ�buff����
* ��ע��
*******************************************************/
void Deque_Buffer::pushBackTo_dequeBuffUse(uint8_t *a)
{
	std::lock_guard<std::mutex> lg(dequeBuffUseMutex);
	//QMutexLocker locker(&dequeBuffUseMutex);
	dequeBuffUse.push_back(a);
}
void Deque_Buffer::Init_buffer()
{
	for (int i = 0; i < MAXCHAINDEQUESIZE; i++)
	{
		// ���뵥֡�ֽڳ��ȵ�����
		uint8_t *pDataa = new uint8_t[sizeof(DataChainCommonType)];
		pushBackTo_dequeBuffEmpty(pDataa);
	}
}