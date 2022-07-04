#pragma once
#include "../Rovers/Rover.h"
#include "../Rovers/RoverLists.h";
#include"../Missions/MissionsList.h"
#include"../Queue/LinkedQueue.h"
#include"../Queue/PriorityLinkedQueue.h"
#include "../Event/Event.h"
#include "../Event/FormulationEvent.h"
#include "../Event/CancelEvent.h"
#include "../Event/PromoteEvent.h"
#include <string>
#include <chrono> //Used in step by step mode to pause for 1 sec
#include <thread> //Used in step by step mode to pause for 1 sec
#include<fstream>
#include<iostream>
using namespace std;

class UI
{
	int mode;
public:
	UI();
	int getMode(); //to get the mode of the console output
	void readInput(RoverLists& RL, LinkedQueue<Event*>& EL);
	void consoleOutput(MissionsList& ML, RoverLists& RL, long curDay);
};

