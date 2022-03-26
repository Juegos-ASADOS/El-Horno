#include "EventListener.h"
#include "EventManager.h"
#include "CheckMl.h"

EventListener::~EventListener()
{
	EventManager::getInstance()->removeListener(this);
}

bool EventListener::recieveEvent(Event* e)
{
	return false;
}
