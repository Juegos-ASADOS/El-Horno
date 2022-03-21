#include "UIElement.h"

#include <CEGUI/CEGUI.h>

UIElement::UIElement(CEGUI::Window* window)
{
	elementInterface = window;
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

void UIElement::setSize(int x, int y)
{
	CEGUI::USize v2 = elementInterface->getSize();
	elementInterface->setSize(v2);
}

void UIElement::setText(const std::string& text)
{
	elementInterface->setText(text);
}

void UIElement::setAlpha(float valor)
{
	elementInterface->setAlpha(valor);
}

float UIElement::getPosXscale()
{
	return 0.0f;
}

float UIElement::getPosYscale()
{
	return 0.0f;
}

float UIElement::getPosXoffset()
{
	return 0.0f;
}

float UIElement::getPosYoffset()
{
	return 0.0f;
}

bool UIElement::isActive()
{
	return elementInterface->isActive();
}

void UIElement::setActive(bool value)
{
	elementInterface->setVisible(value);
}
