#include "Timer.h"
#include <Windows.h> 

Timer::Timer()
{
	resetTimer();
	originalTime_ = firstTime_;
}

Timer::~Timer()
{
}

// Tiempo que lleva el programa en ejecuci�n en segundos
double Timer::getExeTime()
{
	return (double)GetTickCount64() / 1000.0 - originalTime_;
}

// Tiempo desde firstTime_ (desde que se resetea el timer)
double Timer::getTime()
{
	return getExeTime() - firstTime_;
}

void Timer::resetTimer()
{
	firstTime_ = (double)GetTickCount64() / 1000.0;
}