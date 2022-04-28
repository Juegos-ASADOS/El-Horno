#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "SDL_keyboard.h"
#include <vector>
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
			bool down_;
			bool pressed_;
			bool up_;
		};

		KeyState keys_[SDL_NUM_SCANCODES];

		std::vector<int> keysUpsToFlush;

		std::vector<int> keysDownToFlush;

		void manageKeys(SDL_Event event);

		void flushInput();

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
	};
}
#endif _INPUT_MANAGER_H