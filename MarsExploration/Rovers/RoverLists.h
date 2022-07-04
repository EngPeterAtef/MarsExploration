#ifndef ROVER_LIST_
#define ROVER_LIST_

#include"..\Queue\LinkedQueue.h"
#include"..\Queue\PriorityLinkedQueue.h"
#include"Rover.h"

class RoverLists
{
private:
	//Rover are sorted in queue by their speed
	PriorityLinkedQueue<Rover*> E;
	PriorityLinkedQueue<Rover*> M;
	PriorityLinkedQueue<Rover*> P;
	PriorityLinkedQueue<Rover*> CheckupList;

	//counters 
	int AvailableRovers;
	int InCheckUpRovers;
	int ERnum, MRnum, PRnum;
public:
	RoverLists();
	void addtoRoverList(Rover* R); //the bool flag is to indecate that the rover was already in the list if was true
	bool isAvailable(char type); 
	Rover* getAvailableRover(char type); //mission type - assign a rover to a mission 
	void addToCheckUpList(Rover* R, int CurrentDay);
	void ReturnRover(Rover* R, int CurrentDay);
	void Update(int CurrentDay);
	bool isCheckUpEmpty();
	int getNumOf_ER();
	int getNumOf_MR();
	int getNumOf_PR();
	int getNumOf_WaitingRovers();
	int getNumOf_InCheckUpRovers();
	PriorityLinkedQueue<Rover*> getAvailableEmergencyList();
	PriorityLinkedQueue<Rover*> getAvailableMountanuousList();
	PriorityLinkedQueue<Rover*> getAvailablePolarList();
	PriorityLinkedQueue<Rover*> getCheckupList();

};

#endif



