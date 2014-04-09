#pragma once
#pragma once
#include "UdpInterface.h"
#include "JsonProtocol.h"
#include "VHand30.h"

class GloveDataReader
{
private:
	UdpInterface udp;
	JsonProtocol ptcl;
	VHand30 *dataglove;
	int connectionTypeRaw;
	int mapCoordinates(double x);
	

public:
	GloveDataReader(void);
	~GloveDataReader(void);
	bool isConnected(void);
	static enum ConnectionType {USB,WIFI};

	/**
		connetcs to the glove, return true if connection was successful
		the type of connection is specified by type:ConnectionType
	**/
	bool connect(ConnectionType type,unsigned int maxTicks,int comport, char* ip);

	
	/**
	reads one value from the glove,
	finger[5] are values from 0..100
	rotation: [roll,pitch,yaw] in degree
	**/
	unsigned int GloveDataReader::readValues(double finger[5],double rotation[3]);


	/**
		prints out status infos
	**/
	void status(void);

	/**
		sends data values to the remote endpoint via udp using the JsonProtocol
	**/
	void GloveDataReader::sendToRemote(double finger[5],double rotation[3]);

	/** 
		Disconnects the glove
	**/
	void disconnect(void);




};

