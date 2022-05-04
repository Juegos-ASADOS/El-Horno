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

	bool SceneManager::getChangeScene()
	{
		return changeScene_;
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

	void SceneManager::changeScene()
	{
		changeScene_ = false;
		currentScene_->deleteAllExcepDontDestroyOnLoad();
		nextScene_->setEntitiesMap(currentScene_->getEntitesMap());
		El_Horno::SceneManager::getInstance()->setScene(nextScene_);
		currentScene_->init(nextSceneName_);
		currentScene_->awake();
		currentScene_->start();
		std::cout << "hola\n";
	}

	void SceneManager::nextScene(std::string s)
	{
		auto it = allScenes.find(s);
		nextScene_ = (it->second)();;
		nextSceneName_ = s;
		changeScene_ = true;
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
	}
	std::map<std::string, Component* (*)()> SceneManager::getComponents()
	{
		return possibleComponents;
	}
}