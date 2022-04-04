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

	class UIPushButton : public UIElement
	{
	private:
		CEGUI::PushButton* boton;
	protected:
		UIPushButton(std::string& schemeName,int posX,int posY, int sizeX,int sizeY, std::string name_);

		void isPushed();

		virtual ~UIPushButton();
	};
}
#endif _UI_PUSH_BUTTON_H