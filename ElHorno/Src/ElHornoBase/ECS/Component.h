#pragma once
#include <string>

using namespace std;

class Entity;

class Component
{
private:
	bool active_;
	Entity* entity_;
	string name_;
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

	inline string getName() { return name_; };
	inline void setName(string n) { name_ = n; };
};