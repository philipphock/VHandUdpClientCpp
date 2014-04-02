#include "stdafx.h"
#include "UdpClient.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN



UdpClient::UdpClient(int port)
{
    iResult;
    WSADATA wsaData;

    s = INVALID_SOCKET;
    addr = new sockaddr_in;

    unsigned short Port = port;

    

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return;
    }

    //---------------------------------------------
    // Create a socket for sending data
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return;
    }
    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // the receiver (in this example case "192.168.1.1")
    // and the specified port number.
    addr->sin_family = AF_INET;
    addr->sin_port = htons(Port);
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    //---------------------------------------------
    // Send a datagram to the receiver
    
	//---------------------------------------------

   

}

void UdpClient::send(const std::string& toSend){
	std::cout << "sending data: "<< toSend << std::endl;
	
	const char* cstr = toSend.c_str();
	
	wprintf(L"Sending a datagram to the receiver...\n");
    iResult = sendto(s,cstr, strlen(cstr), 0, (SOCKADDR *)  addr, sizeof (*addr));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }
    
	
}


UdpClient::~UdpClient(void)
{
	    // When the application is finished sending, close the socket.
    wprintf(L"Finished sending. Closing socket.\n");
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
}




/*


int main()
{


    return 0;
}
*/