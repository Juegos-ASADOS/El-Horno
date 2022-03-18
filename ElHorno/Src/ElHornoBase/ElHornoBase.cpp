// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <iostream>
#include <fstream>

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include "ElHornoBase.h"
#include "ElHornoBullet.h"
#include "ElHornoFMOD.h"
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
	frameListener_ = new OurFrameListener();
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
	//ESTO ES UNA PRUEBA
	screenWidth_ = 1280;
	screenHeight_ = 720;

	//root_ = new Ogre::Root();
	ElHornoBullet::init();
	//ElHornoFMOD::init();
	SDL_Init(SDL_INIT_EVERYTHING);

	// Aqui se inicializan las instancias de todos los managers
	FactoryCreator::setupInstance();
	//Creacion del factoryCreator y declaracion de los componentes del motor
	setupFactories();

	SceneManager::setupInstance();

	// Inicializa root de Ogre
	setupRoot();

	// Si hay configuraciones cargadas o inicia desde el cuadro de config de Ogre
	if (root_->restoreConfig() || root_->showConfigDialog(nullptr))
		setup();

	setupResources();
}

/*
Ejecuta el start del SceenManager y comienza el renderizado de Ogre
*/
void ElHornoBase::start()
{
	SceneManager::getInstance()->getCurrentScene()->start();
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

	setupWindow();

	// Setup de managers


	ogreSceneManager_ = root_->createSceneManager();

	root_->addFrameListener(frameListener_);


}

/*
Limpia la escena desde el SceneManager
*/
void ElHornoBase::cleanScene()
{
}

/*
* Inicializa SDL, flags para resizable screen, cremamos la window sdl y comprobamos
* que ha cogido bien la info. Despues inicializa la ventana de ogre con parametros
* de configuracion.
*/
void ElHornoBase::setupWindow()
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
void ElHornoBase::setupRoot()
{
	Ogre::String pluginPath;

	pluginPath = "plugins.cfg";

	if (!Ogre::FileSystemLayer::fileExists(pluginPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, pluginPath, "No existe plugins.cfg o plugins_d.cfg");
	}

	root_ = new Ogre::Root("plugins.cfg", "window.cfg");
}

void ElHornoBase::setupResources()
{
	Ogre::String resourcesPath;

	resourcesPath = "resources.cfg";

	if (!Ogre::FileSystemLayer::fileExists(resourcesPath)) {
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, resourcesPath, "No existe resouces.cfg");
	}

	Ogre::ConfigFile cf;
	cf.load(resourcesPath);

	// go through all specified resource groups
	std::string sec, type, arch;
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++) {
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void ElHornoBase::shutdown()
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
void ElHornoBase::pollEvents()
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

void ElHornoBase::setConfigOptions()
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

/*OgreRoot llama a frameListener_ que llama a processFrame que actualiza
la instancia de cada manager dependiendo del estado del juego*/
void ElHornoBase::processFrame() {
	pollEvents();

	// Updates de managers
	SceneManager::getInstance()->update();
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

Ogre::SceneManager* ElHornoBase::getSceneManager()
{
	//return SceneManager;
	//HE TOCAO ESTO CUIDAO
	return ogreSceneManager_;
	//HE TOCAO ESTO
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
Devuelve en json opciones de ejes invertidos de input manager
y volumenes de musica (a espera de crear estos managers)
*/
nlohmann::json ElHornoBase::saveExtraOptions()
{
	return nlohmann::json();
}

std::string ElHornoBase::getResolution()
{
	return resolution;
}

/*
* Establece la resolución deseada (Podemos cambiar el formato)
*/
void ElHornoBase::setResolution(std::string value)
{
	resolution = value;

	std::stringstream mode(value);

	Ogre::String token;
	mode >> screenWidth_;
	mode >> token;
	mode >> screenHeight_;
}

int ElHornoBase::getScreenWidth()
{
	return screenWidth_;
}

int ElHornoBase::getScreenHeight()
{
	return screenHeight_;
}

std::string ElHornoBase::getFSAA()
{
	return fsaa;
}

void ElHornoBase::setFSAA(int value)
{
	fsaa = std::to_string(value);

	graphicOptions_["FSAA"].currentValue = fsaa;
}

bool ElHornoBase::getGamma()
{
	return gamma_;
}
/*
* Establece el gamma
*/
void ElHornoBase::setGamma(bool value)
{
	std::string currValue;
	currValue = value ? "Yes" : "No";
	gamma_ = value;
	graphicOptions_["sRGB Gamma Conversion"].currentValue = currValue;
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
* Devuelve los ajustes al default
*/
void ElHornoBase::revertBasicOptions()
{
}

void ElHornoBase::changeGraphicComponents()
{
	setFullScreen();

	graphicOptions_["Video Mode"].currentValue = resolution;

	if (graphicOptions_["VSync"].currentValue != (vSync_ ? "Yes" : "No")) {
		setVSync(vSync_);
		graphicOptions_["VSync"].currentValue = vSync_ ? "Yes" : "No";
	}

	saveGraphicOptions();
	saveExtraOptions();

}

void ElHornoBase::changeAdvancedGraphicComponents()
{
	graphicOptions_["FSAA"].currentValue = fsaa;

	graphicOptions_["sRGB Gamma Conversion"].currentValue = gamma_ ? "Yes" : "No";
}

void ElHornoBase::revertGraphicChanges()
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

void ElHornoBase::revertAdvancedGraphicChanges()
{
	fsaa = graphicOptions_["FSAA"].currentValue;

	if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "Yes")
		gamma_ = true;
	else if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "No")
		gamma_ = false;
}

void ElHornoBase::setFarShadowDistance(float dist)
{
	ogreSceneManager_->setShadowFarDistance(dist);
}

float ElHornoBase::getFarShadowDistance()
{
	return ogreSceneManager_->getShadowFarDistance();
}
