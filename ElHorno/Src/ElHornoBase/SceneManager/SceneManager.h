#pragma once

#include <vector>
#include <queue>

class SceneManager
{
public:

	static SceneManager* getInstance();
	static bool setupInstance();
	static void erase();



private:

	static SceneManager* instance;

	SceneManager() {};
	~SceneManager();

};
