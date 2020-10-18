#include <iostream>
#include "Receive.h"

using namespace std;
Receive::Receive(void)
{
	m_socket = INVALID_SOCKET;

	//初始化winsock
	WSAData ws;

	if (WSAStartup(MAKEWORD(1, 1), &ws))
	{
		cout << "WSAStartup failed" << WSAGetLastError() << endl;
	}
}

Receive::~Receive(void)
{
	WSACleanup();
}

bool Receive::InitSocket(const string strIPAddress, const string strPort)
{


	// 用于表示组播组地址的结构
	struct ip_mreq mreq;

	// 创建数据报类型的socket
	if ((m_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		//报错
		cout << "Allocating socket failed! Error:" << WSAGetLastError() << endl;

		return FALSE;
	}


	// 设定本地Socket地址信息
	//IPv4版本
	m_sockLocalAddress.sin_family = AF_INET;
	//端口
	m_sockLocalAddress.sin_port = htons(atol(strPort.c_str()));
	//地址
	m_sockLocalAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	// 绑定
	if (bind(m_socket,
		(struct sockaddr FAR *) &m_sockLocalAddress,
		sizeof(m_sockLocalAddress)) == SOCKET_ERROR)
	{
		//报错
		cout << "Binding socket failed! Error: " << WSAGetLastError() << endl;
		closesocket(m_socket);
		return FALSE;
	}

	// 欲加入组播组地址信息
	//组播地址
	mreq.imr_multiaddr.s_addr = inet_addr(strIPAddress.c_str());
	//透明所有协议
	mreq.imr_interface.s_addr = INADDR_ANY;

	//设置套接字选项,加入一个多播组
	if (setsockopt(m_socket,
		IPPROTO_IP,
		IP_ADD_MEMBERSHIP,
		(char FAR *)&mreq,
		sizeof(mreq)) == SOCKET_ERROR)
	{
		//报错

		cout << "setsockopt failed! Error: " << WSAGetLastError() << endl;
		closesocket(m_socket);
		return FALSE;
	}

	return true;


}


bool Receive::ReceiveStringData(char* strMessage)
{

	m_sockReceiveAddress.sin_family = AF_INET;

	int iRecvLen = sizeof(m_sockReceiveAddress);

	// 从组播组接收数据报
	if (recvfrom(m_socket,
		//接收数据的缓冲区
		strMessage,
		//缓冲区长度
		243,
		//接收数据的方式
		0,
		(struct sockaddr FAR *)&m_sockReceiveAddress,
		&iRecvLen) == SOCKET_ERROR)
	{
		//报错		
		cout << "recvfrom failed! Error: " << WSAGetLastError() << endl;
		closesocket(m_socket);
		return FALSE;
	}
	else
	{
		return true;
	}
}

void Receive::CloseSocket()
{
	// 禁用套接字
	shutdown(m_socket, 0x00);

	// 关闭套接字
	closesocket(m_socket);
}