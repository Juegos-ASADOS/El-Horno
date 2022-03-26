#include "UIElement.h"

#include <CEGUI/CEGUI.h>
#include "CheckMl.h"

UIElement::UIElement()
{

}

CEGUI::Window* UIElement::getElement()
{
	return elementInterface;
}

UIElement::~UIElement()
{

}

void UIElement::setPos(int x, int y)
{
	elementInterface->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
}

//No tocar estos 3 metodos
void UIElement::setSize(int x, int y)
{
	elementInterface->setSize(CEGUI::USize(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0)));
}

void UIElement::setText(const std::string& text)
{
	elementInterface->setText(text);
}

void UIElement::setAlpha(float valor)
{
	elementInterface->setAlpha(valor);
}


//POSICION RELATIVA [0,1]
float UIElement::getPosXscale()
{
	CEGUI::UVector2 v2 = elementInterface->getPosition();
	return (v2.d_x.d_scale);
}

float UIElement::getPosYscale()
{
	CEGUI::UVector2 v2 = elementInterface->getPosition();
	return (v2.d_y.d_scale);
}

//POSICION ABSOLUTA (A chol�n)
float UIElement::getPosXoffset()
{
	CEGUI::UVector2 v2 = elementInterface->getPosition();
	return (v2.d_x.d_offset);
}

float UIElement::getPosYoffset()
{
	CEGUI::UVector2 v2 = elementInterface->getPosition();
	return (v2.d_y.d_offset);
}

//No devuelvo el rect dividido porque no es publico, solo sus valores
float UIElement::getPivotCenterX()
{
	//Cogemos la parte de arriba izquierda y abajo derecha
	float i = elementInterface->getOuterRectClipper().d_min.d_x;
	float j = elementInterface->getOuterRectClipper().d_max.d_x;

	//Y hacemos media
	float x = (i + j) / 2;

	return x;
}

float UIElement::getPivotCenterY()
{
	//Reutilizamos variables
	float i = elementInterface->getOuterRectClipper().d_min.d_y;
	float j = elementInterface->getOuterRectClipper().d_max.d_y;

	//Y hacemos media
	float y = (i + j) / 2;

	return y;
}


float UIElement::getAlpha()
{
	return elementInterface->getAlpha();
}

CEGUI::Window* UIElement::getWindowElement()
{
	return elementInterface;
}

void UIElement::addChild(CEGUI::Window* windowChild)
{
	elementInterface->addChild(windowChild);
}

CEGUI::Window* UIElement::getChild(const std::string& namePath)
{
	return elementInterface->getChild(namePath);
}

CEGUI::Window* UIElement::getChildByIndex(int index)
{
	//VIGILAR ESTO CON EL GETCHILDCOUNT
	return elementInterface->getChildAtIdx(index);
}

bool UIElement::isActive()
{
	return elementInterface->isActive();
}

void UIElement::setActive(bool value)
{
	elementInterface->setVisible(value);
}