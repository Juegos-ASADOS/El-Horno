#pragma once
#ifndef _EVENT_H
#define _EVENT_H

//No se si deberia de ser un ChangeScene o que directamente sea Scene1 y que te cambie al menú o a X scena en concreto

namespace El_Horno {
	enum EventType {
		EventoBase, ChangeScene,
		CollisionEnter, CollisionStay, CollisionExit,
		TriggerEnter, TriggerStay, TriggerExit
	};

	struct Event {
		Event(EventType ty) : ty_(ty) {};
		EventType ty_;

		virtual ~Event() {};
	};

	class Entity;

	struct rbCollisionEnter : public Event {
	public:
		rbCollisionEnter(Entity* other) : Event(EventType::CollisionEnter) {
			other_ = other;
		}
		Entity* other_;
	};

	struct rbCollisionStay : public Event {
	public:
		rbCollisionStay(Entity* other) : Event(EventType::CollisionStay) {
			other_ = other;
		}
		Entity* other_;
	};

	struct rbCollisionExit : public Event {
	public:
		rbCollisionExit(Entity* other) : Event(EventType::CollisionExit) {
			other_ = other;
		}
		Entity* other_;
	};

	struct rbTriggerEnter : public Event {
	public:
		rbTriggerEnter(Entity* other) : Event(EventType::TriggerEnter) {
			other_ = other;
		}
		Entity* other_;
	};

	struct rbTriggerStay : public Event {
	public:
		rbTriggerStay(Entity* other) : Event(EventType::TriggerStay) {
			other_ = other;
		}
		Entity* other_;
	};

	struct rbTriggerExit : public Event {
	public:
		rbTriggerExit(Entity* other) : Event(EventType::TriggerExit) {
			other_ = other;
		}
		Entity* other_;
	};
}


#endif _EVENT_H