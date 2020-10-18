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
	//初始化socket
	bool InitSocket(const string strIPAddress, const string strPort);

	//接受string数据
	bool ReceiveStringData(char* strMessage);

	//接受结构体数据
	bool ReceiveStructeData();

	//关闭socket
	void CloseSocket();

private:
	SOCKET m_socket; //socket;
	sockaddr_in m_sockLocalAddress;
	sockaddr_in m_sockReceiveAddress;
};

#endif  //RECEIVE_H_