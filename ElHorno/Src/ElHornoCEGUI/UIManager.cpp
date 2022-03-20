#include "UIManager.h"

//#include <CEGUI/CEGUI.h>

UIManager* UIManager::instance = 0;

UIManager::UIManager()
{
	
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{
	return instance;
}


bool UIManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new UIManager();
		return true;
	}

	return false;
}

void UIManager::clean()
{
	delete instance;
}
