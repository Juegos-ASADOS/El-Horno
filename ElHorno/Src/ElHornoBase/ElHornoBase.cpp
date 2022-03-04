// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include "ElHornoBase.h"
#include "ElHornoBullet.h"
#include "ElHornoFMOD.h"
#include "OurFrameListener.h"

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
	delete root_;

	delete frameListener_;
	frameListener_ = nullptr;
	SDL_Quit();
}

ElHornoBase* ElHornoBase::getInstance() {
	//if (instance_ == nullptr)
	//	return nullptr;
	//else
	//	return instance_;
	return nullptr;
}

bool ElHornoBase::setInstance()
{
	//if (instance_ == 0) {
	//	instance_ = new ElHornoBase();
	//	return true;
	//}
	return false;
}

void ElHornoBase::erase()
{
	//delete instance_;
}

/* Inicializa managers */
void ElHornoBase::init() {
	root_ = new Ogre::Root();
	ElHornoBullet::init();
	ElHornoFMOD::init();
	SDL_Init(SDL_INIT_EVERYTHING);

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

/*
* Inicializa SDL y todos los demás managers (importante capturar posibles excepciones)
*/
void ElHornoBase::setup() {
	root_->initialise(false);

	setupWindow();

	// Setup de managers
	ogreSceneManager_ = root_->createSceneManager();

	root_->addFrameListener(frameListener_);


}

/*
* Inicializa SDL, flags para resizable screen, cremamos la window sdl y comprobamos
* que ha cogido bien la info. Despues inicializa la ventana de ogre con parametros
* de configuracion. 
*/
void ElHornoBase::setupWindow()
{
	if (!SDL_WasInit(SDL_INIT_EVERYTHING)) 
		SDL_InitSubSystem(SDL_INIT_EVERYTHING);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI;

	sdlWindow_ = SDL_CreateWindow("ElHorno", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (!SDL_GetWindowWMInfo(sdlWindow_, &wmInfo)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Fallo info ventana SDL (SDL2)", "ElHornoBase::setupWindow()");
	}

	Ogre::NameValuePairList params;

	//Inicializar el mapa de graphicOptions para que no de valores vacios
	params["FSAA"] = graphicOptions_["FSAA"].currentValue;
	params["vsync"] = graphicOptions_["VSync"].currentValue;
	params["gamma"] = graphicOptions_["sRGB_Gamma"].currentValue;
	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	ogreWindow_ = root_->createRenderWindow("ElHorno", screenWidth_, screenHeight_, false, &params);

	//Ocultar raton
	//SDL_SetWindowGrab(sdlWindow_, SDL_bool(false));
	//SDL_ShowCursor(false);
}

void ElHornoBase::setupRoot()
{
}

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame() {

}

Ogre::Root* ElHornoBase::getRoot()
{
	return root_;
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

Ogre::SceneManager* ElHornoBase::getSceneManager()
{
	//return SceneManager;
	return nullptr;
}

//InputManager* ElHornoBase::getInputManager()
//{
//	return nullptr;
//}

/*
Devuelve el timer que lleva el frameRenderer para ejecutar el ciclo de juego
*/
float ElHornoBase::getTime()
{
	return frameListener_->getTime();
}

/*
Devuelve el tiempo entre un frame y el anterior
*/
float ElHornoBase::deltaTime()
{
	return 	frameListener_->DeltaTime();
}

/*
Resetea el timer
*/
void ElHornoBase::resetTimer()
{
	frameListener_->resetTimer();
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

/*
* Pone o quita la pantalla completa
*/
void ElHornoBase::setFullScreen()
{
	if (fullScreen_) {
		//SDL_SetWindowFullscreen(sdlWindow_, SDL_WINDOW_FULLSCREEN);
		resizeScreen(screenWidth_, screenHeight_);
		root_->getRenderSystem()->setConfigOption("Full Screen", "Yes");
	}
	else {
		//!SDL_SetWindowFullscreen(sdlWindow_, !SDL_WINDOW_FULLSCREEN);
		resizeScreen(screenWidth_, screenHeight_);
		root_->getRenderSystem()->setConfigOption("Full Screen", "No");
	}

	fullScreen_ = !fullScreen_;
}

bool ElHornoBase::getFullScreen()
{
	return fullScreen_;
}

bool ElHornoBase::getVSync()
{
	return vSync_;
}

void ElHornoBase::setVSync(bool val)
{
	vSync_ = val;
}

void ElHornoBase::toggleVSync()
{
	if (vSync_) {
		//SDL_GL_SetSwapInterval(1);
		root_->getRenderSystem()->setConfigOption("VSync", "Yes");
	}
	else {
		//SDL_GL_SetSwapInterval(0);
		root_->getRenderSystem()->setConfigOption("VSync", "No");
	}
}

// Guarda la configuración gráfica actual
void ElHornoBase::saveGraphicOptions()
{
	std::ofstream outputFile;

#ifdef  _DEBUG
	outputFile.open("window_d.cfg");
#else
	outputFile.open("window.cfg");
#endif

	outputFile << "Render System=OpenGL Rendering Subsystem\n";
	outputFile << "[OpenGL Rendering Subsystem]\n";
	outputFile << "Colour Depth=32\n";
	outputFile << "Display Frequency=N/A\n"; 
	outputFile << "FSAA=" << graphicOptions_["FSAA"].currentValue << "\n";
	outputFile << "Full Screen=" << graphicOptions_["Fulscreen"].currentValue << "\n";
	outputFile << "RTT Preferred Mode=FBO\n";
	outputFile << "VSync=" << graphicOptions_["VSync"].currentValue << "\n";
	outputFile << "VSync Interval=1\n";
	outputFile << "Video Mode=" << graphicOptions_["Video Mode"].currentValue << "\n";
	outputFile << "sRGB Gamma Conversion=" << graphicOptions_["sRGB Gamma Conversion"].currentValue << "\n";

	outputFile.close();
}

/*
* Establece la resolución deseada
*/
void ElHornoBase::setResolution(std::string value)
{
}
/*
* Establece el gamma
*/
void ElHornoBase::setGamma(bool value)
{
}
