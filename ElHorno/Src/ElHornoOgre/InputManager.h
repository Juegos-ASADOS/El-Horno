#pragma once
#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "SDL_keyboard.h"

union SDL_Event;
//enum SDL_Scancode;

class InputManager
{

private:
	InputManager();

	static InputManager* instance;

	//pendiente de agregar mandos

public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	~InputManager();

	static InputManager* getInstance();
	static bool setupInstance();
	static void erase();

	void setup();

	bool GeneralInputManagement(SDL_Event event);

	//el resto sera para arreglar lo que SDL no hace, (raton, mando xbox, etc)
	bool IsKeyDown(SDL_Scancode key);
};

#endif _INPUT_MANAGER_H