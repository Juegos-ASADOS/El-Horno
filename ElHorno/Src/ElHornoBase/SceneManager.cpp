#include "SceneManager.h"
#include "Scene.h"
#include "EventManager.h"
#include "Event.h"
#include "Transform.h"
#include "Mesh.h"

#include <string>

#include <iostream>
#include "CheckML.h"

namespace El_Horno {

	SceneManager* SceneManager::instance_ = 0;

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
		return instance_;
	}

	bool SceneManager::setupInstance()
	{
		if (instance_ == 0) {
			instance_ = new SceneManager();
			return true;
		}
		return false;
	}

	void SceneManager::erase()
	{
		delete instance_;
	}

	Scene* SceneManager::getCurrentScene()
	{
		return currentScene_;
	}

	Scene* SceneManager::loadScene(const std::string& sceneName)
	{
		currentScene_ = new Scene();

		//TODO
		//Creamos el evento de cambiar la escena??
		Event* changeSceneEvent = new Event(EventType::ChangeScene);

		EventManager::getInstance()->sendEvent(changeSceneEvent);

		return currentScene_;
	}

	void SceneManager::preUpdate()
	{
		currentScene_->preUpdate();
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

	void SceneManager::setScene(Scene* newScene) {
		delete currentScene_;
		currentScene_ = newScene;
		//possibleComponents.emplace("Transform", new Transform());
		//possibleComponents.emplace("Mesh", new Mesh());
	}
	std::map<std::string, Component* (*)()> SceneManager::getComponents()
	{
		return possibleComponents;
	}
}