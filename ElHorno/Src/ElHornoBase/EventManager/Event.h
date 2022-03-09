#pragma once

//No se si deberia de ser un ChangeScene o que directamente sea Scene1 y que te cambie al menú o a X scena en concreto
enum EventType {
	EventoBase,ChangeScene
};

struct Event {
	Event(EventType ty) : ty_(ty) {};
	EventType ty_;

	virtual ~Event() {};
};