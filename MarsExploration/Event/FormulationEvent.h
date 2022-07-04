#include "Event.h"

class FormulationEvent :public Event
{
private:
	char MissionType;
	int TLOC; //is the mission’s target location(in kilometers from the base station).
	int MDUR; //is the number of days needed to fulfill the mission requirements at target location.
	int SIG; //is the mission’s significance
	int AutoP; // the auto promotion limit
public:
	FormulationEvent(int ed, int id, char Mt, int TL, int MD, int sig, int autop);
	void Execute(MissionsList& m);//To add a mission this function is called by mars station
	
};

