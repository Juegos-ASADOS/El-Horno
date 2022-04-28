#include "InputManager.h" 
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_events.h>
#include <iostream>
#include "CheckML.h"
#include <CEGUI/CEGUI.h>

//#include <CEGUI/CEGUI.h>
//#include "checkML.h"

namespace El_Horno {
	InputManager* InputManager::instance_ = 0;

	InputManager::InputManager()
	{
	}

	void InputManager::manageKeys(SDL_Event event)
	{
		if (event.type == SDL_KEYDOWN) {
			SDL_Scancode code = event.key.keysym.scancode;
			if (!keys_[code].pressed_) {
				keys_[code].down_ = true;
				keys_[code].up_ = false;
				keysDownToFlush.push_back(code);
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			SDL_Scancode code = event.key.keysym.scancode;
			keys_[code].down_ = false;
			keys_[code].pressed_ = false;
			keys_[code].up_ = true;
			keysUpsToFlush.push_back(code);
		}

	}

	void InputManager::flushInput()
	{
		for (int c : keysUpsToFlush)
			keys_[c].up_ = false;
		keysUpsToFlush.clear();
		for (int c : keysDownToFlush)
			keys_[c].down_ = false;
		keysDownToFlush.clear();
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


	 //auxilaires para injectar a cegui
	CEGUI::Key::Scan KeyCode_TO_CEGUI(SDL_KeyCode key)
	{
		using namespace CEGUI;
		switch (key)
		{
		case SDLK_UP:
			return Key::ArrowUp;
		case SDLK_DOWN:
			return Key::ArrowDown;
		case SDLK_LEFT:
			return Key::ArrowLeft;
		case SDLK_RIGHT:
			return Key::ArrowRight;
		case SDLK_ESCAPE:
			return Key::Escape;
		case SDLK_INSERT:
			return Key::Insert;
		case SDLK_SPACE:
			return Key::Space;
		default:
			return Key::Unknown;
		}
	}

	CEGUI::MouseButton MouseButton_TO_CEGUI(Uint8 MouseButtons)
	{
		switch (MouseButtons) {
		case SDL_BUTTON_LEFT: return CEGUI::MouseButton::LeftButton;
		case SDL_BUTTON_MIDDLE: return CEGUI::MouseButton::MiddleButton;
		case SDL_BUTTON_RIGHT: return CEGUI::MouseButton::RightButton;
		case SDL_BUTTON_X1: return CEGUI::MouseButton::X1Button;
		case SDL_BUTTON_X2: return CEGUI::MouseButton::X2Button;
		}
		return CEGUI::MouseButton::NoButton;
	}

	void InputManager::injectCegui(SDL_Event event)
	{
		if (event.type == SDL_KEYDOWN) {
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI((SDL_KeyCode)event.key.keysym.sym));
		}
		else if (event.type == SDL_KEYUP) {
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI((SDL_KeyCode)event.key.keysym.sym));
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(MouseButton_TO_CEGUI(event.button.button));
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(MouseButton_TO_CEGUI(event.button.button));
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(event.motion.x, event.motion.y);
		}

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
			manageKeys(event);
			break;
		}

		injectCegui(event);

		return false;

	}


	bool InputManager::isKeyDown(SDL_Scancode key)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		return state[key];
	}

	bool InputManager::getKeyDown(SDL_Scancode code)
	{
		return keys_[code].down_;
	}

	bool InputManager::getKeyUp(SDL_Scancode code)
	{
		return keys_[code].up_;
	}
}

//http://cegui.org.uk/wiki/Using_CEGUI_with_SDL_and_OpenGL_(0.7) //la referencia que voya a usar