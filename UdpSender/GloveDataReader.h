#pragma once
#pragma once
#include "UdpInterface.h"
#include "JsonProtocol.h"

class GloveDataReader
{
private:
	UdpInterface udp;
	JsonProtocol ptcl;
	void sendToRemote(void);

public:
	GloveDataReader(void);
	~GloveDataReader(void);
	static enum ConnectionType {USB,WIFI};

	/**
		connetcs to the glove, return true if connection was successful
		the type of connection is specified by type:ConnectionType
	**/
	bool connect(ConnectionType type);

	/**
	 signature not yet specified
	**/
	void readValues(void);


};

