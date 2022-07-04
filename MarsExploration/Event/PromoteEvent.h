#include "Event.h"

class PromoteEvent :public Event
{
public:
	PromoteEvent(int ed, int id);
	void Execute(MissionsList& m);
};

