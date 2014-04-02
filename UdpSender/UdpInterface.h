#pragma once
#include <iostream>
#include <string>

#include "UdpClient.h"

using namespace std;

class UdpInterface
{
public:
	UdpClient *client;
	
	
	UdpInterface(void);
	virtual ~UdpInterface(void);

	void send(const string &toSend);
};

