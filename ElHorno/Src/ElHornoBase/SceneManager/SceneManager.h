#pragma once

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

private:
	static SceneManager* instance;

	Scene* currentScene_ = nullptr;

	SceneManager() {};
	~SceneManager();

	std::string nextScene_ = "";
};
