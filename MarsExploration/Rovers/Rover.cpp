#include "Rover.h"

Rover::Rover(char t, int id, int c, int s, int max)
{
	setType(t);
	setID(id);
	setSpeed(s);
	setCheckUpDuration(c);
	isAvailable = true;
	isInCheckup = false;
	missionCounter = 0;
	maxMissions = max;
	checkUpDay = 0;
}

void Rover::setType(char t)
{
	if (t == 'E' || t == 'M' || t == 'P')
		Type = t;
	else
		Type = '\0';
}

void Rover::setID(int id)
{
	ID = (id > 0) ? id : 0;
}

void Rover::setCheckUpDuration(int c)
{
	CheckUpDuration = c > 0 ? c : 0;
}

void Rover::setSpeed(int s)
{
	Speed = s > 0 ? s : 0;
}

void Rover::setIsAvailable(bool b)
{
	isAvailable = b;
}

void Rover::setisInCheckup(bool b)
{
	isInCheckup = b;
}

void Rover::setCheckUpDay(int c)
{
	checkUpDay = (c > 0) ? c : 0;
}

char Rover::getType()
{
	return Type;
}

char Rover::getChecKUpDuration()
{
	return CheckUpDuration;
}

char Rover::getSpeed()
{
	return Speed;
}

bool Rover::getisInCheckup()
{
	return isInCheckup;
}

bool Rover::getisAvailable()
{
	return isAvailable;
}

int Rover::getCountMissions()
{
	return missionCounter;
}

int Rover::getmaxMissions()
{
	return maxMissions;
}

int Rover::getcheckUpDay()
{
	return checkUpDay;
}

int Rover::getPriority()
{
	return (1000 / FinishCheckUpDay()); //to put the high priority for less days
}

int Rover::getID()
{
	return ID;
}

int Rover::FinishCheckUpDay()
{
	return checkUpDay + CheckUpDuration;
}

void Rover::increaseCountMissions()
{
	missionCounter++;
}

void Rover::resetCountMissions()
{
	missionCounter = 0;
}

Rover::~Rover()
{
}
