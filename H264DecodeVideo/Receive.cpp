#include <iostream>
#include "Receive.h"

using namespace std;
Receive::Receive(void)
{
	m_socket = INVALID_SOCKET;

	//��ʼ��winsock
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


	// ���ڱ�ʾ�鲥���ַ�Ľṹ
	struct ip_mreq mreq;

	// �������ݱ����͵�socket
	if ((m_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		//����
		cout << "Allocating socket failed! Error:" << WSAGetLastError() << endl;

		return FALSE;
	}


	// �趨����Socket��ַ��Ϣ
	//IPv4�汾
	m_sockLocalAddress.sin_family = AF_INET;
	//�˿�
	m_sockLocalAddress.sin_port = htons(atol(strPort.c_str()));
	//��ַ
	m_sockLocalAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	// ��
	if (bind(m_socket,
		(struct sockaddr FAR *) &m_sockLocalAddress,
		sizeof(m_sockLocalAddress)) == SOCKET_ERROR)
	{
		//����
		cout << "Binding socket failed! Error: " << WSAGetLastError() << endl;
		closesocket(m_socket);
		return FALSE;
	}

	// �������鲥���ַ��Ϣ
	//�鲥��ַ
	mreq.imr_multiaddr.s_addr = inet_addr(strIPAddress.c_str());
	//͸������Э��
	mreq.imr_interface.s_addr = INADDR_ANY;

	//�����׽���ѡ��,����һ���ಥ��
	if (setsockopt(m_socket,
		IPPROTO_IP,
		IP_ADD_MEMBERSHIP,
		(char FAR *)&mreq,
		sizeof(mreq)) == SOCKET_ERROR)
	{
		//����

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

	// ���鲥��������ݱ�
	if (recvfrom(m_socket,
		//�������ݵĻ�����
		strMessage,
		//����������
		243,
		//�������ݵķ�ʽ
		0,
		(struct sockaddr FAR *)&m_sockReceiveAddress,
		&iRecvLen) == SOCKET_ERROR)
	{
		//����		
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
	// �����׽���
	shutdown(m_socket, 0x00);

	// �ر��׽���
	closesocket(m_socket);
}