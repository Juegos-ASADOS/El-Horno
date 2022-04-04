#include "UIPushButton.h"
#include "UIManager.h"
#include <CEGUI/CEGUI.h>
#include "CheckML.h"

//El UIPushButton se crea un boton
//Se lo guarda
//Y le dice al root del UIManager que ahora es hijo de la ventana principal
namespace El_Horno {
	UIPushButton::UIPushButton(std::string& schemeName, int posX, int posY, int sizeX, int sizeY, std::string name_) : UIElement(posX, posY, sizeX, sizeY, name_)
	{
		//Le decimos a la ventana principal que cree una más
		boton = (CEGUI::PushButton*)UIManager::getInstance()->getWinMngr()->createWindow(schemeName + "/PushButton","PushButtonName");

		//Le asignamos el CEGUI::Window del padre para no tener que hacer casteos
		//Cada vez que queramos llamar a cualquier metodo propio de CEGUI::PushButton
		setElementInterface(boton);

		//Establecemos el nombre del evento y no se que mas
		boton->addEvent("nombrePropioDelEvento");

		//La clase padre UIElement se encarga de posicionarlo correctamente...
		init();

		//Y lo añadimos al boton a la escena
		UIManager::getInstance()->getRoot()->addChild(boton);

	}
	//No se como hacer qué hace cuando está pulsado
	void UIPushButton::isPushed()
	{
		//Todos los metodos propios de ButtonBase
		boton->isPushed();	//True si está siendo pulsado
		boton->isHovering();//True si tienes el raton por encima o has mantenido pulsado pero no has soltado CREO
	}

	UIPushButton::~UIPushButton()
	{
	}
}