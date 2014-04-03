#pragma once
class GloveDataReader
{
public:
	GloveDataReader(void);
	~GloveDataReader(void);
	enum ConnectionType {USB,WIFI};

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

