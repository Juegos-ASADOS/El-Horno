#include "InputManager.h" //ajusten a ruta cuano organicemos carpetas
#include <iostream>

#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>

#include <SDL_events.h>
#include <CEGUI/CEGUI.h>
#include "checkML.h"

InputManager* InputManager::instance = 0;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	for (int i = 0; i < NumControls && controllers.size() > i; i++) {
		SDL_GameControllerClose(controllers[i].cReference);
	}
	controllers.clear();
}

InputManager* InputManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}


bool InputManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new InputManager();
		return true;
	}

	return false;
}

void InputManager::clean()
{
	delete instance;
}

//esto seria para poner el setup principalmente de los mandos, lo omito ya que solo queiro pillar el input de teclado momento
void InputManager::setup()
{

	//TODO
}

//recoge los principales eventos de SDL y los gestiona de ser necesario
void InputManager::GeneralInputManagement(SDL_Event event)
{
	//casa paco sponsored


	switch (event.type)
	{
		//En principio, como se puede preguntar si X tecla o boton del mando est� pulsada/o, no hace falta gestionar esos eventos
		//Teclado

		//Estos si hay que guardarlos
		//Raton
	case SDL_MOUSEMOTION:

		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y != mouseWheel.y) // scroll up/down
		{
		}
		else if (event.wheel.x != mouseWheel.x) // scroll left
		{
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			break;
		case SDL_BUTTON_MIDDLE:
			break;
		case SDL_BUTTON_RIGHT:
			break;
		case SDL_BUTTON_X1:
			break;
		case SDL_BUTTON_X2:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			break;
		case SDL_BUTTON_MIDDLE:
			break;
		case SDL_BUTTON_RIGHT:
			break;
		case SDL_BUTTON_X1:
			break;
		case SDL_BUTTON_X2:
			break;
		}
		break;
	default:
		break;
	}

}


bool InputManager::IsKeyDown(Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	return state[(SDL_Scancode)key];
}