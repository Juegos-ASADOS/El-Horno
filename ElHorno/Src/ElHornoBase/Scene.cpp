#include "Scene.h"
#include "Entity.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Scene::Scene()
{
	json j;
	std::ifstream i("../../Exes/Assets/componentsConfig.json");
	if (i.is_open()) {
		i >> j;
		i.close();
	}
	else {
		throw "File not found: .. / .. / Exes / Assets / componentsConfig.json \n";
	}

	std::vector<json> comp = j["components"];

	Entity* a = addEntity("camera", "prueba");
	a->addComponent(comp[0]);
	a->addComponent(comp[1]);
	
	Entity* b = addEntity("object", "prueba");
	b->addComponent(comp[0]);
	b->addComponent(comp[2]);
}

//TODO Destruir VierwPorts y cámaras lo primero de todo
Scene::~Scene()
{
	std::map<std::string, Entity*> dontDelete;
	for (std::pair<std::string, Entity*> i : entities_) {
		if (!i.second->dontDestroyOnLoad)
			delete i.second;
		else
			dontDelete.insert(i);
	}
	entities_.clear();

	//Metemos las entidades que decidimos NO borrar
	for (std::pair<std::string, Entity*> i : dontDelete)
	{
		entities_.insert(i);
	}
	dontDelete.clear();
}

Entity* Scene::getEntity(const std::string& name)
{
	std::map<std::string, Entity*>::iterator entity = entities_.find(name);
	if (entity == entities_.end())
		return nullptr;
	else
		return entity->second;
}

Entity* Scene::addEntity(std::string name, std::string layer)
{
	Entity* e = new Entity(name, this);
	entities_.insert({ layer, e });

	return e;
}

void Scene::start()
{
}

void Scene::update()
{
	for (std::pair<std::string, Entity*> e : entities_) {
		if (e.second->isActive()) e.second->update();
	}
}
