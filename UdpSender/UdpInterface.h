#pragma once
#include <iostream>
#include <string>

#include "UdpClient.h"

using namespace std;

/**
Helper Class for sending udp strings, default port is 11911 (to change in UdpClient.cpp)
**/
class UdpInterface
{
private: 
	UdpClient *client;
public:
	
	UdpInterface(void);
	virtual ~UdpInterface(void);

	/**
		sends an arbitrary string to the remote endpoint
	**/
	void send(const string &toSend);
};

