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

	/**
		sends a data value to the remote endpoint via udp using the JsonProtocol
	**/
	void sendToRemote(void);

public:
	GloveDataReader(void);
	~GloveDataReader(void);
	static enum ConnectionType {USB,WIFI};

	/**
		connetcs to the glove, return true if connection was successful
		the type of connection is specified by type:ConnectionType
	**/
	bool connect(ConnectionType type,unsigned int maxTicks,char* ip);

	/**
	 signature not yet specified
	**/
	/**
	reads one value from the glove
	**/
	void readValues(void);


	/**
		prints out status infos
	**/
	void status(void);


	/** 
		Disconnects the glove
	**/
	void disconnect(void);




};

