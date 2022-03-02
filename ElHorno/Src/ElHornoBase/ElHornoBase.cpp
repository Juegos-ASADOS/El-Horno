// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
//#include <SDL.h>
//#include <SDL_video.h>
//#include <SDL_syswm.h>
#include "ElHornoBase.h"
#include "ElHornoBullet.h"
//#include "OurFrameListener"

ElHornoBase::ElHornoBase()
{
	//frameListener_ = new OurFrameListener();
}

ElHornoBase::~ElHornoBase()
{

}

ElHornoBase* ElHornoBase::getInstance() {
	if (instance_ == nullptr)
		return nullptr;
	else
		return instance_;
}

bool ElHornoBase::setInstance()
{
	if (instance_ == 0) {
		instance_ = new ElHornoBase();
		return true;
	}
	return false;
}

void ElHornoBase::erase()
{
	delete instance_;
}

// Inicializa managers
void ElHornoBase::init() {
	Ogre::Root* root;
	root = new Ogre::Root();
	ElHornoBullet::bullet();

	//SDL_Init(SDL_INIT_EVERYTHING);
}

void ElHornoBase::start()
{
}

void ElHornoBase::exit()
{
}

/*
CADENA DE LLAMADAS QUE EJECUTAN EL BUCLEPRINCIPAL
Llamamos a Ogre::root->addFrameListener() y le metemos nuestro listener
"frameListener_" como parametro. OgreRoot llama a frameListener_ que,
a su vez, llama a processFrame, encargado de actualizar cada instancia de
cada manager
*/
void ElHornoBase::setup() {

}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame() {

}

//pollEvents
//Procesa los eventos de SDL y los envía al InputManager