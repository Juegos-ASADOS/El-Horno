#include "Scene.h"
#include "Entity.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

Scene::Scene()
{
	json j;
	std::ifstream i("Assets/componentsConfig.json");
	if (i.is_open()) {
		i >> j;
		i.close();
	}
	else {
		throw "File not found: Assets/componentsConfig.json \n";
	}

	std::vector<json> comp = j["components"];

	Entity* a = addEntity("camera", "prueba");
	a->addComponent(comp[0]);
	a->addComponent(comp[1]);

	Entity* b = addEntity("object", "prueba");
	b->addComponent(comp[0]);
	//b->addComponent(comp[2]);
}

//TODO Destruir VierwPorts y cámaras lo primero de todo
Scene::~Scene()
{
	std::map<std::string, Entity*> dontDelete;
	auto it = entities_.begin();
	while (it != entities_.end()) {
		for (auto e : it->second) {
			if (!e->dontDestroyOnLoad)
				delete e;
			else
				dontDelete.insert({ it->first, e });
		}
		it++;
	}
	entities_.clear();

	//Metemos las entidades que decidimos NO borrar
	for (std::pair<std::string, Entity*> i : dontDelete)
	{
		addEntity(i.second->getName(), i.first);
	}
	dontDelete.clear();
}

Entity* Scene::getEntity(const std::string& name, const std::string& layer)
{
	std::map<std::string, std::vector<Entity*>>::iterator entity = entities_.find(layer);
	if (entity == entities_.end())
		return nullptr;
	else {
		for (Entity* e : entity->second)
			if (e->getName() == name) return e;
		return nullptr;
	}
}

Entity* Scene::addEntity(const std::string& name, const std::string& layer)
{
	Entity* e = new Entity(name, this);
	auto it = entities_.find(layer);
	if (it != entities_.end())
		it->second.push_back(e);
	else {
		std::vector<Entity*> a = std::vector<Entity*>();
		a.push_back(e);
		entities_.insert(std::pair<std::string, std::vector<Entity*>>(layer, a));
	}

	return e;
}

void Scene::start()
{
	auto iter = entities_.begin();
	while (iter != entities_.end()) {
		for(Entity* e : iter->second)
			if (e->isActive()) e->start();
		iter++;
	}
}

void Scene::update()
{
	auto iter = entities_.begin();
	while (iter != entities_.end()) {
		for (Entity* e : iter->second)
			if (e->isActive()) e->update();
		iter++;
	}
}
