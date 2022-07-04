#include "Mission.h"

Missions::Missions(int id, char T, int FD, int TL, int MD, int Sig, int autop)
{
	setID(id);
	setType(T);
	setFD(FD);
	setTL(TL);
	setMD(MD);
	setSignificance(Sig);
	setAutpP(autop);
	Assign = false;
	WaitingDays = 0;
	HelpingRover = NULL;
	CompletionDay = 0;
	AutoPromoted = false;
	ExecutionDays = 0;
}

void Missions::setID(int id)
{
	ID = (id >= 0) ? id : 0;
}

void Missions::setType(char T)
{
	if (T == 'E' || T == 'M' || T == 'P')
		Type = T;
	else
		Type = '\0';
}

void Missions::setFD(int FD)
{
	FormulationDay = (FD >= 0) ? FD : 0;
}

void Missions::setTL(int TL)
{
	TargetLocation = (TL >= 0) ? TL : 0;
}

void Missions::setMD(int MD)
{
	MissionDuration = (MD >= 0) ? MD : 0;
}

void Missions::setSignificance(int Sig)
{
	Significance = (Sig >= 0) ? Sig : 0;
}

void Missions::setAutpP(int autop)
{
	AutoP = (autop >= 0) ? autop : 0;
}

void Missions::setAutoPromoted(bool b)
{
	AutoPromoted = b;
}

bool Missions::getAutoPromoted() const
{
	return AutoPromoted;
}

int Missions::getID()
{
	return ID;
}

char Missions::getType()
{
	return Type;
}

int Missions::getFD()
{
	return FormulationDay;
}

int Missions::getWD()
{
	return WaitingDays;
}


int Missions::getCD()
{
	return CompletionDay;
}

int Missions::getED()
{
	return ExecutionDays;
}

int Missions::getMD()
{
	return MissionDuration;
}

int Missions::getTL()
{
	return TargetLocation;
}

int Missions::getAutoP()
{
	return AutoP;
}

int Missions::getSignificance()
{
	return Significance;
}

Rover* Missions::getHelpingRover()
{
	return HelpingRover;
}

void Missions::AssignRover(Rover* R)
{
	HelpingRover = R;
	Assign = true;
	R->setIsAvailable(false);

	int RS = HelpingRover->getSpeed();//rover speed
	ExecutionDays = MissionDuration + ceil(2 * ((float(TargetLocation) / RS) / 25)); //number of days required to go and back from the mission location + the mission duration
	CompletionDay = FormulationDay + WaitingDays + ExecutionDays; //total days needed to finish the mission
}

void Missions::Update()
{
	// if the mission is not assigned yet, increase the waiting days counter 
	if (!Assign)
		WaitingDays++;
}

Missions::~Missions()
{
}
