#include "GraphicsManager.h"
#include "InputManager.h"
#include <iostream>
#include <fstream>
#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

GraphicsManager* GraphicsManager::instance_;

GraphicsManager::GraphicsManager() {

}

GraphicsManager::~GraphicsManager()
{
	delete root_;
	SDL_Quit();
}

GraphicsManager* GraphicsManager::getInstance()
{
	return instance_;
}

bool GraphicsManager::setInstance()
{
	if (instance_ == nullptr) {
		instance_ = new GraphicsManager();
		return true;
	}
	return false;
}

void GraphicsManager::erase()
{
	delete instance_;
}

void GraphicsManager::init()
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

void GraphicsManager::start()
{
	// Si usamos renderOneFrame manualmente esto no es necesario
	root_->startRendering();
}

void GraphicsManager::exit()
{
	root_->queueEndRendering();
}

void GraphicsManager::setup()
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
void GraphicsManager::setupWindow()
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
void GraphicsManager::setupRoot()
{
	Ogre::String pluginPath;

	pluginPath = "plugins.cfg";

	if (!Ogre::FileSystemLayer::fileExists(pluginPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, pluginPath, "No existe plugins.cfg o plugins_d.cfg");
	}

	root_ = new Ogre::Root("plugins.cfg", "window.cfg");
}

void GraphicsManager::shutdown()
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
bool GraphicsManager::pollEvents()
{
	if (sdlWindow_ == nullptr)
		return false;  // SDL events not initialized
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			root_->queueEndRendering();
			return true;

			break;
		default:
			//llamar a InputManager
			InputManager::getInstance()->GeneralInputManagement(event);

			//TODO es provisional con la tecla escape se cierra el juego
			return InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE);
			break;
		}

	}
	return false;
}

void GraphicsManager::render()
{
	//Actualiza render targets
	root_->renderOneFrame();
}

void GraphicsManager::setConfigOptions()
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

Ogre::Root* GraphicsManager::getRoot()
{
	return root_;
}


Ogre::RenderWindow* GraphicsManager::getRenderWindow()
{
	return ogreWindow_;
}

SDL_Window* GraphicsManager::getSDLWindow()
{
	return sdlWindow_;
}

Ogre::SceneManager* GraphicsManager::getSceneManager()
{
	//return SceneManager;
	//HE TOCAO ESTO CUIDAO
	return ogreSceneManager_;
	//HE TOCAO ESTO
	return nullptr;
}

// actualiza el tama�o de la ventana de SDL y de CEGUI
void GraphicsManager::resizeScreen(int width, int height)
{
	//SDL_SetWindowSize(sdlWindow_, width, height);
	//sdlWindow_->windowMovedOrResized();

}

/*
* Pone o quita la pantalla completa
*/
void GraphicsManager::setFullScreen()
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

bool GraphicsManager::getFullScreen()
{
	return fullScreen_;
}

bool GraphicsManager::getVSync()
{
	return vSync_;
}

void GraphicsManager::setVSync(bool val)
{
	vSync_ = val;
}

void GraphicsManager::toggleVSync()
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


std::string GraphicsManager::getResolution()
{
	return resolution;
}

/*
* Establece la resoluci�n deseada (Podemos cambiar el formato)
*/
void GraphicsManager::setResolution(std::string value)
{
	resolution = value;

	std::stringstream mode(value);

	Ogre::String token;
	mode >> screenWidth_;
	mode >> token;
	mode >> screenHeight_;
}

int GraphicsManager::getScreenWidth()
{
	return screenWidth_;
}

int GraphicsManager::getScreenHeight()
{
	return screenHeight_;
}

std::string GraphicsManager::getFSAA()
{
	return fsaa;
}

void GraphicsManager::setFSAA(int value)
{
	fsaa = std::to_string(value);

	graphicOptions_["FSAA"].currentValue = fsaa;
}

bool GraphicsManager::getGamma()
{
	return gamma_;
}
/*
* Establece el gamma
*/
void GraphicsManager::setGamma(bool value)
{
	std::string currValue;
	currValue = value ? "Yes" : "No";
	gamma_ = value;
	graphicOptions_["sRGB Gamma Conversion"].currentValue = currValue;
}

// Guarda la configuraci�n gr�fica actual
void GraphicsManager::saveGraphicOptions()
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

void GraphicsManager::changeGraphicComponents()
{
	setFullScreen();

	graphicOptions_["Video Mode"].currentValue = resolution;

	if (graphicOptions_["VSync"].currentValue != (vSync_ ? "Yes" : "No")) {
		setVSync(vSync_);
		graphicOptions_["VSync"].currentValue = vSync_ ? "Yes" : "No";
	}

	saveGraphicOptions();
}

/*
* Devuelve los ajustes al default
*/
void GraphicsManager::revertBasicOptions()
{
}

void GraphicsManager::changeAdvancedGraphicComponents()
{
	graphicOptions_["FSAA"].currentValue = fsaa;

	graphicOptions_["sRGB Gamma Conversion"].currentValue = gamma_ ? "Yes" : "No";
}

void GraphicsManager::revertGraphicChanges()
{
	resolution = graphicOptions_["Video Mode"].currentValue;

	setResolution(resolution);

	setFullScreen();

	if (graphicOptions_["VSync"].currentValue == "Yes") {
		vSync_ = true;
	}
	else
		vSync_ = false;
}

void GraphicsManager::revertAdvancedGraphicChanges()
{
	fsaa = graphicOptions_["FSAA"].currentValue;

	if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "Yes")
		gamma_ = true;
	else if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "No")
		gamma_ = false;
}

void GraphicsManager::setFarShadowDistance(float dist)
{
	ogreSceneManager_->setShadowFarDistance(dist);
}

float GraphicsManager::getFarShadowDistance()
{
	return ogreSceneManager_->getShadowFarDistance();
}

Ogre::Entity* GraphicsManager::createEntity(std::string meshName) 
{
	return ogreSceneManager_->createEntity(meshName);
}