#pragma once
class Entity;

class Component
{
private:
	bool active_;
	Entity* entity_;
public:
	Component() : entity_(nullptr), active_(true) {};
	~Component();

	inline void setEntity(Entity* e) { entity_ = e; };
	inline Entity* getEntity() { return entity_; };

	void setActive(bool a);
	inline bool isActive() { return active_; };

	virtual void start() {};		//VER SI QUEREMOS HACER UN START EN ENTITY PARA HACERLO AL FINAL DE LA CREACION DE ENTIDADES
	virtual void update() {};
	virtual void render() {};

	virtual void onEnable() {};
	virtual void onDisable() {};
};

