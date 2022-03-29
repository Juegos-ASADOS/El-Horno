#include "SceneManager.h"
#include "Scene.h"
#include "EventManager.h"
#include "Event.h"

#include <string>

#include <iostream>
#include "CheckMl.h"

SceneManager* SceneManager::instance = 0;

SceneManager::SceneManager() 
{ 
	try {

		currentScene_ = new Scene(); 
	}
	catch (std::string a) {
		std::cout << a;
	}
}

SceneManager* SceneManager::getInstance()
{
	return instance;
}

bool SceneManager::setupInstance()
{
	if (instance == 0) {
		instance = new SceneManager();
		return true;
	}
	return false;
}

void SceneManager::erase()
{
	delete instance;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene_;
}

Scene* SceneManager::loadScene(const std::string& sceneName)
{
	//COMENTADO POR EL USO DE JSON
	//json j /*= ResourceManager::getInstance()->loadSceneFile(sceneName)*/;

	currentScene_ = new Scene();
	//currentScene_->setupScene(j);

	//Creamos el evento de cambiar la escena?
	Event* changeSceneEvent = new Event(EventType::ChangeScene);

	EventManager::getInstance()->sendEvent(changeSceneEvent);

	return currentScene_;
}

void SceneManager::update()
{
	currentScene_->update();
}

void SceneManager::deleteEntities()
{
	currentScene_->deleteInstances();
}

SceneManager::~SceneManager()
{
	delete currentScene_;
	currentScene_ = nullptr;
}
