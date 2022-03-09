#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>

class Entity;

class Component
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

	virtual void start() {};		
	virtual void update() {};
	virtual void render() {};

	virtual void onEnable() {};
	virtual void onDisable() {};

	inline std::string getName() { return name_; };
	inline void setName(std::string n) { name_ = n; };
};

#endif _COMPONENT_H