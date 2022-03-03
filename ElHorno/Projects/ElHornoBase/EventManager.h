#pragma once

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
	void processEvents();
	void clearQueue();
	void clearListeneres();
	void addListener(EventListener* eL);
	bool removeListener(EventListener* eL);

private:

	static EventManager* instance;

	EventManager() {};
	~EventManager();

	std::queue<Event*> eventsQueue;
	std::vector<EventListener*> eventListeners;
};
