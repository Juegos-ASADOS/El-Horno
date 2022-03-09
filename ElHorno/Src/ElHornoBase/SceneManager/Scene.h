#pragma once

//ELIMINAR INCLUDES
#include <string>
#include "../json.hpp"

using json = nlohmann::json;

class Entity;
class Scene
{
public:
	Scene();
	~Scene();

	void setupScene(json& j);
	void setupProcess(json& j);

	Entity* getEntity(const std::string& name);
	
	//No se como hacer estas vainas
	Entity* createEntity(json& j);
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
