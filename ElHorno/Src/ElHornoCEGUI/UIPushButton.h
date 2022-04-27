#pragma once
#ifndef _UI_PUSH_BUTTON_H
#define _UI_PUSH_BUTTON_H

#include "UIElement.h"

namespace CEGUI {
	class RadioButton;
}

namespace El_Horno {
	class _declspec(dllexport) UIPushButton : public UIElement
	{
	private:
		CEGUI::RadioButton* boton;
		std::string schemeName_;
	public:
		UIPushButton(std::string schemeName, float posX, float posY, float sizeX, float sizeY, std::string name_);
		UIPushButton() {}

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start();
		void isPushed();
		void addEvent(std::string evento);

		virtual ~UIPushButton();
	};
}
#endif _UI_PUSH_BUTTON_H