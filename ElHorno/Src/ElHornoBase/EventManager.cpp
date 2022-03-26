#include "EventManager.h"
#include "Event.h"
#include "EventListener.h"
#include "CheckMl.h"

EventManager* EventManager::instance = 0;

EventManager* EventManager::getInstance()
{
	if (instance == 0)
		return nullptr;

	return instance;
}

bool EventManager::setupInstance()
{
	if (instance == 0) {
		instance = new EventManager();
		return true;
	}
	return false;
}

void EventManager::erase()
{
	delete instance;
}

//Coloca el evento en una lista de eventos a procesar
void EventManager::sendEvent(Event* e)
{
	
	eventsQueue.push(e);
}

//Procesa todos los eventos y los envia a todas las entidades
void EventManager::processEvents()
{
	while (!eventsQueue.empty()) {
		Event* e = eventsQueue.front(); eventsQueue.pop();
		for (EventListener* eL : eventListeners) {
			eL->recieveEvent(e);
		}
		delete e;
	}
}

//Vacia la cola de eventos
void EventManager::clearQueue()
{
	while (!eventsQueue.empty()) {
		eventsQueue.pop();
	}
}

//Vacia el vector de listeners de eventos
void EventManager::clearListeneres()
{
	eventListeners.clear();
}

//Añade un listener al vector
void EventManager::addListener(EventListener* eL)
{
	eventListeners.push_back(eL);
}

//Elimina un listener del vector
bool EventManager::removeListener(EventListener* e)
{
	auto it = eventListeners.begin();
	while (it != eventListeners.end()) {
		if (*it == e) {
			eventListeners.erase(it);
			return true;
		}
		++it;
	}
	return false;
}

EventManager::~EventManager()
{
}
