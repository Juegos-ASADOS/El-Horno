﻿// ElHornoMain.cpp

#include <iostream>
#include <fstream>
#include "ElHornoBase.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "ElHornoFMOD.h"
#include "GraphicsManager.h"
#include "OurFrameListener.h"
#include "FactoryCreator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Factory.h"

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
}

/*
Limpia managers y dependencias de bibliotecas externas
*/
ElHornoBase::~ElHornoBase()
{
	/*delete frameListener_;
	frameListener_ = nullptr;*/
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


}

/*
Ejecuta el start del SceenManager y comienza el renderizado de Ogre
*/
void ElHornoBase::start()
{
	SceneManager::getInstance()->getCurrentScene()->start();
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
	facCreat->addFactory("transform", new TransformFactory());
	facCreat->addFactory("camera", new CameraFactory());
	facCreat->addFactory("mesh", new MeshFactory());
}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame() {
	GraphicsManager::getInstance()->pollEvents();

	// Updates de managers
	SceneManager::getInstance()->update();
}

void ElHornoBase::update()
{
	exit_ = false;

	while (!exit_) {

	}
}

SceneManager* ElHornoBase::getSceneManager()
{
	return nullptr;
}

InputManager* ElHornoBase::getInputManager()
{
	return InputManager::getInstance();
}

GraphicsManager* ElHornoBase::getGraphicsManager()
{
	return GraphicsManager::getInstance();
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