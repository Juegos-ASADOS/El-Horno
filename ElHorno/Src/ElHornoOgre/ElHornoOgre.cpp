#include "ElHornoOgre.h"
#include <iostream>
#include <fstream>
#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

ElHornoOgre* ElHornoOgre::instance_;

ElHornoOgre::~ElHornoOgre()
{
	delete root_;
	SDL_Quit();
}

ElHornoOgre* ElHornoOgre::getInstance()
{
	return instance_;
}

bool ElHornoOgre::setInstance()
{
	if (instance_ == nullptr) {
		instance_ = new ElHornoOgre();
		return true;
	}
	return false;
}

void ElHornoOgre::erase()
{
	delete instance_;
}

void ElHornoOgre::init()
{
	//ESTO ES UNA PRUEBA
	screenWidth_ = 1280;
	screenHeight_ = 720;

	SDL_Init(SDL_INIT_EVERYTHING);

	// Inicializa root de Ogre
	setupRoot();

	// Si hay configuraciones cargadas o inicia desde el cuadro de config de Ogre
	if (root_->restoreConfig() || root_->showConfigDialog(nullptr))
		setup();
}

void ElHornoOgre::start()
{
	root_->startRendering();
}

void ElHornoOgre::exit()
{
	root_->queueEndRendering();
}

void ElHornoOgre::setup()
{
	root_->initialise(false);
	setupWindow();

	// Setup de managers


	ogreSceneManager_ = root_->createSceneManager();
}

/*
* Inicializa SDL, flags para resizable screen, cremamos la window sdl y comprobamos
* que ha cogido bien la info. Despues inicializa la ventana de ogre con parametros
* de configuracion.
*/
void ElHornoOgre::setupWindow()
{
	setConfigOptions();

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
	params["VSync"] = graphicOptions_["VSync"].currentValue;
	params["sRGB Gamma Conversion"] = graphicOptions_["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	ogreWindow_ = root_->createRenderWindow("ElHorno", screenWidth_, screenHeight_, false, &params);

	//Ocultar raton
	//SDL_SetWindowGrab(sdlWindow_, SDL_bool(false));
	//SDL_ShowCursor(false);
}

/*
* Setter de ogre root utilizando archivo plugins, si este no existe se lanza una excepcion de ogre.
*/
void ElHornoOgre::setupRoot()
{
	Ogre::String pluginPath;

	pluginPath = "plugins.cfg";

	if (!Ogre::FileSystemLayer::fileExists(pluginPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, pluginPath, "No existe plugins.cfg o plugins_d.cfg");
	}

	root_ = new Ogre::Root("plugins.cfg", "window.cfg");
}

void ElHornoOgre::shutdown()
{
	if (ogreWindow_ != nullptr)
	{
		//root_->destroyRenderTarget(ogreWindow_);
		ogreWindow_ = nullptr;
	}

	if (sdlWindow_ != nullptr)
	{
		SDL_DestroyWindow(sdlWindow_);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		sdlWindow_ = nullptr;
	}
}

/*
Gestion de eventos por input
*/
void ElHornoOgre::pollEvents()
{
	if (sdlWindow_ == nullptr)
		return;  // SDL events not initialized
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			root_->queueEndRendering();
			break;
		default:
			//llamar a InputManager
			//InputManager::getInstance()->GeneralInputManagement(event);
			break;
		}
	}
}

void ElHornoOgre::setConfigOptions()
{
	graphicOptions_ = root_->getRenderSystem()->getConfigOptions();

	fsaa = graphicOptions_["FSAA"].currentValue;

	if (graphicOptions_["VSync"].currentValue == "Yes")
		vSync_ = true;
	else if (graphicOptions_["VSync"].currentValue == "No")
		vSync_ = false;

	if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "Yes")
		gamma_ = true;
	else if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "No")
		gamma_ = false;

	std::istringstream mode(graphicOptions_["Video Mode"].currentValue);
	resolution = graphicOptions_["Video Mode"].currentValue;

	//TEMPORAL HASTA QUE SE PUEDA LEER EL CONFIG
	/*Ogre::String token;
	mode >> screenWidth_;
	mode >> token;
	mode >> screenHeight_;*/
}

Ogre::Root* ElHornoOgre::getRoot()
{
	return root_;
}


Ogre::RenderWindow* ElHornoOgre::getRenderWindow()
{
	return ogreWindow_;
}

SDL_Window* ElHornoOgre::getSDLWindow()
{
	return sdlWindow_;
}

Ogre::SceneManager* ElHornoOgre::getSceneManager()
{
	//return SceneManager;
	//HE TOCAO ESTO CUIDAO
	return ogreSceneManager_;
	//HE TOCAO ESTO
	return nullptr;
}

// actualiza el tamaño de la ventana de SDL y de CEGUI
void ElHornoOgre::resizeScreen(int width, int height)
{
	//SDL_SetWindowSize(sdlWindow_, width, height);
	//sdlWindow_->windowMovedOrResized();

}

/*
* Pone o quita la pantalla completa
*/
void ElHornoOgre::setFullScreen()
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

bool ElHornoOgre::getFullScreen()
{
	return fullScreen_;
}

bool ElHornoOgre::getVSync()
{
	return vSync_;
}

void ElHornoOgre::setVSync(bool val)
{
	vSync_ = val;
}

void ElHornoOgre::toggleVSync()
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


std::string ElHornoOgre::getResolution()
{
	return resolution;
}

/*
* Establece la resolución deseada (Podemos cambiar el formato)
*/
void ElHornoOgre::setResolution(std::string value)
{
	resolution = value;

	std::stringstream mode(value);

	Ogre::String token;
	mode >> screenWidth_;
	mode >> token;
	mode >> screenHeight_;
}

int ElHornoOgre::getScreenWidth()
{
	return screenWidth_;
}

int ElHornoOgre::getScreenHeight()
{
	return screenHeight_;
}

std::string ElHornoOgre::getFSAA()
{
	return fsaa;
}

void ElHornoOgre::setFSAA(int value)
{
	fsaa = std::to_string(value);

	graphicOptions_["FSAA"].currentValue = fsaa;
}

bool ElHornoOgre::getGamma()
{
	return gamma_;
}
/*
* Establece el gamma
*/
void ElHornoOgre::setGamma(bool value)
{
	std::string currValue;
	currValue = value ? "Yes" : "No";
	gamma_ = value;
	graphicOptions_["sRGB Gamma Conversion"].currentValue = currValue;
}
