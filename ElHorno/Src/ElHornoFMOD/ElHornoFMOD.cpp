//#include "ElHornoFMOD.h"
//
//#include "fmod.hpp"
//#include "fmod_errors.h"
//#include <iostream>
//
//#include "fmod_studio.hpp"
//#include "fmod.hpp"
//#include <string>
//#include <map>
//#include <vector>
//#include <math.h>
//
//void ElHornoFMOD::init()
//{
//	// Inicialización de FMOD core
//	FMOD_RESULT result;
//	FMOD::System* system = nullptr;
//
//	result = FMOD::System_Create(&system);      // Create the main system object.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		return;
//	}
//
//	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		return;
//	}
//	std::cout << "FMOD inciado.\n";
//}
