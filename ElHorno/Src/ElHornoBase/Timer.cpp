#include "Timer.h"
#include <Windows.h> 
#include "CheckML.h"

Timer::Timer()
{
	resetTimer();
}

Timer::~Timer()
{
}

// Tiempo que lleva el programa en ejecución en segundos
double Timer::getExeTime()
{
	return (double)GetTickCount64() / 1000.0;
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