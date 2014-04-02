// UdpSender.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "UdpInterface.h"
#include "JsonProtocol.h"

#include <string>
#include <sstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	UdpInterface udp;
	JsonProtocol ptcl;
	string jsonString;

	int finger[5] = {0,-90,-90,-90,-90};
	int handRot[3] = {0,0,0};
	int handLoc[3] = {0,0,0};
	ptcl.createJSONString(jsonString,finger,handLoc,handRot);
	
	udp.send(jsonString);
	

	cin.ignore();
	cin.get();
	return 0;
}

