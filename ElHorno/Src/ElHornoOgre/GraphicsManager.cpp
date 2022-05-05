#include "GraphicsManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include <iostream>
#include <fstream>
#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include "CheckML.h"

namespace El_Horno {

	GraphicsManager* GraphicsManager::instance_;

	GraphicsManager::GraphicsManager() {

	}

	GraphicsManager::~GraphicsManager()
	{
		//if(debug)
		PhysicsManager::getInstance()->removeDebug();
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
		//Tamaño de la ventana
		screenWidth_ = 1920;
		screenHeight_ = 1080;

		resolutions.push_back("800x600");
		resolutions.push_back("1024x768");
		resolutions.push_back("1280x720");
		resolutions.push_back("1280x1024");
		resolutions.push_back("1650x1080");
		resolutions.push_back("1920x1080");

		currentResolution = resolutions.size() - 1;

		SDL_Init(SDL_INIT_EVERYTHING);

		// Inicializa root de Ogre
		setupRoot();

		// Si hay configuraciones cargadas o inicia desde el cuadro de config de Ogre
		if (root_->restoreConfig() || root_->showConfigDialog(nullptr))
			setup();

		setupResources();

		ogreSceneManager_->setSkyDome(true, "Examples/CloudySky", 5, 80);

		//Inicializa el debug en PhysicsManager
		//if(debug)
		PhysicsManager::getInstance()->debugStart();
	}

	void GraphicsManager::start()
	{
		// Si usamos renderOneFrame manualmente esto no es necesario
		//root_->startRendering();
	}

	void GraphicsManager::exit()
	{
		root_->queueEndRendering();
	}

	void GraphicsManager::setup()
	{
		root_->initialise(false);
		setupWindow();

		// Setup de manager de escena de ogre
		ogreSceneManager_ = root_->createSceneManager();

		ogreSceneManager_->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE); // This enables shadow
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

	void GraphicsManager::setupResources()
	{
		Ogre::String resourcesPath;

		resourcesPath = "resources.cfg";

		if (!Ogre::FileSystemLayer::fileExists(resourcesPath)) {
			OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, resourcesPath, "No existe resouces.cfg");
		}

		Ogre::ConfigFile cf;
		cf.load(resourcesPath);

		std::string sec, type, arch;
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

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
		InputManager::getInstance()->flushInput();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return true;

			InputManager::getInstance()->generalInputManagement(event);

			//switch (event.type)
			//{
			//case sdl_quit:
				//root_->queueEndRendering();
			//	return true;

			//	break;
			//default:
			//	InputManager::getInstance()->generalInputManagement(event);

			//	return false;
			//	break;
			//}

		}
		return false;
	}

	void GraphicsManager::render()
	{
		//Actualiza render targets
		root_->renderOneFrame();
		//SDL_ShowCursor(SDL_DISABLE);

	}

	void GraphicsManager::setConfigOptions()
	{
		graphicOptions_ = root_->getRenderSystem()->getConfigOptions();

		fsaa_ = graphicOptions_["FSAA"].currentValue;

		if (graphicOptions_["VSync"].currentValue == "Yes")
			vSync_ = true;
		else if (graphicOptions_["VSync"].currentValue == "No")
			vSync_ = false;

		if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "Yes")
			gamma_ = true;
		else if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "No")
			gamma_ = false;

		std::istringstream mode(graphicOptions_["Video Mode"].currentValue);
		resolution_ = graphicOptions_["Video Mode"].currentValue;

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
		return ogreSceneManager_;
	}

	// Actualiza el tamaño de la ventana de SDL y de CEGUI
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

	void GraphicsManager::setSkyBox(bool enable, std::string material, int dist, bool drawFirst)
	{
		if(ogreSceneManager_!= nullptr)
			ogreSceneManager_->setSkyBox(enable, material, dist, drawFirst);
	}

	void GraphicsManager::setSkyDome(bool enable, std::string material, int angle, int tiling)
	{
		if(ogreSceneManager_ != nullptr)
			ogreSceneManager_->setSkyDome(enable, material, angle, tiling);

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
		return resolution_;
	}

	/*
	* Establece la resolución deseada (Podemos cambiar el formato)
	*/
	void GraphicsManager::setResolution(std::string value)
	{
		resolution_ = value;

		std::stringstream mode(value);

		Ogre::String token;
		mode >> screenWidth_;
		mode >> token;
		mode >> screenHeight_;
	}

	void GraphicsManager::setResolutionUp()
	{
		if (currentResolution < resolutions.size() - 1) {
			currentResolution += 1;
		}
		resolution_ = resolutions[currentResolution];

		std::stringstream mode(resolution_);

		Ogre::String token;
		mode >> screenWidth_;
		mode >> token;
		mode >> screenHeight_;
	}

	void GraphicsManager::setResolutionDown()
	{
		if (currentResolution > 0) {
			currentResolution -= 1;
		}
		resolution_ = resolutions[currentResolution];

		std::stringstream mode(resolution_);

		Ogre::String token;
		mode >> screenWidth_;
		mode >> token;
		mode >> screenHeight_;
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
		return fsaa_;
	}

	void GraphicsManager::setFSAA(int value)
	{
		fsaa_ = std::to_string(value);

		graphicOptions_["FSAA"].currentValue = fsaa_;
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

	// Guarda la configuración gráfica actual
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

		graphicOptions_["Video Mode"].currentValue = resolution_;

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
		graphicOptions_["FSAA"].currentValue = fsaa_;

		graphicOptions_["sRGB Gamma Conversion"].currentValue = gamma_ ? "Yes" : "No";
	}

	void GraphicsManager::revertGraphicChanges()
	{
		resolution_ = graphicOptions_["Video Mode"].currentValue;

		setResolution(resolution_);

		setFullScreen();

		if (graphicOptions_["VSync"].currentValue == "Yes") {
			vSync_ = true;
		}
		else
			vSync_ = false;
	}

	void GraphicsManager::revertAdvancedGraphicChanges()
	{
		fsaa_ = graphicOptions_["FSAA"].currentValue;

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
}