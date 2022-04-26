#include "UIPushButton.h"
#include "UIManager.h"
#include <CEGUI/CEGUI.h>
#include "CheckML.h"

//El UIPushButton se crea un boton
//Se lo guarda
//Y le dice al root del UIManager que ahora es hijo de la ventana principal
namespace El_Horno {
	UIPushButton::UIPushButton(std::string schemeName, float posX, float posY, float sizeX, float sizeY, std::string name_) : UIElement(posX, posY, sizeX, sizeY, name_)
	{
		schemeName_ = schemeName;
	}
	
	


	void UIPushButton::start() {
		//Le decimos a la ventana principal que cree una más							//es estupido, taharez solo saca el framewindow
		boton = (CEGUI::PushButton*)UIManager::getInstance()->getWinMngr()->createWindow(schemeName_ + "/FrameWindow", "PushButtonName");

		//Le asignamos el CEGUI::Window del padre para no tener que hacer casteos
		//Cada vez que queramos llamar a cualquier metodo propio de CEGUI::PushButton
		setElementInterface(boton);


		//La clase padre UIElement se encarga de posicionarlo correctamente...
		init();

		//Y lo añadimos al boton a la escena
		UIManager::getInstance()->getRoot()->addChild(boton);
		boton->activate();
	}


	
	//No se como hacer qué hace cuando está pulsado
	void UIPushButton::isPushed()
	{
		//Todos los metodos propios de ButtonBase
		boton->isPushed();	//True si está siendo pulsado
		boton->isHovering();//True si tienes el raton por encima o has mantenido pulsado pero no has soltado CREO
	}

	void UIPushButton::addEvent(std::string evento)
	{
		//Establecemos el nombre del evento 
		boton->addEvent(evento);
	}

	UIPushButton::~UIPushButton()
	{
	}
}