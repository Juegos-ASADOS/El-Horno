// main.cpp : Este archivo contiene la función "main" del motor, que debe cargar un juego 
//

#include <iostream>
#include "ElHornoBase.h"
#include "CheckML.h"
#include <Windows.h>
#include <Scene.h>
#include <SceneManager.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

#ifndef _DEBUG
	HMODULE game = LoadLibrary(TEXT("./ElHornoGame.dll"));
#endif // !_DEBUG
#ifdef _DEBUG
	HMODULE game = LoadLibrary(TEXT("./ElHornoGame_d.dll"));
#endif // _DEBUG
	//_CrtSetBreakAlloc(160161); //Deteccion de basura
	if (game != NULL) {
		El_Horno::ElHornoBase::setInstance();
		El_Horno::ElHornoBase::getInstance()->init();

		El_Horno::GameVoid gameFactories = (El_Horno::GameVoid)GetProcAddress(game, "addGameFactories");
		El_Horno::SceneLoad startScene = (El_Horno::SceneLoad)GetProcAddress(game, "loadStartScene");
		if (gameFactories && startScene) {
			gameFactories();
			startScene();
			El_Horno::ElHornoBase::getInstance()->start();
			El_Horno::ElHornoBase::getInstance()->update();
		}
		FreeLibrary(game);
	}
	return 0;
}
