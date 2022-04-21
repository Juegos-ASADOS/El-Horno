#pragma once
#ifndef _UI_PUSH_BUTTON_H
#define _UI_PUSH_BUTTON_H

#include "UIElement.h"

namespace CEGUI {
	class PushButton;
	class WindowManager;
	class DefaultWindow;
}

namespace El_Horno {
	class _declspec(dllexport) UIPushButton : public UIElement
	{
	private:
		CEGUI::PushButton* boton;
	protected:
		UIPushButton(std::string& schemeName, float posX, float posY, float sizeX, float sizeY, std::string name_);

		void isPushed();

		virtual ~UIPushButton();
	};
}
#endif _UI_PUSH_BUTTON_H