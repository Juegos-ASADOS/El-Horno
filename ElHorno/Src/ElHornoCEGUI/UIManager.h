#pragma once
#ifndef _UI_MANAGER_H
#define _UI_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "LuaManager.h"

namespace CEGUI {
	class Window;
	class OgreRenderer;
	class WindowManager;
	class DefaultWindow;
	class GUIContext;
	class UDim;
	class EventArgs;
}

namespace Ogre {
	class RenderWindow;
}

namespace El_Horno {
	class _declspec(dllexport) UIManager
	{

	private:
		UIManager();

		static UIManager* instance_;

		CEGUI::WindowManager* winMngr;
		CEGUI::OgreRenderer* renderer;

		CEGUI::Window* root = nullptr;
		CEGUI::GUIContext* guiContext;


		std::unordered_map<std::string, CEGUI::Window*> layouts;
	public:

		~UIManager();

		static UIManager* getInstance();
		static bool setupInstance();
		void setUpResources();
		static void erase();

		void createRoot();
		void createContext();
		void deleteContext();

		void defineScheme(std::string schemeName);

		void removeLayoutRoot();

		CEGUI::Window* loadLayout(std::string layoutName, std::string name = "");
		CEGUI::Window* createLayout(std::string layoutName, std::string name = "");

		void setRootLayout(CEGUI::Window* nRoot);
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

		void setFont(const std::string& font);

		CEGUI::Window* createWidget(const std::string& type, const std::string& name = "");
		void setWidgetDestRect(CEGUI::Window* wnd, const CEGUI::UDim& pos, const CEGUI::UDim& relativePos, const CEGUI::UDim& size, const CEGUI::UDim& relativeSize);

		CEGUI::Window* getRoot();

		//Para coger la entidad que quieras
		CEGUI::Window* getWindow(const std::string& name);
		CEGUI::WindowManager* getWinMngr();

		CEGUI::GUIContext* getContext() { return guiContext; };

		//Cambiar la transparencia de una entidad
		void changeAlpha(const std::string& image, float alpha);
		float getAlpha(const std::string& namePath);





		//todo a aprtir de aqui es para layouts y widgets y lo que se expone a Lua principalmente
		void setLayoutVisibility(std::string layoutName, bool visible);

		void subscribeLayoutChildVisibility(std::string layoutName, std::string childName, bool visible);

		void addLayout(std::string layoutName, std::string name = "");
		void removeLayout(std::string layoutName);

		void removeLayouts();
		//define scheme;


		void setLayoutScale(std::string layoutName, float x, float y);

		void subscribeLayoutChildEvent(std::string layoutName, std::string childName, std::function<bool(const CEGUI::EventArgs&)> func);
		void subscribeChildEvent(std::string childName, std::function<bool(const CEGUI::EventArgs&)> func);


		void addImageFile(const std::string& imageName, const std::string& imageFile);

		void addWidgetToLayout(const std::string& layoutName, const std::string& childName, const std::string& widgetType);
		void removeWidgetFromLayout(const std::string& layoutName, const std::string& childPath);

		void setChildProperty(const std::string& layoutName, const std::string& childPath, const std::string& propertyName, const std::string& values);

		CEGUI::Window* getLayout(std::string layoutName);
	};
}

#endif _UI_MANAGER_H