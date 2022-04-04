#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "SDL_keyboard.h"

union SDL_Event;
//enum SDL_Scancode;

namespace El_Horno {
	class _declspec(dllexport) InputManager
	{

	private:
		InputManager();

		static InputManager* instance_;

		//pendiente de agregar mandos

	public:

		//lo uncio necesario para recoger input del teclado a traves de SDL
		~InputManager();

		static InputManager* getInstance();
		static bool setupInstance();
		static void erase();

		void setup();

		bool generalInputManagement(SDL_Event event);

		bool isKeyDown(SDL_Scancode key);
	};
}
#endif _INPUT_MANAGER_H