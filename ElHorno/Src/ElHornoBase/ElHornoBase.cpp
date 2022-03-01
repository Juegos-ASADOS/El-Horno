// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
#include "ElHornoBase.h"
#include "ElHornoBullet.h"

// Inicializa managers
void ElHornoBase::init() {
	Ogre::Root* root;
	root = new Ogre::Root();
	ElHornoBullet::bullet();
}

// 
ElHornoBase* ElHornoBase::getInstance() {
	if (instance_ == nullptr)
		return nullptr;
	else
		return instance_;
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