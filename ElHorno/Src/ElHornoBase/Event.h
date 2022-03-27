#pragma once
#ifndef _EVENT_H
#define _EVENT_H

//No se si deberia de ser un ChangeScene o que directamente sea Scene1 y que te cambie al menú o a X scena en concreto
enum EventType {
	EventoBase, ChangeScene, Collision
};

struct Event {
	Event(EventType ty) : ty_(ty) {};
	EventType ty_;

	virtual ~Event() {};
};

class Entity;
struct RigidBodyCollision : public Event {
public:
	RigidBodyCollision(Entity* other) : Event(EventType::Collision) {
		other_ = other;
	}
	Entity* other_;
};

#endif _EVENT_H