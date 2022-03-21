#pragma once
#ifndef _UI_ELEMENT_H
#define _UI_ELEMENT_H

#include <string>

namespace CEGUI {
	class Window;
}

class UIElement
{

private:
	UIElement(CEGUI::Window* window);

	//Entidad de la interfaz
	CEGUI::Window* elementInterface;
public:

	CEGUI::Window* getElement();
	~UIElement();

	//Metodos iguales que una entidad/transform

	void setPos(int x, int y);
	void setSize(int x,int y);
	void setText(const std::string & text);

	//Transparencia del objeto
	void setAlpha(float valor);

	//GETTERS
	float getPosXscale();
	float getPosYscale();
	float getPosXoffset();
	float getPosYoffset();
	float getPivotCenterX();
	float getPivotCenterY();

	float getAlpha();


	void addChild(CEGUI::Window* windowChild);
	UIElement getChild(const std::string & childNamePath);
	UIElement getChildByIndex(int index);

	bool isActive();
	void setActive(bool valor);

	//Hacemos como las entidades y le metemos hijos y que hereden de un padre X?
	//Hay metodos en Cegui que sirven para saber facilmete si una ventana es objeto de otra etc
};

#endif _UI_ELEMENT_H