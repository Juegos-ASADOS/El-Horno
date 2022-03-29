#pragma once
#ifndef _UI_ELEMENT_H
#define _UI_ELEMENT_H

#include <string>
#include <Component.h>
namespace CEGUI {
	class Window;
}


namespace El_Horno {
	//AHORA LA UIElement hereda de Component
	class UIElement : Component
	{
	protected:
		UIElement();

		//Entidad de la interfaz
		CEGUI::Window* elementInterface;

		CEGUI::Window* getElement();
		virtual ~UIElement();

		//Metodos iguales que una entidad/transform

		//ELIMINAR ESTAS VAINAS


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