#pragma once

#include <string>
#include <sstream>
using namespace std;
class JsonProtocol
{
public:
	JsonProtocol(void){};
	~JsonProtocol(void){};


	/**
		stores a json in outData with the values afterwards. Alternatively use void createJSONString(string &outData,int thumb,int index,int middle,int ring,int pinky,int hand_yaw,int hand_pitch,int hand_roll,int hand_x,int hand_y, int hand_z)
		the values afterwards represent rotation of the fingers and the hand, also the location of the hand. Rotation of fingers are in range 0..-90 (degree), where 0 is fully straight, -90 is fully curved. The Rotation of the hand is represented as euler (yaw, pitch, roll) in degree
	**/
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

	/**
		stores a json in outData with the values afterwards. This is a wrapper for createJSONString(string &outData,const int finger[5],const int hand_rotation[3],const int hand_location[3])
	**/
	void createJSONString(string &outData,int thumb,int index,int middle,int ring,int pinky,int hand_roll,int hand_pitch,int hand_yaw,int hand_x,int hand_y, int hand_z){
		int finger[5] = {thumb,index,middle,ring,pinky};
		int handRot[3] = {hand_roll,hand_pitch,hand_yaw};
		int handLoc[3] = {hand_x,hand_y,hand_z};
		createJSONString(outData,finger,handRot,handLoc);
	}

};

