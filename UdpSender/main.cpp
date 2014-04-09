// main.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "GloveDataReader.h"
using namespace std;

GloveDataReader *gloveReader;

void success(){
	//cout << "connected with dataglove" << endl;	
	//gloveReader->status();
	//cin.get();
	double finger[5];
	double rot[3];

	//gloveReader->status();

	while(gloveReader->isConnected()){
		Sleep(100);
		gloveReader->readValues(finger,rot);
//		finger[0] = 0;
//		finger[1] = 0;
//		finger[2] = 0;
//		finger[3] = 0;
//		finger[4] = 0;
//		rot[0] = 0.0;
//		rot[1] = 0.0;
//		rot[2] = 0.0;
		gloveReader->sendToRemote(finger,rot);
		
		printf("(%.1f, %.1f, %.1f)\n",rot[0],rot[1],rot[2]);
	}
		cin.get();
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	gloveReader = new GloveDataReader();

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

