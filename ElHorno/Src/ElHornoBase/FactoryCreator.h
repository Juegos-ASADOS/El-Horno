#pragma once
#ifndef _FACTORY_CREATOR_H
#define _FACTORY_CREATOR_H

#include <string>
#include <map>
#include "json.hpp"

class Component;
class Factory;

class FactoryCreator
{

private:
	FactoryCreator() {};

	static FactoryCreator* instance_;

	//Lleva todas las factorias de todos los componentes que creas en el juego
	std::map<std::string, Factory*> map;

public:
	static FactoryCreator* getInstance();
	static bool setupInstance();
	static void clean();

	Component* getComponentFromJson(const std::string type, nlohmann::json& args);
	void addFactory(const std::string& type, Factory* factory);
};

#endif _FACTORY_CREATOR_H