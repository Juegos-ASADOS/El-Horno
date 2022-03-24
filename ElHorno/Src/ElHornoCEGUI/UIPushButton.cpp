#include "UIPushButton.h"
#include "UIManager.h"
#include <CEGUI/CEGUI.h>

//El UIPushButton se crea un boton
//Se lo guarda
//Y le dice al root del UIManager que ahora es hijo de la ventana principal

UIPushButton::UIPushButton():UIElement()
{

	elementInterface = new CEGUI::PushButton("", "");

	elementInterface->addEvent("");
	
	//Problemon
	static_cast<CEGUI::PushButton*>(elementInterface)->setPushedState(false);


	UIManager::getInstance()->getRoot();
}

UIPushButton::~UIPushButton()
{

}
