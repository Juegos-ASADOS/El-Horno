#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include "json.hpp"
#include "EventListener.h"

class Entity;

class Component : EventListener
{
protected:
	bool active_;
	Entity* entity_;
	std::string name_;
	nlohmann::json& args_;
public:
	Component(nlohmann::json& args) : args_(args), entity_(nullptr), active_(true) {};
	~Component();

	inline void setEntity(Entity* e) { entity_ = e; };
	inline Entity* getEntity() { return entity_; };

	void setActive(bool a);
	inline bool isActive() { return active_; };

	virtual void start() {};	//Esto es el init de nuestros componentes
	virtual void update() {};
	virtual void render() {};

	virtual void onEnable() {};
	virtual void onDisable() {};

	inline std::string getName() { return name_; };
	inline void setName(std::string n) { name_ = n; };
};

#endif _COMPONENT_H