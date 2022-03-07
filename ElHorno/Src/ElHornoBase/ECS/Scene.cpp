#include "Scene.h"


Scene::Scene() : entities()
{

}

Scene::~Scene()
{
	for (Entity* e : entities)
		delete e;
}

void Scene::update()
{
	for (Entity* e : entities)
		e->update();
}

void Scene::render()
{
	for (Entity* e : entities)
		e->render();
}

