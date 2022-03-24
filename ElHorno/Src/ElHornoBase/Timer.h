#pragma once
#ifndef _TIMER_H
#define _TIMER_H

class Timer{
public:

	Timer();
	~Timer();

	double getExeTime();
	double getTime();
	void resetTimer();

private:
	double firstTime_;
	double originalTime_;
};

#endif _TIMER_H