#include "EventListener.h"
#include "EventManager.h"
#include "CheckML.h"

EventListener::~EventListener()
{
	El_Horno::EventManager::getInstance()->removeListener(this);
}

bool EventListener::recieveEvent(Event* e)
{
	return false;
}
