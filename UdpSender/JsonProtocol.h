#pragma once

#include <string>
#include <sstream>
using namespace std;
class JsonProtocol
{
public:
	JsonProtocol(void){};
	~JsonProtocol(void){};



	void createJSONString(string &outData,const int finger[5],const int hand_rotation[3],const int hand_location[3]) {
		stringstream tmp;
		tmp << "{\"finger\":[";
		tmp << finger[0] << ",";
		tmp << finger[1] << ",";
		tmp << finger[2] << ",";
		tmp << finger[3] << ",";
		tmp << finger[4] << "]";
		tmp << ",\"hand.rot\":[";
		tmp << hand_rotation[0] << ",";
		tmp << hand_rotation[1] << ",";
		tmp << hand_rotation[2] << "]";
		tmp << ",\"hand.loc\":[";
		tmp << hand_location[0] << ",";
		tmp << hand_location[1] << ",";
		tmp << hand_location[2] << "]}";

		
		outData = tmp.str();
	}
		


};

