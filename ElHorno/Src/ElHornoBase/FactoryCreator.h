#pragma once
#ifndef _FACTORY_CREATOR_H
#define _FACTORY_CREATOR_H

#include <string>
#include <vector>
#include "Factory.h"

class Component;
class Factory;

class FactoryCreator
{

private:
	FactoryCreator() {
		compList_ = std::vector<std::string>();
	};

	static FactoryCreator* instance_;

	//Lleva todas las factorias de todos los componentes que creas en el juego
	std::vector<std::string> compList_;

public:
	static FactoryCreator* getInstance();
	static bool setupInstance();
	static void erase();

	template<typename T, typename ...Ts>
	T* getComponent(const std::string type, Ts &&...args)
	{
		auto it = compList_.begin();
		for (auto it : compList_)
			if (it == type)
				break;

		// Si esta en el mapa
		if (it != compList_.end())
		{
			// Cogemos la factoria del componente y lo creamos
			return Factory::createComponent<T>(args...);
		}

		//Si no esta en el mapa
		return nullptr;

	}
	void addFactory(const std::string& type);
};

#endif _FACTORY_CREATOR_H