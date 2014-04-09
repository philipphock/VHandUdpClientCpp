// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "GloveDataReader.h"
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <signal.h>


using namespace std;

GloveDataReader *gloveReader;
volatile bool isRunnung = true;
BOOL WINAPI ConsoleHandler(
    DWORD dwCtrlType   //  control signal type
);

void success(){
	double finger[5];
	double rot[3];

	//gloveReader->status();

	while(isRunnung && gloveReader->isConnected()){
		Sleep(100);
		gloveReader->readValues(finger,rot);
		gloveReader->sendToRemote(finger,rot);
	}
	gloveReader->disconnect();
	cout << "disconnected, press any key to exit..." << endl;
	cin.get();
}

int _tmain(int argc, _TCHAR* argv[])
{
	gloveReader = new GloveDataReader();
	if (SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
    {
        fprintf(stderr,"Unable to install handler!\n");
        return -1;
    }
	

	
	cout << "connecting to glove. ";
	cout << "Try USB..." << endl;
	if (gloveReader->connect(GloveDataReader::ConnectionType::USB,5000,4,"127.0.0.1")){
		cout << "success" << endl;	
		success();
		return 0;
	}


	cout << "failed, try Wifi... " << endl;	
	if (gloveReader->connect(GloveDataReader::ConnectionType::WIFI,5000,4,"127.0.0.1")){
		cout << "success" << endl;	
		success();
		return 0;
	}
	cout << "failed, sorry... " << endl;	
	cin.get();
	return 1;
}








BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
    char mesg[128];

    switch(CEvent)
    {
		case CTRL_C_EVENT:
			isRunnung = false;
        break;
    }
    return TRUE;
}