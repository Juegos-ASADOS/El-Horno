#include "Scene.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <OgreVector3.h>
//#include "CheckML.h"
#include "Transform.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Mesh.h"
#include "ParticleSystem.h"
#include "Rigibody.h"
#include "AudioComponent.h"
#include "AudioListenerComponent.h"
#include "AnimatorController.h"
#include "SinbadAnimTest.h"


#include "InputManager.h"
#include "btBulletCollisionCommon.h"

namespace El_Horno {
	Scene::Scene()
	{
		Entity* light = addEntity("light", "prueba");
		light->addComponent<Transform>("transform", Ogre::Vector3(0, 200, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0));
		light->addComponent<LightComponent>("light", 0, Ogre::Vector3(0, 0, 0));

		Entity* a = addEntity("camera", "prueba");
		Ogre::Vector3 p = { 10,10,10 };
		a->addComponent<Transform>("transform", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 0));
		a->addComponent<CameraComponent>("camera", Ogre::Vector3(0, 100, 450), Ogre::Vector3(0, 0, 0), Ogre::ColourValue(0, 0.3, 0.5), 5, 10000);
		a->addComponent<AudioListenerComponent>("audioListener");

		Entity* b = addEntity("object", "prueba");
		b->addComponent<Transform>("transform", Ogre::Vector3(0, 150, 0), Ogre::Vector3(0, 0, 0), p);
		b->addComponent<Mesh>("mesh", "Sinbad");
		b->addComponent<RigidBody>("rigidbody", 2.0f, false, false, 0);
		b->addComponent<AnimatorController>("animatorController");
		b->addComponent<SinbadAnimTest>("sinbadAnimTest");
		b->addComponent<AudioComponent>("audioComponent");

		b = addEntity("object2", "prueba");
		b->addComponent<Transform>("transform", Ogre::Vector3(0, -15, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(5, 0.1, 5));
		b->addComponent<Mesh>("mesh", "cube");
		b->addComponent<RigidBody>("rigidbody", 0.0f, false, false, 0);

		b = addEntity("esmoque", "prueba");
		b->addComponent<Transform>("transform", Ogre::Vector3(250, 10, 0), Ogre::Vector3(0, 0, 0), p/10);
		b->addComponent<ParticleSystem>("particleSystem", "smoke", "Smoke", 10, true);

		//// Sinbad cuidao ogro
		//Entity* c = addEntity("ogro", "prueba");
		//c->addComponent<Transform>("transform", Ogre::Vector3(100, 50, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(10, 10, 10));
		//c->addComponent<Mesh>("mesh", "Sinbad");
		//c->addComponent<AnimatorController>("animatorController");
		//c->addComponent<SinbadAnimTest>("sinbadAnimTest");
		//// doble sinbad de combate
		//Entity* d = addEntity("ogro", "prueba");
		//d->addComponent<Transform>("transform", Ogre::Vector3(-100, 50, 0), Ogre::Vector3(0, 0, 0), Ogre::Vector3(10, 10, 10));
		//d->addComponent<Mesh>("mesh", "Sinbad");
		//d->addComponent<AnimatorController>("animatorController");
		//d->addComponent<SinbadAnimTest>("sinbadAnimTest");
		
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

		Transform* tr = entities_.at("prueba")[2]->getComponent<Transform>("transform");
		RigidBody* rb = entities_.at("prueba")[2]->getComponent<RigidBody>("rigidbody");
		float speed = 100;

		rb->setAngularFactor(0);
		rb->setSleepingThresholds(0, 0);
		rb->setFriction(0.7);

		btVector3 force(0, 0, 0);
		if (InputManager::getInstance()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_A)) {
			force += btVector3(-speed, 0, 0);
			tr->setDirection({ 1,0,0 });
		}
		if (InputManager::getInstance()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_D)) {
			force += btVector3(speed, 0, 0);
			tr->setDirection({ -1,0,0 });
		}
		if (InputManager::getInstance()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_W)) {
			force += btVector3(0, 0, -speed);
			tr->setDirection({ 0,0,1 });
		}
		if (InputManager::getInstance()->IsKeyDown(SDL_Scancode::SDL_SCANCODE_S)) {
			force += btVector3(0, 0, speed);
			tr->setDirection({ 0,0,-1 });
		}

		force.setY(force.y() + rb->getLinearVelocity().y());
		rb->setLinearVelocity(force);

	}
}