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

	void setupScene(nlohmann::json& j);
	void setupProcess(nlohmann::json& j);

	Entity* getEntity(const std::string& name);
	
	//No se como hacer estas vainas
	Entity* createEntity(nlohmann::json& j);
	Entity* addEntity(std::string name, std::string tag = "Untagged", bool callStart = true);
	bool deleteEntity(const std::string name);
	void deleteInstances();

	void start();
	void update();

	inline std::string getName() const { return name; };

private:
	std::map<std::string, Entity*> entities;

	std::string name;
	bool sceneLoaded = false;
	int addedEntitiesCounter = 0;

	//Buscar entidades por tag? , Eliminar/crear entidades e instancias, Crear en la entidad physicsUpdate,pausedUpdates etc...
};

#endif _SCENE_H