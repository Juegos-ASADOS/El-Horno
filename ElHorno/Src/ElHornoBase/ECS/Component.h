#pragma once
class Entity;

class Component
{
public:
	void setEntity(Entity* e);
	void init();
	bool isActive();
	void update();
	void render();
};

