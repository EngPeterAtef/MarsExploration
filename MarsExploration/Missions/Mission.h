#ifndef MISSIONS_
#define MISSIONS_
#include "../Rovers/Rover.h"
#include <cmath>

class Missions
{
private:
	//main properties
	int ID;
	char Type;
	int FormulationDay;
	int TargetLocation;
	int MissionDuration;
	int Significance;
	int AutoP;
	//needed properties
	Rover* HelpingRover;
	int WaitingDays; //days the mission waited to be assigned
	int CompletionDay; //number of days needed to finish the mission (waiting days ,traveling days and execution days)
	int ExecutionDays; //the days it takes to reach the target location, fulfill the mission, and then get back to the base station
	bool Assign; //is the mission assigned to a rover
	bool AutoPromoted; //is the mission promoted to be emergency mission
public:
	Missions(int id, char T, int FD, int TL, int MD, int Sig, int autop);
	void setID(int id);
	void setType(char T);
	void setFD(int FD);
	void setTL(int TL);
	void setMD(int MD);
	void setSignificance(int Sig);
	void setAutpP(int autop);
	void setAutoPromoted(bool b);
	bool getAutoPromoted() const;
	int getID();
	char getType();
	int getFD();
	int getWD();
	int getCD();
	int getED();
	int getMD();
	int getTL();
	int getAutoP();
	int getSignificance();
	Rover* getHelpingRover();
	void AssignRover(Rover* R);
	void Update();
	~Missions();
};

#endif

