#pragma once
#ifndef _FACTORY_H
#define _FACTORY_H

namespace El_Horno {
	class Component;
	class _declspec(dllexport) Factory
	{
	public:
		Factory() {};

		template<typename T, typename ...Ts>
		static T* createComponent(Ts &&...args) { return new T(args...); };
	};
}
#endif _FACTORY_H