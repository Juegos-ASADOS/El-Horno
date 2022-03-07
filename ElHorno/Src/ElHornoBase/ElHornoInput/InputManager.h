#pragma once

#include <vector>


#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>

#include <SDL_events.h>

union SDL_Event;
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
	static void clean();

	void setup();

	void GeneralInputManagement(SDL_Event event);

	//el resto sera para arreglar lo que SDL no hace, (raton, mando xbox, etc)

	bool IsKeyDown(SDL_Scancode key);


};


