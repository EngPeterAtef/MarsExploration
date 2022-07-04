#ifndef MISSIONS_LIST_
#define MISSIONS_LIST_
#include "Mission.h"
#include "../Queue/LinkedQueue.h"
#include "../Queue/PriorityLinkedQueue.h"
#include "../Rovers/RoverLists.h"

class MissionsList
{
private:
	//main lists
	PriorityLinkedQueue<Missions*> E;
	LinkedQueue<Missions*> M;
	LinkedQueue<Missions*> P;
	//inexecution list
	PriorityLinkedQueue<Missions*> inEx;
	//completed missions 
	LinkedQueue<Missions*> CompletedMissionsL;
	//counters 
	int WaitingMissions; // number of the missions waiting for an available rover 
	int InExecutionMissions;
	int AutoPromotedMissions;
	int Enum, Mnum, Pnum; // numbers of the each type of the missions
public:
	MissionsList();
	void AddMission(Missions* newMission);  // used to add a mission to the appropriate list 
	void AddMissionToExecution(Missions* newMission); // used to add the mission to the execution list
	void Update(int CurrentDay, RoverLists& RL); // used to update all the missions in the lists and move the completed missions to completed list
	Missions*& getAvailable_E(); // used to get the first ready Emergency mission to be assigned
	Missions*& getAvailable_M(); // used to get the first ready Mountainous mission to be assigned
	Missions*& getAvailable_P(); // used to get the first ready Polar mission to be assigned
	bool isEmpty(); // used to know if all the lists are empty (the stopping condition for the simulation)
	int getNumOf_WaitingMissions();
	int getNumOf_InExecutionMissions();
	int getNumOf_AutoPromotedMissions();
	int getNumOf_EM();
	int getNumOf_MM();
	int getNumOf_PM();
	void decrease_MNum();
	LinkedQueue<Missions*> getCompletedMissions();
	PriorityLinkedQueue<Missions*> getInExecutionList();
	LinkedQueue<Missions*> getWaitingMountainuousList();
	LinkedQueue<Missions*> getWaitingPolarList();
	PriorityLinkedQueue<Missions*> getWaitingEmergencyList();
	Missions*& GetWaitingMount(int id);
	~MissionsList();
};

#endif