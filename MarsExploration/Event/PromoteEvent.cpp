#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(int ed, int id): Event(ed, id)
{
	
}

void PromoteEvent::Execute(MissionsList& m)
{
	Missions* PM = m.GetWaitingMount(getID());
	if (PM) 
	{
		PM->setType('E');
		PM->setAutoPromoted(true);
		m.decrease_MNum();
		m.AddMission(PM);
	}
}
