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
		eventsQueue_.push(e);
	}

	void EventManager::sendComponentEvent(EventListener* target, Event* e)
	{
		componentQueue_.push({ target, e });
	}

	void EventManager::sendEntityEvent(Entity* target, Event* e)
	{
		entityQueue_.push({ target, e });
	}

	//Procesa todos los eventos y los envia a todas las entidades
	void EventManager::processEvents()
	{
		//Eventos generales
		while (!eventsQueue_.empty()) {
			Event* e = eventsQueue_.front(); eventsQueue_.pop();			
			for (EventListener* eL : eventListeners_) {
				eL->recieveEvent(e);
			}
			delete e;
		}

		//Eventos de entidades
		while (!entityQueue_.empty()) {
			Entity* target = entityQueue_.front().first;
			Event* e = entityQueue_.front().second; entityQueue_.pop();
			for (Component* cp : target->getComponents()) {
				cp->recieveEvent(e);
			}
			delete e;
		}

		//Eventos específicos
		while (!componentQueue_.empty()) {
			EventListener* target = componentQueue_.front().first;
			Event* e = componentQueue_.front().second; componentQueue_.pop();

			target->recieveEvent(e);

			delete e;
		}
	}

	//Vacia la cola de eventos
	void EventManager::clearQueue()
	{
		while (!eventsQueue_.empty()) {
			auto* elem = eventsQueue_.front(); eventsQueue_.pop();
			delete elem;
		}

		//Borra solo el evento
		while (!entityQueue_.empty()) {
			auto* elem = entityQueue_.front().second; entityQueue_.pop();
			delete elem;
		}

		//Idem al de arriba
		while (!componentQueue_.empty()) {
			auto* elem = componentQueue_.front().second; componentQueue_.pop();
			delete elem;
		}
	}

	//Vacia el vector de listeners de eventos
	void EventManager::clearListeneres()
	{
		eventListeners_.clear();
	}

	//Añade un listener al vector
	void EventManager::addListener(EventListener* eL)
	{
		eventListeners_.push_back(eL);
	}

	//Elimina un listener del vector
	bool EventManager::removeListener(EventListener* e)
	{
		auto it = eventListeners_.begin();
		while (it != eventListeners_.end()) {
			if (*it == e) {
				eventListeners_.erase(it);
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