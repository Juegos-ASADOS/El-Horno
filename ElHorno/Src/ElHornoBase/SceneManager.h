#pragma once
#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include <string>
#include <map>
#include <vector>


namespace El_Horno {
class Scene;
class Component;

typedef Scene* (*SceneLoad)();
typedef void (*GameVoid)();

	class _declspec(dllexport) SceneManager
	{
	public:
		static SceneManager* getInstance();
		static bool setupInstance();
		static void erase();

		Scene* getCurrentScene();
		bool getChangeScene();

		Scene* loadScene(const std::string& sceneName);

		//TODO
		void changeScene();
		void nextScene(std::string s);

		//TODO
		void start(std::string initialScene);
		void preUpdate();
		void update();
		void deleteEntities();
		void setScene(Scene* newScene);
		std::map<std::string, Component* (*)()> getComponents();

		template<typename T>
		static Component* createComponent() {
			return new T();
		}

		template<typename T>
		static Scene* addScene() {
			return new T();
		}

		std::map<std::string, Component* (*)()> possibleComponents;
		std::map<std::string, Scene* (*)()> allScenes;
	private:
		static SceneManager* instance_;

		Scene* currentScene_ = nullptr;

		SceneManager();
		~SceneManager();

		std::string nextSceneName_ = "";
		Scene* nextScene_ = nullptr;
		bool changeScene_ = false;

	};
}
#endif _SCENE_MANAGER_H