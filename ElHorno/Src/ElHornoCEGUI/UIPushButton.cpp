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

	void UIPushButton::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "schemeName") {
				schemeName_ =parameters[i].second;
			}
			else if (parameters[i].first == "posX") {
				posX = stof(parameters[i].second);
			}
			else if (parameters[i].first == "posY") {
				posY = stof(parameters[i].second);
			}
			else if (parameters[i].first == "sizeX") {
				sizeX = stof(parameters[i].second);
			}
			else if (parameters[i].first == "sizeY") {
				sizeY = stof(parameters[i].second);
			}
			else if (parameters[i].first == "name") {
				name = parameters[i].second;
			}
		}
	}

	void UIPushButton::start() {
		UIManager::getInstance()->defineScheme(schemeName_ + ".scheme");

		//Le decimos a la ventana principal que cree una m�s							//es estupido, taharez solo saca el framewindow
		boton = (CEGUI::RadioButton*)UIManager::getInstance()->getWinMngr()->createWindow(schemeName_ + "/RadioButton", "PushButtonName");

		//Le asignamos el CEGUI::Window del padre para no tener que hacer casteos
		//Cada vez que queramos llamar a cualquier metodo propio de CEGUI::PushButton
		setElementInterface(boton);


		//La clase padre UIElement se encarga de posicionarlo correctamente...
		init();

		//Y lo a�adimos al boton a la escena
		UIManager::getInstance()->getRoot()->addChild(boton);
	}
	//No se como hacer qu� hace cuando est� pulsado
	void UIPushButton::isPushed()
	{
		////Todos los metodos propios de ButtonBase
		//boton->isPushed();	//True si est� siendo pulsado
		//boton->isHovering();//True si tienes el raton por encima o has mantenido pulsado pero no has soltado CREO
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