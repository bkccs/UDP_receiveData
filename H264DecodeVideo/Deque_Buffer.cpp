/*******************************************************
* @作者: 黄竞辉
* @Date: 2020-10-08 02:04:58
* @LastEditTime: 2020-10-08 03:17:28
* @最后编写者: 黄竞辉
* @描述: 用于数据链传输与数据获取通道的数据交换，使用双端队列实现缓冲
* @FilePath: /Harb_Device/device/src/Deque_Buffer.cpp
* @评论备注:
*******************************************************/
#include "Deque_Buffer.h"
#include "DataChain.h"

// 获取到压缩数据后 首先popFront_FromdequeBuffEmpty，弹出一个存储数组，填好数组内容后pushBackTo_dequeBuffUse
// 发送时，循环访问popFront_FromdequeBuffUse，当为非空时，将数据发送出去，并将弹出的指针pushBackTo_dequeBuffEmpty
// （注意也可以先弹出，再发送，因为指针不变，弹出之后只要队列没有被赶超，就不会出现数据覆盖）
// 当前设置为256个数组循环，可以存储60K左右的图像缓存，大约会有10帧以上的缓冲区域
/*******************************************************
* 类名:    DequeBuffObject
* 函数名:  DequeBuffObject
* 变量名：
* 功能：   DequeBuffObject构造函数
* 备注：
*******************************************************/


/*******************************************************
* 类名:    DequeBuffObject
* 函数名:  popFrontFrom_dequeBuffEmpty
* 变量名：
* 功能：   弹出空buff队列首个单元
* 备注：
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
* 类名:    DequeBuffObject
* 函数名:  pushBackTo_dequeBuffEmpty
* 变量名： uint8_t *a                  uint8_t类型指针
* 功能：   将一个单元压入空buff队列
* 备注：
*******************************************************/
void Deque_Buffer::pushBackTo_dequeBuffEmpty(uint8_t *a)
{
	std::lock_guard<std::mutex> lg(dequeBuffEmptyMutex);
	//QMutexLocker locker(&dequeBuffEmptyMutex);
	dequeBuffEmpty.push_back(a);
}

/*******************************************************
* 类名:    DequeBuffObject
* 函数名:  popFrontFrom_dequeBuffUse
* 变量名：
* 功能：   弹出使用的buff队列首个单元
* 备注：
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
* 类名:    DequeBuffObject
* 函数名:  pushBackTo_dequeBuffUse
* 变量名： uint8_t *a                  uint8_t类型指针
* 功能：   将一个单元压入使用的buff队列
* 备注：
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
		// 申请单帧字节长度的数组
		uint8_t *pDataa = new uint8_t[sizeof(DataChainCommonType)];
		pushBackTo_dequeBuffEmpty(pDataa);
	}
}