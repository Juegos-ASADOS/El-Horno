#pragma once
#ifndef _UI_MANAGER_H
#define _UI_MANAGER_H

class UIManager
{

private:
	UIManager();

	static UIManager* instance;


public:

	~UIManager();

	static UIManager* getInstance();
	static bool setupInstance();
	static void clean();

};

#endif _UI_MANAGER_H