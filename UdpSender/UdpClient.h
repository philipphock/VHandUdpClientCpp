#pragma once
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

class UdpClient
{

private:
	SOCKET s;
	SOCKADDR_IN *addr;
	int iResult;
public:
	UdpClient(int port);
	~UdpClient(void);

	void send(const std::string& toSend);
	
	
};

