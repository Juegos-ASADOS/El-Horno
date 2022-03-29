#include "EventManager.h"
#include "Event.h"
#include "EventListener.h"
#include "CheckML.h"

namespace El_Horno {
	EventManager* EventManager::instance_ = 0;

	EventManager* EventManager::getInstance()
	{
		if (instance_ == 0)
			return nullptr;

		return instance_;
	}

	bool EventManager::setupInstance()
	{
		if (instance_ == 0) {
			instance_ = new EventManager();
			return true;
		}
		return false;
	}

	void EventManager::erase()
	{
		delete instance_;
	}

	//Coloca el evento en una lista de eventos a procesar
	void EventManager::sendEvent(Event* e)
	{
		eventsQueue.push(e);
	}

	void EventManager::sendTargetEvent(EventListener* target, Event* e)
	{
		targetEventsQueue.push({ target, e });
	}

	//Procesa todos los eventos y los envia a todas las entidades
	void EventManager::processEvents()
	{
		//Eventos generales
		while (!eventsQueue.empty()) {
			Event* e = eventsQueue.front(); eventsQueue.pop();
			for (EventListener* eL : eventListeners) {
				eL->recieveEvent(e);
			}
			delete e;
		}

		//Eventos específicos
		while (!targetEventsQueue.empty()) {
			EventListener* target = targetEventsQueue.front().first;
			Event* e = targetEventsQueue.front().second;
			targetEventsQueue.pop();

			target->recieveEvent(e);

			delete e;
		}
	}

	//Vacia la cola de eventos
	void EventManager::clearQueue()
	{
		while (!eventsQueue.empty()) {
			eventsQueue.pop();
		}

		while (!targetEventsQueue.empty()) {
			targetEventsQueue.pop();
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
}