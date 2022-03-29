#include "OurFrameListener.h"

#include "ElHornoBase.h"
#include <OgreTimer.h>

#include <Windows.h> 

//#include <SDL_events.h>
namespace El_Horno {

	OurFrameListener::OurFrameListener()
	{
		//timer_ = new Ogre::Timer();
		//prevTime = std::chrono::high_resolution_clock::now();
	}

	OurFrameListener::~OurFrameListener()
	{
		//delete timer_;
		//timer_ = nullptr;
	}

	bool OurFrameListener::frameStarted(const Ogre::FrameEvent& evt)
	{
		//std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - prevTime;

		//deltaTime_ = elapsed.count();

		//prevTime = std::chrono::high_resolution_clock::now(); //Necesita Windows.h

		//ElHornoBase::getInstance()->processFrame();

		return true;
	}
}
//// Tiempo que lleva el programa en ejecución en segundos
//double OurFrameListener::getTime()
//{
//	return (double)GetTickCount64() / 1000.0;
//}
//
//// Diferencia en segundos
//double OurFrameListener::getTimeDifference(double prevTime)
//{
//	return getTime() - prevTime;
//}
//
//// Tiempo que transcurre entre frames en segundos
//double OurFrameListener::DeltaTime()
//{
//	return deltaTime_;
//}
//
//void OurFrameListener::resetTimer()
//{
//	timer_->reset();
//	prevTime = std::chrono::high_resolution_clock::now();
//}