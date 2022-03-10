#include "Scene.h"

#include "Entity.h"


//TODO REVISAR QUE ES UN UNIQUE_LOCK Y TODAS ESTAS VAINAS
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

Scene::Scene()
{
}

//TODO Destruir VierwPorts y cámaras lo primero de todo
Scene::~Scene()
{
	std::map<std::string, Entity*> dontDelete;
	for (std::pair<std::string, Entity*> i : entities) {
		if (!i.second->dontDestroyOnLoad)
			delete i.second;
		else
			dontDelete.insert(i);
	}
	entities.clear();

	//Metemos las entidades que decidimos NO borrar
	for (std::pair<std::string, Entity*> i : dontDelete)
	{
		entities.insert(i);
	}
	dontDelete.clear();
}

void Scene::setupScene(nlohmann::json& j)
{	
	std::unique_lock<std::mutex> lck(mtx);
	setupProcess(j);
	while (!sceneLoaded) cv.wait(lck);
	sceneLoaded = false;
	//ElHornoBase::getInstance()->resetTimer();
}

Entity* Scene::getEntity(const std::string& name)
{
	std::map<std::string, Entity*>::iterator entity = entities.find(name);
	if (entity == entities.end())
		return nullptr;
	else
		return entity->second;
}

void Scene::start()
{
}

void Scene::update()
{
	for(std::pair<std::string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->update();
	}
}
