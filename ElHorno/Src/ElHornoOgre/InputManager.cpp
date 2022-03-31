#include "InputManager.h" //ajusten a ruta cuano organicemos carpetas
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_events.h>
#include <iostream>
#include "CheckML.h"

//#include <CEGUI/CEGUI.h>
//#include "checkML.h"

namespace El_Horno {
	InputManager* InputManager::instance = 0;

	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
		/*for (int i = 0; i < NumControls && controllers.size() > i; i++) {
			SDL_GameControllerClose(controllers[i].cReference);
		}
		controllers.clear();*/
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

	void InputManager::erase()
	{
		delete instance;
	}

	//esto seria para poner el setup principalmente de los mandos, lo omito ya que solo queiro pillar el input de teclado momento
	void InputManager::setup()
	{

		//TODO configuracion de mandos
	}

	//recoge los principales eventos de SDL y los gestiona de ser necesario
	bool InputManager::GeneralInputManagement(SDL_Event event)
	{
		//http://cegui.org.uk/wiki/Using_CEGUI_with_SDL_and_OpenGL_(0.7) //la referencia que voya a usar


		switch (event.type)
		{
			//En principio, como se puede preguntar si X tecla o boton del mando está pulsada/o, no hace falta gestionar esos eventos
			//Teclado y mando

			//Estos si hay que guardarlos
			//Raton
		case SDL_MOUSEMOTION:

			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y) // scroll up/down
			{
			}
			else if (event.wheel.x) // scroll left
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
		return false;

	}


	bool InputManager::IsKeyDown(SDL_Scancode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		return state[key];
	}
}