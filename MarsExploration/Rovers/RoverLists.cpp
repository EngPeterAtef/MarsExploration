#include"RoverLists.h"

RoverLists::RoverLists()
{
	AvailableRovers = InCheckUpRovers = 0;
	ERnum = MRnum = PRnum = 0;
}


//Add Rover to it's corresponding RoverList for the first time or after getting back from a mission or after getting back from CheckUp
void RoverLists::addtoRoverList(Rover* R) 
{
	Pair<Rover*, int> Pa;
	Pa.first = R;
	Pa.second = R->getSpeed();
	char type = R->getType();
	if (type == 'E')
	{
		E.enqueue(Pa);
		//if the rover was not already in the list (not coming back from a mission or CheckUp)
		if (!R->getisInCheckup() && R->getisAvailable()) 
			ERnum++;

	}
	else if (type == 'M')
	{
		M.enqueue(Pa);
		if (!R->getisInCheckup() && R->getisAvailable())
			MRnum++;
	}
	else  if (type == 'P')
	{
		P.enqueue(Pa);
		if (!R->getisInCheckup() && R->getisAvailable()) 
			PRnum++;
	}
	R->setisInCheckup(false);
	R->setIsAvailable(true);
	AvailableRovers++;
}


//if there is an available Rover for a mission of type t
bool RoverLists::isAvailable(char t)
{
	if (t == 'E')
	{
		if (!E.isEmpty())
			return true;
		else if (!M.isEmpty())
			return true;
		else if (!P.isEmpty())
			return true;
	}
	else if (t == 'M')
	{
		if (!M.isEmpty())
			return true;
		else if (!E.isEmpty())
			return true;
	}
	else  if (t == 'P')
	{
		if (!P.isEmpty())
			return true;
	}
	return false;
}


//Return a suitable Rover for a mission of type t
Rover* RoverLists::getAvailableRover(char t)
{
	Rover* R = nullptr;
	Pair<Rover*, int> Pa;
	Pa.first = nullptr;
	if (t == 'E')
	{
		if (!E.isEmpty())
			E.dequeue(Pa);
		else if (!M.isEmpty())
			M.dequeue(Pa);
		else if (!P.isEmpty())
			P.dequeue(Pa);
	}
	else if (t == 'M')
	{
		if (!M.isEmpty())
			M.dequeue(Pa);
		else if (!E.isEmpty())
			E.dequeue(Pa);
	}
	else  if (t == 'P')
	{
		if (!P.isEmpty())
			P.dequeue(Pa);
	}
	R = Pa.first;

	if (R) // if there is available Rover (not null) decreament waiting Rovers 
	{
		AvailableRovers--;
		R->setIsAvailable(false);
	}
	return R;
}


//after n missions the Rover is added to CheckUp List
void RoverLists::addToCheckUpList(Rover* R, int CurrentDay)
{
	R->setCheckUpDay(CurrentDay);
	Pair<Rover*, int> P;
	P.first = R;
	P.second = R->getPriority();

	CheckupList.enqueue(P);
	R->setisInCheckup(true);
	InCheckUpRovers++;
}

void RoverLists::ReturnRover(Rover* R, int CurrentDay)
{
	R->increaseCountMissions();
	if (R->getmaxMissions() == R->getCountMissions())
		addToCheckUpList(R, CurrentDay);

	else
		addtoRoverList(R); //coming back from a mission ( was already in the roverlist ) no need to increament Rnum
}

void RoverLists::Update(int CurrentDay)
{
	do
	{
		Pair<Rover*, int> P;
		if (!CheckupList.isEmpty()) {

			CheckupList.peek(P);

			if (P.first->FinishCheckUpDay() == CurrentDay) // return Rover to list after CheckUp
			{
				CheckupList.dequeue(P);
				addtoRoverList(P.first); //coming from checkup ( was already in the roverlist ) no need to increament Rnum
				P.first->resetCountMissions();
				InCheckUpRovers--;
			}
			else break;
		}
		else break;
	} while (true);
}

bool RoverLists::isCheckUpEmpty()
{
	return CheckupList.isEmpty();
}

int RoverLists::getNumOf_ER()
{
	return ERnum;
}

int RoverLists::getNumOf_MR()
{
	return MRnum;
}

int RoverLists::getNumOf_PR()
{
	return PRnum;
}

int RoverLists::getNumOf_WaitingRovers()
{
	return AvailableRovers;
}

int RoverLists::getNumOf_InCheckUpRovers()
{
	return InCheckUpRovers;
}

PriorityLinkedQueue<Rover*> RoverLists::getAvailableEmergencyList()
{
	return E;
}

PriorityLinkedQueue<Rover*> RoverLists::getAvailableMountanuousList()
{
	return M;
}

PriorityLinkedQueue<Rover*> RoverLists::getAvailablePolarList()
{
	return P;
}

PriorityLinkedQueue<Rover*> RoverLists::getCheckupList()
{
	return CheckupList;
}
