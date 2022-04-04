#pragma once
#ifndef _TIMER_H
#define _TIMER_H

namespace El_Horno {
	class _declspec(dllexport) Timer {
	public:

		Timer();
		~Timer();

		double getExeTime();
		double getTime();
		void resetTimer();

	private:
		double firstTime_;
	};
}
#endif _TIMER_H