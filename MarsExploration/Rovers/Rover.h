#ifndef ROVER_
#define ROVER_

class Rover
{
private:
	//main properties
	char Type;
	int CheckUpDuration;
	int Speed;
	int ID;

	//needed properties
	bool isInCheckup;   //rover is in checkup
	bool isAvailable;   //rover is not assigned to a mission
	int missionCounter; //number of missions done by the rover
	int maxMissions;    // max number of mission needed to go to checkup
	int checkUpDay;     //day when the rover starts checkup

public:
	Rover(char t, int id, int c, int s, int max);
	void setType(char t);
	void setID(int id);
	void setCheckUpDuration(int c);
	void setSpeed(int s);
	void setIsAvailable(bool b);
	void setisInCheckup(bool b);
	void setCheckUpDay(int c);
	char getType();
	char getChecKUpDuration();
	char getSpeed();
	bool getisInCheckup();
	bool getisAvailable();
	int getCountMissions();
	int getmaxMissions();
	int getcheckUpDay();
	int getPriority();
	int getID();
	int FinishCheckUpDay();
	void increaseCountMissions();
	void resetCountMissions();
	~Rover();
};

#endif