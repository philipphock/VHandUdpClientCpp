#include "stdafx.h"
#include "UdpClient.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

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
		std::stringstream serr;
		serr << "WSAStartup failed with error: "<<iResult;
		fprintf(stderr,serr.str().c_str());
		//throw serr.str().c_str();
        
        return;
    }

    //---------------------------------------------
    // Create a socket for sending data
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) {
		std::stringstream serr;
		serr << "socket failed with error: "<<WSAGetLastError();
		fprintf(stderr,serr.str().c_str());
		//throw serr.str().c_str();
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
	std::cout << "socket init" << std::endl;
    //---------------------------------------------
    // Send a datagram to the receiver
    
	//---------------------------------------------

   

}

void UdpClient::send(const std::string& toSend){
	const char* cstr = toSend.c_str();
	
    iResult = sendto(s,cstr, strlen(cstr), 0, (SOCKADDR *)  addr, sizeof (*addr));
    if (iResult == SOCKET_ERROR) {
		std::stringstream serr;
		serr << "sendto failed with error: " << WSAGetLastError() << "\n";
        closesocket(s);
        WSACleanup();
		fprintf(stderr,serr.str().c_str());

		//throw serr.str().c_str();
        return;
    }
    
	
}


UdpClient::~UdpClient(void)
{
	    // When the application is finished sending, close the socket.
    
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR) {
		std::stringstream serr;
		serr << "closesocket failed with error: " << WSAGetLastError() << "\n";
        closesocket(s);
        WSACleanup();
		throw serr.str();
        return;
    }
}


