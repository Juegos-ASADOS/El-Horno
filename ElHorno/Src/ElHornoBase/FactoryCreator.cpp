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


	// Para a�adir factorias(crean componentes) al mapa
	void FactoryCreator::addFactory(const std::string& type)
	{
		compList_.push_back(type);
	}
}