#pragma once
#ifndef _EVENT_LISTENER_H
#define _EVENT_LISTENER_H

struct Event;

class EventListener
{
public:
	virtual ~EventListener();
	virtual bool recieveEvent(Event* e);
};

#endif _EVENT_LISTENER_H