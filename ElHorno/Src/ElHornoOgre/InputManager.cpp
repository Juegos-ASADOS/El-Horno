#include "InputManager.h" 
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_events.h>
#include <iostream>
#include "CheckML.h"

//#include <CEGUI/CEGUI.h>
//#include "checkML.h"

namespace El_Horno {
	InputManager* InputManager::instance_ = 0;

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
		if (instance_ == 0 || instance_ == nullptr)
		{
			return nullptr;
		}

		return instance_;
	}


	bool InputManager::setupInstance()
	{
		if (instance_ == 0)
		{
			instance_ = new InputManager();
			return true;
		}

		return false;
	}

	void InputManager::erase()
	{
		delete instance_;
	}

	//esto seria para poner el setup principalmente de los mandos, lo omito ya que solo queiro pillar el input de teclado momento
	void InputManager::setup()
	{
		//TODO configuracion de mandos
	}

	//recoge los principales eventos de SDL y los gestiona de ser necesario
	bool InputManager::generalInputManagement(SDL_Event event)
	{
		switch (event.type)
		{
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


	bool InputManager::isKeyDown(SDL_Scancode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		return state[key];
	}
}

//http://cegui.org.uk/wiki/Using_CEGUI_with_SDL_and_OpenGL_(0.7) //la referencia que voya a usar