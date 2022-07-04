#include "Event.h"

Event::Event(int ed, int id)
{
	setED(ed);
	setID(id);
}

Event::~Event()
{

}

void Event::setED(int i)
{
	EventDay = (i > 0) ? i : 0;
}

int Event::getED() const
{
	return EventDay;
}

void Event::setID(int i)
{
	ID = (i > 0) ? i : 0;
}

int Event::getID() const
{
	return ID;
}
