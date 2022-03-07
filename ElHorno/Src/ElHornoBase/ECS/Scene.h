#pragma once
#include <map>
#include "Entity.h"

using namespace std;

//class Entity;

class Scene
{
private:
	//La idea es dividir las entidades en capas(serían la key del map)
	map<string, Entity*> entities;

public:
	Scene();
	~Scene();

	virtual void start() {};		
	virtual void update() {};
	virtual void render() {};
};

