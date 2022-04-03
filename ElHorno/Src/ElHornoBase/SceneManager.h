#pragma once
#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <string>


namespace El_Horno {
class Scene;

	class SceneManager
	{
	public:
		static SceneManager* getInstance();
		static bool setupInstance();
		static void erase();

		Scene* getCurrentScene();

		Scene* loadScene(const std::string& sceneName);
		void changeScene(const std::string& name);


		void start(std::string initialScene);
		void update();
		void deleteEntities();
		void setScene(Scene* newScene);
	private:
		static SceneManager* instance;

		Scene* currentScene_ = nullptr;

		SceneManager();
		~SceneManager();

		std::string nextScene_ = "";
	};
}
#endif _SCENE_MANAGER_H