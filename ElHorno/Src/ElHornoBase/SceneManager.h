#pragma once
#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <string>


namespace El_Horno {
class Scene;

typedef Scene* (*SceneLoad)();

	class SceneManager
	{
	public:
		static SceneManager* getInstance();
		static bool setupInstance();
		static void erase();

		Scene* getCurrentScene();

		Scene* loadScene(const std::string& sceneName);

		//TODO
		void changeScene(const std::string& name);

		//TODO
		void start(std::string initialScene);
		void preUpdate();
		void update();
		void deleteEntities();
		void setScene(Scene* newScene);
	private:
		static SceneManager* instance_;

		Scene* currentScene_ = nullptr;

		SceneManager();
		~SceneManager();

		std::string nextScene_ = "";
	};
}
#endif _SCENE_MANAGER_H