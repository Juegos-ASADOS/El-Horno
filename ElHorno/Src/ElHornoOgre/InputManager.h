#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "SDL_keyboard.h"
#include <vector>
#include <array>
#include <SDL_gamecontroller.h>
union SDL_Event;
//enum SDL_Scancode;

namespace El_Horno {
	class _declspec(dllexport) InputManager
	{

	private:
		InputManager();

		static InputManager* instance_;

		//pendiente de agregar mandos

		struct KeyState {
			bool down_ = false;
			bool pressed_ = false;
			bool up_ = false;
		};

		KeyState keys_[SDL_NUM_SCANCODES];

		std::vector<int> keysUpsToFlush;

		std::vector<int> keysDownToFlush;

		void manageKeys(SDL_Event event);

		void manageAxes(SDL_Event event);
		void manageButtons(SDL_Event event);
		void manageControllerAdded(SDL_Event event);
		void manageControllerRemoved(SDL_Event event);

		void flushInput();

		SDL_GameController* controller_ = nullptr;
		std::array<Sint16, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX> controllerAxes_;
		std::array<bool, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX> controllerButtons_;

		const float AXESDEADZONE = 10000.0f;
	public:

		//lo uncio necesario para recoger input del teclado a traves de SDL
		~InputManager();

		static InputManager* getInstance();
		static bool setupInstance();
		static void erase();

		void injectCegui(SDL_Event event);

		void setup();

		bool generalInputManagement(SDL_Event event);

		bool isKeyDown(SDL_Scancode key);
		bool getKeyDown(SDL_Scancode code);
		bool getKeyUp(SDL_Scancode code);

		Sint16 getAxis(SDL_GameControllerAxis axis);
		bool isButtonDown(SDL_GameControllerButton button);
	};
}
#endif _INPUT_MANAGER_H