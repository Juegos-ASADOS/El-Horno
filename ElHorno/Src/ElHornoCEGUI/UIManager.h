#pragma once
#ifndef _UI_MANAGER_H
#define _UI_MANAGER_H

#include <string>
#include <vector>

class UIElement;

namespace CEGUI {
	class Window;
	class OgreRenderer;
	class WindowManager;
}


namespace Ogre {
	class RenderWindow;
}

class UIManager
{

private:
	UIManager(Ogre::RenderWindow* renderWindow);

	static UIManager* instance;

	//Canvas +/-
	UIElement* root;

	CEGUI::WindowManager* winMngr;
	CEGUI::OgreRenderer* renderer;
	//Para diferenciar las capas
	std::vector<CEGUI::Window*> layouts;

public:

	~UIManager();

	static UIManager* getInstance();
	static bool setupInstance(Ogre::RenderWindow* window);
	static void clean();


	void createRoot();

	void changeScreenSize(int width,int height);
	//Para añadir los eventos a los botones
	//void setEvents(CEGUI::PushButton* button, CALLBACK DE FUNCION);

	void update();

	//Investigar si creat getpushbutton getStatic text y todo eso o si solo con el getWindow me sirve

	void changeText(CEGUI::Window* window,std::string text);

	void setMouseCursor(const std::string & imageFile);
	void showMouseCursor();
	void hideMouseCursor();

	//Eventos

	UIElement* getRoot();

	//Para coger la ventana que quieras
	CEGUI::Window* getWindow(const std::string & name);

	CEGUI::WindowManager* getWinMngr();
	void setVisibleLayout(bool visible, int layout);

	void changeAlpha(const std::string & image ,float alpha);
	float getAlpha(const std::string & namePath);


	std::vector<CEGUI::Window*> getLayouts();
};

#endif _UI_MANAGER_H