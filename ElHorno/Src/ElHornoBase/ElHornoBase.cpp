#include <iostream>
#include <fstream>
#include "ElHornoBase.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "LuaManager.h"
#include "EventManager.h"
#include "UIManager.h"
#include "FactoryCreator.h"
#include "Scene.h"
#include "Factory.h"
#include "Timer.h"
#include "Entity.h"
#include "AudioComponent.h"
#include "CheckMl.h"
#

namespace El_Horno {

	ElHornoBase* ElHornoBase::instance_;

	/*
	CADENA DE LLAMADAS QUE EJECUTAN EL BUCLE PRINCIPAL
	*/

	ElHornoBase::ElHornoBase()
	{
		paused_ = false;
	}

	/*
	Limpia managers y dependencias de bibliotecas externas
	*/
	ElHornoBase::~ElHornoBase()
	{
		delete globalTimer_; globalTimer_ = nullptr;
		AudioManager::erase();
		InputManager::erase();
		FactoryCreator::erase();
		LuaManager::erase();
		SceneManager::erase();
		UIManager::erase();
		GraphicsManager::erase();
		PhysicsManager::erase();
		EventManager::erase();

	}

	ElHornoBase* ElHornoBase::getInstance() {
		return instance_;
	}

	bool ElHornoBase::setInstance()
	{
		if (instance_ == nullptr) {
			instance_ = new ElHornoBase();
			return true;
		}
		return false;
	}

	void ElHornoBase::erase()
	{
		delete instance_;
	}

	/* Inicializa instancias de managers */
	void ElHornoBase::init() {

		FactoryCreator::setupInstance();
		//Creacion del factoryCreator y declaracion de los componentes del motor
		setupFactories();

		SceneManager::setupInstance();
		GraphicsManager::setInstance();
		PhysicsManager::setupInstance();
		InputManager::setupInstance();
		AudioManager::setupInstance();
		EventManager::setupInstance();

		//UIManager
		UIManager::setupInstance();

		//HornoLua
		LuaManager::setupInstance();
		LuaManager::getInstance()->init();
		AudioManager::getInstance()->init();
	}

	/*
	Ejecuta el start de managersy comienza el renderizado de Ogre
	*/
	void ElHornoBase::start()
	{
		PhysicsManager::getInstance()->start("");
		GraphicsManager::getInstance()->init();
		UIManager::getInstance()->createContext();
		SceneManager::getInstance()->getCurrentScene()->awake(); //Inicializacion
		SceneManager::getInstance()->getCurrentScene()->start(); //Toma de codependencias
	}

	/*
	Finaliza el renderizado de Ogre
	*/
	void ElHornoBase::exit()
	{
		exit_ = true;
	}

	/*
	Limpia la escena desde el SceneManager
	*/
	//void ElHornoBase::cleanScene()
	//{
	//}

	// Factorías de componentes principales (transform, rigidbody, etc.)
	void ElHornoBase::setupFactories()
	{
		FactoryCreator* facCreat = FactoryCreator::getInstance();

		facCreat->addFactory("transform");
		facCreat->addFactory("camera");
		facCreat->addFactory("mesh");
		facCreat->addFactory("light");
		facCreat->addFactory("rigidbody");
		facCreat->addFactory("particleSystem");
		facCreat->addFactory("audiocomponent");
		facCreat->addFactory("audiolistener");
		facCreat->addFactory("uilayout");
		//facCreat->addFactory("UIPushButton");
		facCreat->addFactory("animatorcontroller");

	}

	/*
	Gestiona eventos y actualiza los managers
	*/
	void ElHornoBase::processFrame(float deltaTime) {
		exit_ = GraphicsManager::getInstance()->pollEvents();

		if (!paused_) {
			SceneManager::getInstance()->preUpdate();

			PhysicsManager::getInstance()->update(deltaTime);
			PhysicsManager::getInstance()->updateDebug(3);

			EventManager::getInstance()->processEvents();

			SceneManager::getInstance()->update();
			if (SceneManager::getInstance()->getChangeScene())
				LuaManager::getInstance()->callLuaFunction("changeNextScene");
		}
		else {
			//SceneManager::getInstance()->pausedUpdate();
		}

		AudioManager::getInstance()->update();
		GraphicsManager::getInstance()->render();
		UIManager::getInstance()->update();
		SceneManager::getInstance()->deleteEntities();
		//SceneManager::getInstance()->endFrame();
	}

	void ElHornoBase::update()
	{
		exit_ = false;
		globalTimer_ = new Timer();
		deltaTime_ = 0;

		while (!exit_) {
			globalTimer_->resetTimer();
			processFrame(deltaTime_);

			deltaTime_ = globalTimer_->getTime();
		}

		erase();
	}

	SceneManager* ElHornoBase::getSceneManager()
	{
		return SceneManager::getInstance();
	}

	InputManager* ElHornoBase::getInputManager()
	{
		return InputManager::getInstance();
	}

	GraphicsManager* ElHornoBase::getGraphicsManager()
	{
		return GraphicsManager::getInstance();
	}

	AudioManager* ElHornoBase::getAudioManager()
	{
		return AudioManager::getInstance();
	}

	UIManager* ElHornoBase::getUIManager()
	{
		return UIManager::getInstance();
	}

	FactoryCreator* ElHornoBase::getFactoryCreator()
	{
		return FactoryCreator::getInstance();
	}

	void ElHornoBase::pause()
	{
		paused_ = !paused_;
	}

	bool ElHornoBase::isPaused()
	{
		return paused_;
	}

	/*
	* Devuelve el Timer global del proyecto
	*/
	Timer* ElHornoBase::getGlobalTime()
	{
		return globalTimer_;
	}
	double ElHornoBase::getDeltaTime()
	{
		return deltaTime_;
	}
}