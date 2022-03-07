#pragma once
#include <string>
#include <map>
#include "../json.hpp"

using namespace std;
class Component;
class Factory;

class FactoryCreator
{

private:
	FactoryCreator();

	static FactoryCreator* instance;

	//Lleva todas las factorias de todos los componentes que creas en el juego
	std::map<std::string, Factory*> map;

public:
	static FactoryCreator* getInstance();
	static bool setupInstance();
	static void clean();

	Component* getComponentFromJson(const std::string type, nlohmann::json& args);
	void addFactory(const std::string& type, Factory* factory);
};