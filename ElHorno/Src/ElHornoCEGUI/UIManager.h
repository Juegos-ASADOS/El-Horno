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
	class DefaultWindow;
	class GUIContext;
}

namespace Ogre {
	class RenderWindow;
}

namespace El_Horno {
	class UIManager
	{

	private:
		UIManager(Ogre::RenderWindow* renderWindow);

		static UIManager* instance;

		CEGUI::WindowManager* winMngr;
		CEGUI::OgreRenderer* renderer;

		//HABRÁ QUE QUITAR ESTO E INFORMARSE DE LOS CEGUI::LAYOUTS
		std::vector<CEGUI::Window*> layouts;


		CEGUI::DefaultWindow* root;
		CEGUI::GUIContext* guiContext;
	public:

		~UIManager();

		static UIManager* getInstance();
		static bool setupInstance(Ogre::RenderWindow* window);
		void setUpResources();
		static void clean();

		void createRoot();
		void createContext();
		void deleteContext();
		//void shutdown?¿ cerrar el context y resetear la instancia?

		//INVESTIGAR FRAMEWINDOW
		void changeScreenSize(int width, int height);

		//Para añadir los eventos a los botones???
		//void setEvents(CEGUI::PushButton* button, CALLBACK DE FUNCION);

		void update();

		//Investigar si creat getpushbutton getStatic text y todo eso o si solo con el getWindow me sirve

		void changeText(CEGUI::Window* window, std::string text);

		void setMouseCursor(const std::string& imageFile);
		void showMouseCursor();
		void hideMouseCursor();


		CEGUI::DefaultWindow* getRoot();

		//Para coger la entidad que quieras
		CEGUI::Window* getWindow(const std::string& name);

		CEGUI::WindowManager* getWinMngr();

		//Habrá que modificarlo por el vector de windows provisional
		void setVisibleLayout(bool visible, int layout);
		std::vector<CEGUI::Window*> getLayouts();



		//Cambiar la transparencia de una entidad
		void changeAlpha(const std::string& image, float alpha);
		float getAlpha(const std::string& namePath);


	};
}

#endif _UI_MANAGER_H