#pragma once
#ifndef _EVENT_LISTENER_H
#define _EVENT_LISTENER_H


namespace El_Horno {
	struct Event;
	class _declspec(dllexport) EventListener
	{
	public:
		virtual ~EventListener();
		virtual bool recieveEvent(Event* e);
	};
}
#endif _EVENT_LISTENER_H