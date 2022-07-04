#include "Event.h"

class CancelEvent :public Event
{
public:
	CancelEvent(int ed, int id);
	void Execute(MissionsList& m);
};

