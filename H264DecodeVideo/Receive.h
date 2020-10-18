#ifndef	RECEIVE_H_
#define RECEIVE_H_

#include <string>
#include <WinSock.h>

using namespace std;
class Receive
{
public:
	Receive(void);
public:
	~Receive(void);

public:
	//��ʼ��socket
	bool InitSocket(const string strIPAddress, const string strPort);

	//����string����
	bool ReceiveStringData(char* strMessage);

	//���ܽṹ������
	bool ReceiveStructeData();

	//�ر�socket
	void CloseSocket();

private:
	SOCKET m_socket; //socket;
	sockaddr_in m_sockLocalAddress;
	sockaddr_in m_sockReceiveAddress;
};

#endif  //RECEIVE_H_