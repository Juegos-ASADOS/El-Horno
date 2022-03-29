#include "Scene.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <OgreVector3.h>
#include "CheckML.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Mesh.h"
#include "ParticleSystem.h"
#include "Rigibody.h"
#include "AudioComponent.h"
#include "AudioListenerComponent.h"

Scene::Scene()
{
	Entity* light = addEntity("light", "prueba");
	light->addComponent<Transform>("transform", Ogre::Vector3(0, 200, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0));
	light->addComponent<El_Horno::LightComponent>("light", 0, Ogre::Vector3(0, 0, 0));

	Entity* a = addEntity("camera", "prueba");
	Ogre::Vector3 p = { 1,1,1 };
	a->addComponent<Transform>("transform", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0));
	a->addComponent<El_Horno::CameraComponent>("camera", Ogre::Vector3(0, 220, 550), Ogre::Vector3(0, 0, 0), Ogre::ColourValue(0, 0.3, 0.5), 5, 10000);
	a->addComponent<El_Horno::AudioListenerComponent>("audioListener");

	Entity* b = addEntity("object", "prueba");
	b->addComponent<Transform>("transform", Ogre::Vector3(0, 50, 0), Ogre::Vector3(180, 0, 0), p);
	b->addComponent<Mesh>("mesh", "ogrehead");
	b->addComponent<El_Horno::RigidBody>("rigidbody", 2.0f, false, 0);
	b->addComponent<El_Horno::AudioComponent>("audioComponent");

	b = addEntity("object2", "prueba");
	b->addComponent<Transform>("transform", Ogre::Vector3(0, -15, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(5, 0.1, 5));
	b->addComponent<Mesh>("mesh", "cube");
	b->addComponent<El_Horno::RigidBody>("rigidbody", 0.0f, false, 0);

	b = addEntity("esmoque", "prueba");
	b->addComponent<Transform>("transform", Ogre::Vector3(0, 50, 0), Ogre::Vector3(0, 0, 0), p);
	b->addComponent<El_Horno::ParticleSystem>("particleSystem", "smoke", "Smoke", 50000, false);
}

//TODO Destruir VierwPorts y c�maras lo primero de todo
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
	if (layer != "" && entity == entities_.end())
		return nullptr;
	else {
		if (layer == "") {
			for (auto a : entities_) {
				for (Entity* e : a.second)
					if (e->getName() == name) return e;
			}
		}
		else {
			for (Entity* e : entity->second)
				if (e->getName() == name) return e;
		}
		return nullptr;
	}
}

Entity* Scene::addEntity(const std::string& name, const std::string& layer, const std::string& group)
{
	Entity* e = new Entity(name, this);
	e->setGroup(group);

	//Seleccion de layer de renderizado
	auto it = entities_.find(layer);
	if (it != entities_.end())
		it->second.push_back(e);
	else {
		std::vector<Entity*> a = std::vector<Entity*>();
		a.push_back(e);
		entities_.insert(std::pair<std::string, std::vector<Entity*>>(layer, a));
	}

	//Seleccion de grupo de entidades(default por defecto)
	auto i = entitiesGroups_.find(group);
	if (i != entitiesGroups_.end())
		i->second.push_back(e);
	else {
		std::vector<Entity*> b = std::vector<Entity*>();
		//b.push_back(e);
		//entitiesGroups_.insert(std::pair<std::string, std::vector<Entity*>>(group, b));
	}
	return e;
}

/*
Recorre las layers y sus entidades hasta encontrar la entidad
de nombre "name", entonces la a�ade al vector de entidades a
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
