#pragma once
#ifndef _UI_PUSH_BUTTON_H
#define _UI_PUSH_BUTTON_H

#include "UIElement.h"

namespace CEGUI {
	class Window;
}

class UIPushButton : public UIElement
{
protected:
	UIPushButton();

	virtual ~UIPushButton();
};

#endif _UI_PUSH_BUTTON_H