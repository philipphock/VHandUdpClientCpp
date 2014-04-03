#pragma once
#include <WinSock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")


/**
 Helper Class to provide a UDP Client. Code mostly adapted from msdn.
**/
class UdpClient
{

private:
	SOCKET s;
	SOCKADDR_IN *addr;
	int iResult;
public:
	/**
	Initializes the socket and connects to localhost:port
	**/
	UdpClient(int port);
	~UdpClient(void);

	/**
	sends an arbitrary string to the remote endpoint
	**/
	void send(const std::string& toSend);
	
	
};

