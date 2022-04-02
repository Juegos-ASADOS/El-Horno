#include "EventManager.h"
#include "Event.h"
#include "Entity.h"
#include "Component.h"
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

	void EventManager::sendComponentEvent(EventListener* target, Event* e)
	{
		componentQueue.push({ target, e });
	}

	void EventManager::sendEntityEvent(Entity* target, Event* e)
	{
		entityQueue.push({ target, e });
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

		//Eventos de entidades
		while (!entityQueue.empty()) {
			Entity* target = entityQueue.front().first;
			Event* e = entityQueue.front().second; entityQueue.pop();
			for (Component* cp : target->getComponents()) {
				cp->recieveEvent(e);
			}
			delete e;
		}

		//Eventos específicos
		while (!componentQueue.empty()) {
			EventListener* target = componentQueue.front().first;
			Event* e = componentQueue.front().second; componentQueue.pop();

			target->recieveEvent(e);

			delete e;
		}
	}

	//Vacia la cola de eventos
	void EventManager::clearQueue()
	{
		while (!eventsQueue.empty()) {
			auto* elem = eventsQueue.front(); eventsQueue.pop();
			delete elem;
		}

		//Borra solo el evento
		while (!entityQueue.empty()) {
			auto* elem = entityQueue.front().second; entityQueue.pop();
			delete elem;
		}
		
		//Idem al de arriba
		while (!componentQueue.empty()) {
			auto* elem = componentQueue.front().second; componentQueue.pop();
			delete elem;
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
		clearQueue();
	}
}