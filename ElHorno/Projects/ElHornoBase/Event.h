#pragma once

enum EventType {
	EventoBase
};

struct Event {
	Event(EventType ty) : ty_(ty) {};
	EventType ty_;

	virtual ~Event() {};
};