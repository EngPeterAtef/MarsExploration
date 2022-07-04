#include "CancelEvent.h"

CancelEvent::CancelEvent(int ed, int id) : Event(ed, id)
{

}

void CancelEvent::Execute(MissionsList& m)
{
	Missions* XM = m.GetWaitingMount(getID());

	if (XM) {
		m.decrease_MNum();
		delete XM;
		XM = NULL;
	}
}
