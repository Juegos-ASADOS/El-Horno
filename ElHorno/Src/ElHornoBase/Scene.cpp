#include "Scene.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <OgreVector3.h>

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
	Ogre::Vector3 p = { 1,1,1 };
	a->addComponent("transform", p,p,p);
	a->addComponent("CameraComponent");

	Entity* b = addEntity("object", "prueba");
	b->addComponent(comp[0]);
	b->addComponent(comp[2]);
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

/*
Recorre las layers y sus entidades hasta encontrar la entidad
de nombre "name", entonces la añade al vector de entidades a
destruir.

Devuelve false si no la encuentra
*/
bool Scene::deleteEntity(const std::string& name)
{
	// Recorre layers
	auto it = entities_.begin();
	while (it != entities_.end()) {
		// Recorre vector de entidades
		for (int i = 0; i < it->second.size(); i++) {
			Entity* ent = it->second[i];

			if (ent->getName() == name) {
				// Mete la entidad al vector de entidades a destruir
				entitiesToDestroy_.push_back({ it->first, ent });
				return true;
			}
		}
	}

	return false;
}

/*
Elimina las entidades del vector a de entidades a destruir y
las borra de los vectores pertinentes
*/
void Scene::deleteInstances()
{
	// Elementos a borrar
	for (int i = 0; i < entitiesToDestroy_.size(); i++)
	{
		if (entitiesToDestroy_[i].second->dontDestroyOnLoad) {
			entitiesToDestroy_.erase(entitiesToDestroy_.begin() + i);
			i--;
			continue;
		}

		// Obtiene la layer
		auto it = entities_.find(entitiesToDestroy_[i].first);

		if (it != entities_.end()) {
			int e = 0;
			bool found = false;

			// Busca la entidad a borrar
			while (e < it->second.size() && !found) {

				// Si la encuentra, se elimina en ambos vectores
				if (it->second[e] == entitiesToDestroy_[i].second) {
					delete it->second[e];

					entitiesToDestroy_.erase(entitiesToDestroy_.begin() + i);
					it->second.erase(it->second.begin() + e);

					i--;
					found = true;
				}
				e++;
			}
		}
	}
}

void Scene::start()
{
	auto iter = entities_.begin();
	while (iter != entities_.end()) {
		for (Entity* e : iter->second)
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
