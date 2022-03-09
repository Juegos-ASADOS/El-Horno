#pragma once

struct Event;

class EventListener
{
public:
	virtual ~EventListener();
	virtual bool recieveEvent(Event* e);
};