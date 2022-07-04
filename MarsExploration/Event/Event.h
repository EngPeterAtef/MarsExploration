#ifndef EVENT_
#define EVENT_
#include "../Missions/MissionsList.h"

class Event
{
private:
	int EventDay;
	int ID; //ID of the mission
public:
	Event(int ed, int id);
	~Event();

	void setED(int i);
	int getED() const;
	void setID(int i);
	int getID() const;
	virtual void Execute(MissionsList& m) = 0;
};

#endif
