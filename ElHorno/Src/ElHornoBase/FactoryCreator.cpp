#include "FactoryCreator.h"
#include "Factory.h"
#include "CheckML.h"

namespace El_Horno {
	FactoryCreator* FactoryCreator::instance_;

	// DEFINIR EL SINGLETONE
	FactoryCreator* FactoryCreator::getInstance()
	{
		// si no hay instancia devolvemos null
		return instance_;
	}
	bool FactoryCreator::setupInstance()
	{
		// Si no hay instancia creamos el singletone
		if (instance_ == 0)
		{
			instance_ = new FactoryCreator();
			return true;
		}

		return false;
	}
	void FactoryCreator::erase()
	{
		delete instance_;
	}
	// FIN DEFINIR SINGLETON


	// Para crear componentes desde el Json
	//template<typename ...Ts>
	//Component* FactoryCreator::getComponent(const std::string type, Ts &&...args)
	//{
	//	std::map<std::string, Factory*>::iterator it = map.find(type);
	//
	//	// Si esta en el mapa
	//	if (it != map.end())
	//	{
	//		// Cogemos la factoria del componente y lo creamos
	//		return (it)->second->createComponent(args);
	//	}
	//
	//	//Si no esta en el mapa
	//	return nullptr;
	//	
	//}

	// Para añadir factorias(crean componentes) al mapa
	void FactoryCreator::addFactory(const std::string& type)
	{
		compList_.push_back(type);
	}
}