#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(int ed, int id, char Mt, int TL, int MD, int sig, int autop) :Event(ed, id)
{
	MissionType = Mt;
	TLOC = TL;
	MDUR = MD;
	SIG = sig;
	AutoP = autop;
}

void FormulationEvent::Execute(MissionsList& m)
{
	Missions* Mnew = new Missions(getID(), MissionType, getED(), TLOC, MDUR, SIG, AutoP);
	m.AddMission(Mnew);
}
