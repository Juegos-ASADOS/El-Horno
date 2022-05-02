#include "Scene.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <OgreVector.h>

//ESTO DEBERIA QUITARSE DE AQUI
#include "LightComponent.h" 
#include "AnimatorController.h"
#include "UILayout.h"

namespace El_Horno {
	Scene::Scene()
	{	
	}

	//TODO Destruir VierwPorts y camaras lo primero de todo
	Scene::~Scene()
	{
		auto it = entities_.begin();
		while (it != entities_.end()) {
			for (auto e : it->second) {
				delete e;
			}
			it++;
		}
		entities_.clear();
	}

	//devuelve la entidad por el nombre y su layer
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

	//agrega una entidad a una layer de renderizado y grupo
	Entity* Scene::addEntity(const std::string& name, const std::string& layer, Entity* parent, const std::string& group)
	{
		Entity* e = new Entity(name, this, parent);
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
			b.push_back(e);
			entitiesGroups_.insert(std::pair<std::string, std::vector<Entity*>>(group, b));
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
					for (Entity* e : ent->getChildren())
						deleteEntity(e->getName());
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

	void Scene::deleteAllExcepDontDestroyOnLoad()
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

	void Scene::awake()
	{
		auto iter = entities_.begin();
		while (iter != entities_.end()) {
			for (Entity* e : iter->second)
				e->awake(); //Se llama aunque esté desactivada
			iter++;
		}
	}

	void Scene::start()
	{
		auto iter = entities_.begin();
		while (iter != entities_.end()) {
			for (Entity* e : iter->second)
				e->start();
			iter++;
		}
	}

	void Scene::preUpdate()
	{
		auto iter = entities_.begin();
		while (iter != entities_.end()) {
			for (Entity* e : iter->second)
				if (e->isActive()) e->preUpdate();
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
}