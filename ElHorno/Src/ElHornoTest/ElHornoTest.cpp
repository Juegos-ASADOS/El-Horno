// ElHornoTest.cpp : Este archivo contiene la función "main" para hacer pruebas únicamente con el motor, sin necesidad de cargar un juego

#include <iostream>
#include "ElHornoBase.h"
#include "CheckML.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	El_Horno::ElHornoBase::setInstance();
	El_Horno::ElHornoBase::getInstance()->init();

	El_Horno::ElHornoBase::getInstance()->start();
	El_Horno::ElHornoBase::getInstance()->update();
}