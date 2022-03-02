// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
//#include <SDL.h>
//#include <SDL_video.h>
//#include <SDL_syswm.h>
#include "ElHornoBase.h"
#include "ElHornoBullet.h"
//#include "OurFrameListener"

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

/* Inicializa managers */
void ElHornoBase::init() {
	Ogre::Root* root;
	root = new Ogre::Root();
	ElHornoBullet::bullet();

	//SDL_Init(SDL_INIT_EVERYTHING);

	// Aqui se inicializan las instancias de todos los managers

	// Inicializa root de Ogre
	setupRoot();

	// Si hay configuraciones cargadas o inicia desde el cuadro de config de Ogre
	if (root_->restoreConfig() || root_->showConfigDialog(nullptr))
		setup();
}

/*
Ejecuta el start del SceenManager y comienza el renderizado de Ogre
*/
void ElHornoBase::start()
{

	root_->startRendering();
}

/*
Finaliza el renderizado de Ogre
*/
void ElHornoBase::exit()
{
	root_->queueEndRendering();
}

void ElHornoBase::setup() {

}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame() {

}

Ogre::Root* ElHornoBase::getRoot()
{
	return root_;
}

Ogre::SceneManager* ElHornoBase::getSceneManager()
{
	//return SceneManager;
}

Ogre::RenderWindow* ElHornoBase::getRenderWindow()
{
	return ogreWindow_;
}

SDL_Window* ElHornoBase::getSDLWindow()
{
	return sdlWindow_;
}

//pollEvents
//Procesa los eventos de SDL y los envía al InputManager

float ElHornoBase::deltaTime()
{
	//return 0.0f;
}

void ElHornoBase::pause()
{
	paused_ = !paused_;
}

bool ElHornoBase::isPaused()
{
	return paused_;
}

// actualiza el tamaño de la ventana de SDL y de CEGUI
void ElHornoBase::resizeScreen(int width, int height)
{
	//SDL_SetWindowSize(sdlWindow_, width, height);
	//sdlWindow_->windowMovedOrResized();

}
