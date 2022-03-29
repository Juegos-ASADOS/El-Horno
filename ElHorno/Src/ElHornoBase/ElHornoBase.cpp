// ElHornoMain.cpp

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
#include "CheckML.h"

using json = nlohmann::json;

ElHornoBase* ElHornoBase::instance_;

/*
CADENA DE LLAMADAS QUE EJECUTAN EL BUCLE PRINCIPAL
Llamamos a Ogre::root->addFrameListener() y le metemos nuestro listener
"frameListener_" como parametro. OgreRoot llama a frameListener_ que,
a su vez, llama a processFrame, encargado de actualizar cada instancia de
cada manager
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
	InputManager::erase();
	FactoryCreator::erase();
	LuaManager::erase();
	SceneManager::erase();
	EventManager::erase();
	GraphicsManager::erase();
	PhysicsManager::erase();
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
	EventManager::setupInstance();
	GraphicsManager::setInstance();
	PhysicsManager::setupInstance();
	InputManager::setupInstance();

	//HornoLua
	LuaManager::setupInstance();
}

/*
Ejecuta el start del SceenManager y comienza el renderizado de Ogre
*/
void ElHornoBase::start()
{
	PhysicsManager::getInstance()->start("");
	GraphicsManager::getInstance()->init();
	SceneManager::getInstance()->getCurrentScene()->start();
	LuaManager::getInstance()->init();

	LuaManager::getInstance()->reedLuaScript("Assets/Scripts/sample.lua");
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
}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame(float deltaTime) {
	exit_ = GraphicsManager::getInstance()->pollEvents();

	
	// Updates de managers
	if (!paused_) {
		//SceneManager::getInstance()->preUpdate();
		PhysicsManager::getInstance()->update(deltaTime);
		SceneManager::getInstance()->update();
	}
	else {
		//SceneManager::getInstance()->pausedUpdate();
	}

	//AudioManager::getInstance()->update();
	GraphicsManager::getInstance()->render();
	//UIManager::getInstance()->update();
	SceneManager::getInstance()->deleteEntities();
	//SceneManager::getInstance()->endFrame();
}

void ElHornoBase::update()
{
	exit_ = false;
	globalTimer_ = new Timer();
	float deltaTime = 0;

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
Timer* ElHornoBase::getGlobalTime()
{
	return globalTimer_;
}