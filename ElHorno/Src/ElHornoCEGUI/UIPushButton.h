#pragma once
#ifndef _UI_PUSH_BUTTON_H
#define _UI_PUSH_BUTTON_H

#include "UIElement.h"
#include "Component.h"

namespace CEGUI {
	class PushButton;
	class WindowManager;
	class DefaultWindow;
}

namespace El_Horno {
	class _declspec(dllexport) UIPushButton : public UIElement, public Component
	{
	private:
		CEGUI::PushButton* boton;
		std::string schemeName_;
	public:
		UIPushButton(std::string schemeName, float posX, float posY, float sizeX, float sizeY, std::string name_);
		UIPushButton() {}

		void start();


		void isPushed();
		void addEvent(std::string evento);

		virtual ~UIPushButton();
	};
}
#endif _UI_PUSH_BUTTON_H