#pragma once
#ifndef _UI_ELEMENT_H
#define _UI_ELEMENT_H

#include <string>
#include <Component.h>
namespace CEGUI {
	class Window;
	class WindowManager;
	class DefaultWindow;
}

namespace El_Horno {
	class UIElement : Component
	{
	private:

		//Entidad de la interfaz
		CEGUI::Window* elementInterface;

		int posX;
		int posY;
		int sizeX;
		int sizeY;
	protected:
		UIElement(int posX, int posY, int sizeX, int sizeY, std::string name_);
		void init();

		std::string name;



		void setElementInterface(CEGUI::Window* elem);
		CEGUI::Window* const getElement()&;
		virtual ~UIElement();

		//Metodos iguales que una entidad/transform

		void setPos(int x, int y);
		void setSize(int x, int y);
		void setText(const std::string& text);

		//Transparencia del objeto
		void setAlpha(float valor);

		//GETTERS
		float getPosXscale();
		float getPosYscale();
		float getPosXoffset();
		float getPosYoffset();
		//------------------


		float getPivotCenterX();
		float getPivotCenterY();

		float getAlpha();

		CEGUI::Window* getWindowElement();

		void addChild(CEGUI::Window* windowChild);
		CEGUI::Window* getChild(const std::string& childNamePath);
		CEGUI::Window* getChildByIndex(int index);

		bool isActive();
		void setActive(bool valor);
	};
}
#endif _UI_ELEMENT_H