#include "stdafx.h"
#include "UdpInterface.h"
#include "UdpClient.h"



UdpInterface::UdpInterface(void)
{
	client = new UdpClient(11911);
}


UdpInterface::~UdpInterface(void)
{
	delete client;
}


void UdpInterface::send(const string &toSend){
	client->send(toSend);
	
	
	
}



