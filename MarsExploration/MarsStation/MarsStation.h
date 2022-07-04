#ifndef MARS_STATION_
#define MARS_STATION_

#include "../Missions/MissionsList.h"
#include "../Rovers/RoverLists.h"
#include "../UI/UI.h"
#include "../Event/Event.h"

class MarsStation {
private:
	//event list here
	MissionsList ML;
	RoverLists RL;
	LinkedQueue<Event*> EventList;
	UI Ui;
	int CurrentDay;
	// Utility functions
	void OpenFile();
	void DailyDisplay();
	void Assign(char t);
	bool Continue();
public:
	MarsStation();
	int getCurrentDay();
	void Simulate();
	void OutPutFile();
	~MarsStation();
};






#endif