#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include <vector>
#include "EventListener.h"

namespace El_Horno {
	class Entity;

	class _declspec(dllexport) Component : public EventListener
	{
	protected:
		bool active_;
		Entity* entity_;
		std::string name_;
	public:
		Component() : entity_(nullptr), active_(true) {};
		~Component();

		inline void setEntity(Entity* e) { entity_ = e; };
		inline Entity* getEntity() { return entity_; };

		void setActive(bool a);
		inline bool isActive() { return active_; };

		virtual void setParameters(std::vector<std::pair<std::string, std::string>> parameters) {};
		virtual void start() {};	//Esto es el init de nuestros componentes
		virtual void preUpdate() {};
		virtual void update() {};
		virtual void render() {};

		virtual void onEnable() {};
		virtual void onDisable() {};
		virtual bool recieveEvent(Event* e) { return false; };

		inline std::string getName() { return name_; };
		inline void setName(std::string n) { name_ = n; };
	};
}
#endif _COMPONENT_H