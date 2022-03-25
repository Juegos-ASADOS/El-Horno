#pragma once
#ifndef _FACTORY_CREATOR_H
#define _FACTORY_CREATOR_H

#include <string>
#include <map>
#include "json.hpp"
#include "Factory.h"

class Component;
class Factory;

class FactoryCreator
{

private:
	FactoryCreator() {
		map = std::map<std::string, Factory*>();
	};

	static FactoryCreator* instance_;

	//Lleva todas las factorias de todos los componentes que creas en el juego
	std::map<std::string, Factory*> map;

public:
	static FactoryCreator* getInstance();
	static bool setupInstance();
	static void clean();

	template<typename ...Ts>
	Component* getComponent(const std::string type, Ts &&...args)
	{
		std::map<std::string, Factory*>::iterator it = map.find(type);

		// Si esta en el mapa
		if (it != map.end())
		{
			// Cogemos la factoria del componente y lo creamos
			return (it)->second->createComponent(args...);
		}

		//Si no esta en el mapa
		return nullptr;

	}
	void addFactory(const std::string& type, Factory* factory);
};

#endif _FACTORY_CREATOR_H