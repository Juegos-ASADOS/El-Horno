#include "EventListener.h"
#include "EventManager.h"

EventListener::~EventListener()
{
	EventManager::getInstance()->removeListener(this);
}

bool EventListener::recieveEvent(Event* e)
{
	return false;
}
