#pragma once
#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include <vector>
#include <queue>

class EventListener;
struct Event;

class EventManager
{
public:

	static EventManager* getInstance();
	static bool setupInstance();
	static void erase();

	void sendEvent(Event* e);
	void sendTargetEvent(EventListener* target, Event* e);

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
	std::queue<Event*> eventsQueue;
	
	//Queue de eventos de los que se conoce el EventListener destinatario
	std::queue<std::pair<EventListener*, Event*>> targetEventsQueue;
	
	std::vector<EventListener*> eventListeners;
};

#endif _EVENT_MANAGER_H