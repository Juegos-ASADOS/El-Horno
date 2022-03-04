#pragma once
#include <vector>
#include "Entity.h"

using namespace std;

//class Entity;

class Scene
{
private:
	vector<Entity*> entities;

public:
	Scene() {};
	~Scene();

	virtual void start() {};		
	virtual void update() {};
	virtual void render() {};
};

