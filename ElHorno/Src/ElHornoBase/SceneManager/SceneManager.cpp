#include "SceneManager.h"


SceneManager* SceneManager::getInstance()
{
	if (instance == 0)
		return nullptr;

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


SceneManager::~SceneManager()
{
}
