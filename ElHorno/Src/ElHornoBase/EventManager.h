#pragma once
#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include <vector>
#include <queue>


namespace El_Horno {
	struct Event;
	class EventListener;
	class Entity;

	class EventManager
	{
	public:

		static EventManager* getInstance();
		static bool setupInstance();
		static void erase();

		void sendEvent(Event* e);
		void sendComponentEvent(EventListener* target, Event* e);
		void sendEntityEvent(Entity* target, Event* e);

		void processEvents();

		void clearQueue();
		void clearListeneres();

		void addListener(EventListener* eL);
		bool removeListener(EventListener* eL);

	private:

		static EventManager* instance_;

		EventManager() {};
		~EventManager();

		//Queue hacia todos los EventListener
		std::queue<Event*> eventsQueue_;

		//Queue de eventos de los que se conoce el EventListener destinatario
		std::queue<std::pair<EventListener*, Event*>> componentQueue_;

		//Queue de eventos a todos los componentes de la Entidad destinataria
		std::queue<std::pair<Entity*, Event*>> entityQueue_;

		std::vector<EventListener*> eventListeners_;
	};
}
#endif _EVENT_MANAGER_H