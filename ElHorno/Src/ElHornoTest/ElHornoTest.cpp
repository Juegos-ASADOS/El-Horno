// ElHornoTest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include "ElHornoBase.h"
#include "CheckML.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	El_Horno::ElHornoBase::setInstance();
	El_Horno::ElHornoBase::getInstance()->init();

	}