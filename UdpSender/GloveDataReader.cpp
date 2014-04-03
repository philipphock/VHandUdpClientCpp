#include "stdafx.h"
#include "GloveDataReader.h"

#include "UdpInterface.h"
#include "JsonProtocol.h"

#include <string>
#include <sstream>

#include "VHand30.h"
GloveDataReader::GloveDataReader(void)
{
	


}


GloveDataReader::~GloveDataReader(void)
{

}

/**
	connects to the glove by the specified type
	returns true on success, false otherwise
**/
bool GloveDataReader::connect(ConnectionType type){
	if (type == ConnectionType::USB){
		return false;
	}
	return true;
}

/**
	reads one value from the glove
**/
void GloveDataReader::readValues(){
	sendToRemote();
}

/**
 sends a data value to the remote endpoint via udp using the JsonProtocol
**/
void GloveDataReader::sendToRemote(){
	int finger[5] = {0,-90,-90,-90,-90};
	int handRot[3] = {0,0,0};
	int handLoc[3] = {0,0,0};
	string jsonString;
	ptcl.createJSONString(jsonString,finger,handLoc,handRot);
	udp.send(jsonString);
}