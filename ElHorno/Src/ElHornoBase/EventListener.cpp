#include "EventListener.h"
#include "EventManager.h"
#include "CheckML.h"

namespace El_Horno {
	EventListener::~EventListener()
	{
		EventManager::getInstance()->removeListener(this);
	}

	bool EventListener::recieveEvent(Event* e)
	{
		return false;
	}
}