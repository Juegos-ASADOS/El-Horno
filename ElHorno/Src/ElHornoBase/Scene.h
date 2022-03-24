#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include <string>
#include "json.hpp"

class Entity;
class Scene
{
public:
	Scene();
	~Scene();

	void setupScene(nlohmann::json& j) {};
	void setupProcess(nlohmann::json& j) {};

	Entity* getEntity(const std::string& name, const std::string& layer);
	
	Entity* addEntity(const std::string& name, const std::string& layer);

	bool deleteEntity(const std::string& name);
	void deleteInstances();

	void start();
	void update();

	inline std::string getName() const { return name_; };

private:
	std::map<std::string, std::vector<Entity*>> entities_;
	std::vector<std::pair<std::string, Entity*>> entitiesToDestroy_;

	std::string name_;
	bool sceneLoaded_ = false;
	int addedEntitiesCounter_ = 0;

	//Buscar entidades por tag? , Eliminar/crear entidades e instancias, Crear en la entidad physicsUpdate,pausedUpdates etc...
};

#endif _SCENE_H