#include "EventListener.h"
#include "EventManager.h"

EventListener::~EventListener()
{
	EventManager::getInstance()->removeListener(this);
}
