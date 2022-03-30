﻿// ElHornoMain.cpp

#include <iostream>
#include <fstream>
#include "ElHornoBase.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "OurFrameListener.h"
#include "FactoryCreator.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "Scene.h"
#include "Factory.h"
#include "Timer.h"
#include "LuaManager.h"
#include "CheckMl.h"
#include "Entity.h"
#include "AudioComponent.h"

using json = nlohmann::json;

ElHornoBase* ElHornoBase::instance_;

/*
CADENA DE LLAMADAS QUE EJECUTAN EL BUCLE PRINCIPAL
*/

ElHornoBase::ElHornoBase()
{
	//frameListener_ = new OurFrameListener();
	paused_ = false;
}

/*
Limpia managers y dependencias de bibliotecas externas
*/
ElHornoBase::~ElHornoBase()
{
	delete globalTimer_; globalTimer_ = nullptr;
	El_Horno::AudioManager::erase();
	El_Horno::InputManager::erase();
	FactoryCreator::erase();
	El_Horno::LuaManager::erase();
	SceneManager::erase();
	El_Horno::EventManager::erase();
	El_Horno::GraphicsManager::erase();
	El_Horno::PhysicsManager::erase();
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

/* Inicializa managers */
void ElHornoBase::init() {

	// Aqui se inicializan las instancias de todos los managers
	FactoryCreator::setupInstance();
	//Creacion del factoryCreator y declaracion de los componentes del motor
	setupFactories();

	SceneManager::setupInstance();
	El_Horno::EventManager::setupInstance();
	El_Horno::GraphicsManager::setInstance();
	El_Horno::PhysicsManager::setupInstance();
	El_Horno::InputManager::setupInstance();
	El_Horno::AudioManager::setupInstance();

	//HornoLua
	El_Horno::LuaManager::setupInstance();
}

/*
Ejecuta el start del SceenManager y comienza el renderizado de Ogre
*/
void ElHornoBase::start()
{
	El_Horno::PhysicsManager::getInstance()->start("");
	El_Horno::GraphicsManager::getInstance()->init();
	SceneManager::getInstance()->getCurrentScene()->start();
	El_Horno::AudioManager::getInstance()->init();
	El_Horno::LuaManager::getInstance()->init();

	El_Horno::LuaManager::getInstance()->reedLuaScript("Assets/Scripts/sample.lua");
}

/*
Finaliza el renderizado de Ogre
*/
void ElHornoBase::exit()
{
	
}

/*
* Inicializa SDL y todos los demás managers (importante capturar posibles excepciones)
*/
void ElHornoBase::setup() {
	

	json extCfg;

	std::ifstream i("config.cfg");

	if (i.is_open())
	{
		i >> extCfg;
		i.close();
	}
	else
		std::cout << "File not found: config.cfg\n";
	

	ExtraConfig = extCfg;

	extraConfig(extCfg);

	// ElhornoOgre->setup
}

/*
Limpia la escena desde el SceneManager
*/
void ElHornoBase::cleanScene()
{
}

void ElHornoBase::extraConfig(nlohmann::json& j)
{
}

void ElHornoBase::setupFactories()
{
	FactoryCreator* facCreat = FactoryCreator::getInstance();
	// Factorías de componentes principales (transform, rigidbody, etc.)
	facCreat->addFactory("transform");
	facCreat->addFactory("camera");
	facCreat->addFactory("mesh");
	facCreat->addFactory("light");
	facCreat->addFactory("rigidbody");
	facCreat->addFactory("particleSystem");
	facCreat->addFactory("audioComponent");
	facCreat->addFactory("audioListener");
}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame(float deltaTime) {
	exit_ = El_Horno::GraphicsManager::getInstance()->pollEvents();

	
	// Updates de managers
	if (!paused_) {
		//SceneManager::getInstance()->preUpdate();
		El_Horno::PhysicsManager::getInstance()->update(deltaTime);
		El_Horno::PhysicsManager::getInstance()->updateDebug(3);
		SceneManager::getInstance()->update();
	}
	else {
		//SceneManager::getInstance()->pausedUpdate();
	}

	//AudioManager::getInstance()->update();
	El_Horno::GraphicsManager::getInstance()->render();
	//UIManager::getInstance()->update();
	SceneManager::getInstance()->deleteEntities();
	//SceneManager::getInstance()->endFrame();
}

void ElHornoBase::update()
{
	exit_ = false;
	globalTimer_ = new El_Horno::Timer();
	float deltaTime = 0;
	
	// ESTO ES DE PRUEBA
	//SceneManager::getInstance()->getCurrentScene()->getEntity("object", "prueba")->getComponent<El_Horno::AudioComponent>("audioComponent")->playSound("NeonRider.mp3");
	while (!exit_) {
		globalTimer_->resetTimer();
		processFrame(deltaTime);

		deltaTime = globalTimer_->getTime();
	}

	erase();
}

SceneManager* ElHornoBase::getSceneManager()
{
	return SceneManager::getInstance();
}

El_Horno::InputManager* ElHornoBase::getInputManager()
{
	return El_Horno::InputManager::getInstance();
}

El_Horno::GraphicsManager* ElHornoBase::getGraphicsManager()
{
	return El_Horno::GraphicsManager::getInstance();
}

El_Horno::AudioManager* ElHornoBase::getAudioManager()
{
	return El_Horno::AudioManager::getInstance();
}

/*
Devuelve el timer que lleva el frameRenderer para ejecutar el ciclo de juego
*/
//float ElHornoBase::getTime()
//{

//	/*return frameListener_->getTime();*/
//}

/*
//Devuelve el tiempo entre un frame y el anterior
//*/

//float ElHornoBase::deltaTime()
//{
//	return 	frameListener_->DeltaTime();
//}

/*
Resetea el timer
*/
//void ElHornoBase::resetTimer()
//{
//	frameListener_->resetTimer();
//}

void ElHornoBase::pause()
{
	paused_ = !paused_;
}

bool ElHornoBase::isPaused()
{
	return paused_;
}

void ElHornoBase::setInvertedAxisX(bool value)
{
	invertedAxisX_ = value;
}

void ElHornoBase::setInvertedAxisY(bool value)
{
	invertedAxisY_ = value;
}

/*
* Preguntan el invertedAxisX al input manager
*/
bool ElHornoBase::getInvertedAxisXInput()
{
	return false;
}

/*
*  Preguntan el invertedAxisY al input manager
*/
bool ElHornoBase::getInvertedAxisYInput()
{
	return false;
}

bool ElHornoBase::getInvertedAxisXTemp()
{
	return invertedAxisX_;
}

bool ElHornoBase::getInvertedAxisYTemp()
{
	return invertedAxisY_;
}

/*
cambia opciones básicas en otros managers (Axis de input manager y
volume de audio manager)
*/
void ElHornoBase::changeBasicOptions()
{

}

/*
* Devuelve el Timer global del proyecto
*/
El_Horno::Timer* ElHornoBase::getGlobalTime()
{
	return globalTimer_;
}