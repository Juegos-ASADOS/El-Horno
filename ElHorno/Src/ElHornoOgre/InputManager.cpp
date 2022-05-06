#include "InputManager.h" 
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_events.h>
#include <iostream>
#include "CheckML.h"
#include <CEGUI/CEGUI.h>
#include <UIManager.h>
//#include <CEGUI/CEGUI.h>
//#include "checkML.h"

namespace El_Horno {
	InputManager* InputManager::instance_ = 0;

	InputManager::InputManager()
	{
	}

	void InputManager::manageKeys(const SDL_Event& event)
	{
		if (event.type == SDL_KEYDOWN) {
			SDL_Scancode code = event.key.keysym.scancode;
			if (!keys_[code].pressed_) {
				keys_[code].down_ = true;
				keys_[code].up_ = false;
				keys_[code].pressed_ = true;
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

	void InputManager::manageAxes(const SDL_Event& event)
	{
		Uint8 axis = 0;
		for (Uint8 i = 0; i < SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX; ++i) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForAxis(controller_, (SDL_GameControllerAxis)i);
			if (b.value.axis == event.caxis.axis) {
				axis = i;
				break;
			}
		}

		// Joysticks
		if (axis < 4)
			controllerAxes_[axis] = (event.caxis.value > AXESDEADZONE || event.caxis.value < -AXESDEADZONE) ? event.caxis.value : 0;
		// Triggers
		else
			controllerAxes_[axis] = (event.caxis.value > AXESDEADZONE) ? abs(event.caxis.value) : 0;
	}

	void InputManager::manageButtonDown(const SDL_Event& event)
	{
		Uint8 button = 0;
		bool found = false;
		for (Uint8 i = 0; i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX; ++i) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(controller_, (SDL_GameControllerButton)i);
			if (b.value.button == event.cbutton.button) {
				button = i;
				found = true;
				break;
			}
		}

		if (found && !buttons_[button].pressed_) {
			//controllerButtons_[button] = event.cbutton.state;
			buttons_[button].down_ = true;
			buttons_[button].pressed_ = true;
			buttons_[button].up_ = false;
			buttonsDownToFlush.push_back(button);
		}
	}

	void InputManager::manageButtonUp(const SDL_Event& event)
	{
		Uint8 button = 0;
		bool found = false;
		for (Uint8 i = 0; i < SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX; ++i) {
			SDL_GameControllerButtonBind b = SDL_GameControllerGetBindForButton(controller_, (SDL_GameControllerButton)i);
			if (b.value.button == event.cbutton.button) {
				button = i;
				found = true;
				break;
			}
		}

		if (found) {
			//controllerButtons_[button] = event.cbutton.state;
			buttons_[button].down_ = false;
			buttons_[button].pressed_ = false;
			buttons_[button].up_ = true;
			buttonsUpToFlush.push_back(button);
		}
	}

	void InputManager::manageControllerAdded(const SDL_Event& event)
	{
		if (controller_ == nullptr) {
			controller_ = SDL_GameControllerOpen(event.cdevice.which);
			for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
				controllerAxes_[i] = 0.0f;

			//std::cout << SDL_GameControllerName(controller_) << std::endl;
			SDL_GameControllerEventState(SDL_ENABLE);
		}
	}

	void InputManager::manageControllerRemoved(const SDL_Event& event)
	{
		if (controller_ == SDL_GameControllerFromInstanceID(event.cdevice.which)) {
			SDL_GameControllerClose(controller_);
			controller_ = nullptr;

			for (float f : controllerAxes_)
				f = 0.0f;
			for (KeyState k : buttons_) {
				k.down_ = false;
				k.pressed_ = false;
				k.up_ = false;
			}
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
		for (int c : buttonsUpToFlush)
			buttons_[c].up_ = false;
		buttonsUpToFlush.clear();
		for (int c : buttonsDownToFlush)
			buttons_[c].down_ = false;
		buttonsDownToFlush.clear();
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
			UIManager::getInstance()->getContext()->injectKeyDown(KeyCode_TO_CEGUI((SDL_KeyCode)event.key.keysym.sym));
		}
		else if (event.type == SDL_KEYUP) {
			UIManager::getInstance()->getContext()->injectKeyUp(KeyCode_TO_CEGUI((SDL_KeyCode)event.key.keysym.sym));
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			UIManager::getInstance()->getContext()->injectMouseButtonDown(MouseButton_TO_CEGUI(event.button.button));
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			UIManager::getInstance()->getContext()->injectMouseButtonUp(MouseButton_TO_CEGUI(event.button.button));
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			UIManager::getInstance()->getContext()->injectMousePosition(event.motion.x, event.motion.y);
		}

	}

	//esto seria para poner el setup principalmente de los mandos, lo omito ya que solo queiro pillar el input de teclado momento
	void InputManager::setup()
	{
		SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
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
		case SDL_CONTROLLERAXISMOTION:
			manageAxes(event);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			manageButtonDown(event);
			break;
		case SDL_CONTROLLERBUTTONUP:
			manageButtonUp(event);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			manageControllerAdded(event);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			manageControllerRemoved(event);
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

	Sint16 InputManager::getAxis(SDL_GameControllerAxis axis)
	{
		if (controller_ != nullptr)
			return controllerAxes_[axis];

		return 0;
	}
	bool InputManager::isButtonDown(SDL_GameControllerButton button)
	{
		if (controller_ != nullptr)
			return buttons_[button].down_;

		return false;
	}
	void InputManager::hideMouse()
	{
		SDL_ShowCursor(false);
	}

	void InputManager::showMouse()
	{
		SDL_ShowCursor(true);
	}
}

//http://cegui.org.uk/wiki/Using_CEGUI_with_SDL_and_OpenGL_(0.7) //la referencia que voya a usar