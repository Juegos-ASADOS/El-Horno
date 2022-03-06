#include "FactoryCreator.h"
#include "Factory.h"


//DEFINIR EL SINGLETONE
FactoryCreator* FactoryCreator::getInstance()
{
	//si no hay instancia devolvemos null
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool FactoryCreator::setupInstance()
{
	//Si no hay instancia creamos el sigletone
	if (instance == 0)
	{
		instance = new FactoryCreator();
		return true;
	}

	return false;
}

void FactoryCreator::clean()
{
	delete instance;
}


Component* FactoryCreator::getComponentFromJson(const std::string type, json& args)
{
	//Comprobamos si el componente esta en el mapa
	std::map<std::string, Factory*>::iterator it = map.find(type);
	if (it != map.end())
	{
		//Cogemos la factoria del componente y lo creamos
		return (it)->second->createComponent(args);
	}

	return nullptr;
	
}