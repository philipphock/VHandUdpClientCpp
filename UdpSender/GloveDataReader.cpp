#include "stdafx.h"
#include "GloveDataReader.h"

#include "UdpInterface.h"
#include "JsonProtocol.h"

#include <string>
#include <sstream>

#include "VHand30.h"
GloveDataReader::GloveDataReader(void)
{
	
	dataglove = new VHand30;

}


GloveDataReader::~GloveDataReader(void)
{
	delete dataglove;
}

/**
	connects to the glove by the specified type
	returns true on success, false otherwise
**/
bool GloveDataReader::connect(ConnectionType type,unsigned int maxTicks,char* ip){
	int ret=-1;
	if (type == ConnectionType::USB){
		dataglove->SetConnectionParameters(1,ip);
		int ret = dataglove->Connect(CONN_USB,STREAM_FINGERS_QUATERNION);
		connectionTypeRaw = CONN_USB;
	}else{
		dataglove->SetConnectionParameters(1,ip);
		int ret = dataglove->Connect(CONN_WIFI,STREAM_FINGERS_QUATERNION);
		connectionTypeRaw = CONN_WIFI;
	}

	fprintf(stderr,"CONNECT RET: %d\n",ret);
	long start = ::GetTickCount();
	while ((dataglove->Connected == NOT_CONNECTED))
	{
		if ((::GetTickCount()-start)>maxTicks){
			//timeout, error with the connection
			fprintf(stderr,"Cannot connect to the dataglove\n");
			dataglove->Disconnect();
			return false;
		}
	}
	return true;
}


unsigned int GloveDataReader::readValues(double finger[5],double rotation[3]){
	int connstatus = dataglove->GetConnectionStatus();
	if(connstatus == USB_CONNECTED || connstatus == WIFI_CONNECTED){
		dataglove->GetFingers(finger);
		dataglove->GetAttitude(&rotation[0],&rotation[1],&rotation[2]);
		unsigned int time = dataglove->GetLastPackageTime();
		return time;
	}else{
		throw "not connected";
	}
	
}


void GloveDataReader::sendToRemote(double finger[5],double rotation[3]){
	int fingerCalced[5] = {0,-90,-90,-90,-90};
	int handRot[3] = {0,0,0};
	int handLoc[3] = {0,0,0};
	string jsonString;
	ptcl.createJSONString(jsonString,fingerCalced,handLoc,handRot);
	udp.send(jsonString);
}


void GloveDataReader::disconnect(){
	dataglove->Disconnect();
	Sleep(1000);
	//turn off module
	dataglove->TurnOFF(connectionTypeRaw);
	Sleep(1000);
}

void GloveDataReader::status(){
	int connstatus = dataglove->GetConnectionStatus();

	//show dataglove informations
	char label[VHAND_STRLEN];
	int ID=0;
	dataglove->GetID(label,&ID);
	fprintf(stderr,"LABEL:%s ID:%d\n",label,ID);
	//firmware version
	int fw1,fw2,fw3;
	dataglove->GetFWVersion(&fw1,&fw2,&fw3);
	fprintf(stderr,"FIRMWARE:%d.%d.%d\n",fw1,fw2,fw3);
	//access point configuration
	char ssid[VHAND_STRLEN], pwd[VHAND_STRLEN];
	dataglove->GetAPNSettings(ssid,pwd);
	fprintf(stderr,"SSID: %s PWD:%s\n",ssid,pwd);
	//show network information
	char ip[VHAND_STRLEN], gw[VHAND_STRLEN], nm[VHAND_STRLEN];
	int DHCP;
	dataglove->GetWiFiSettings(ip,nm,gw,&DHCP);
	fprintf(stderr,"IP: %s NM:%s GW:%s DHCP:%d\n",ip,nm,gw,DHCP);

	if(connstatus == USB_CONNECTED || connstatus == WIFI_CONNECTED){
		double fing[5];
		double roll,pitch,yaw;
		dataglove->GetFingers(fing);
		dataglove->GetAttitude(&roll,&pitch,&yaw);
		unsigned int time = dataglove->GetLastPackageTime();
		fprintf(stderr,"TIME: %04d\n",time);
		fprintf(stderr,"F1:%.1f F2:%1.f F3:%.1f F4:%.1f F5:%.1f\n",fing[0],fing[1],fing[2],fing[3],fing[4]);
		fprintf(stderr,"ROLL:%.1f PITCH:%.1f YAW:%.1f\n",roll,pitch,yaw);
	}else{
		fprintf(stderr,"glove not connected");
	}

}