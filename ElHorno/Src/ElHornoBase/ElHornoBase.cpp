// ElHornoMain.cpp

#include <iostream>
#include <fstream>
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
	delete frameListener_;
	frameListener_ = nullptr;
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
	//root_ = new Ogre::Root();
	ElHornoBullet::init();
	//ElHornoFMOD::init();

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
	pollEvents();

	// Updates de managers
	SceneManager::getInstance()->update();
}

void ElHornoBase::update()
{
	exit_ = false;

	while (!exit_) {

	}
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
	//outputFile << "FSAA=" << graphicOptions_["FSAA"].currentValue << "\n";
	/*outputFile << "Full Screen=" << graphicOptions_["Fulscreen"].currentValue << "\n";
	outputFile << "RTT Preferred Mode=FBO\n";
	outputFile << "VSync=" << graphicOptions_["VSync"].currentValue << "\n";
	outputFile << "VSync Interval=1\n";
	outputFile << "Video Mode=" << graphicOptions_["Video Mode"].currentValue << "\n";
	outputFile << "sRGB Gamma Conversion=" << graphicOptions_["sRGB Gamma Conversion"].currentValue << "\n";*/

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
//void ElHornoBase::changeBasicOptions()
//{
//
//}

/*
* Devuelve los ajustes al default
*/
//void ElHornoBase::revertBasicOptions()
//{
//}

//void ElHornoBase::changeGraphicComponents()
//{
//	setFullScreen();
//
//	graphicOptions_["Video Mode"].currentValue = resolution;
//
//	if (graphicOptions_["VSync"].currentValue != (vSync_ ? "Yes" : "No")) {
//		setVSync(vSync_);
//		graphicOptions_["VSync"].currentValue = vSync_ ? "Yes" : "No";
//	}
//
//	saveGraphicOptions();
//	saveExtraOptions();
//
//}
//
//void ElHornoBase::changeAdvancedGraphicComponents()
//{
//	graphicOptions_["FSAA"].currentValue = fsaa;
//
//	graphicOptions_["sRGB Gamma Conversion"].currentValue = gamma_ ? "Yes" : "No";
//}
//
//void ElHornoBase::revertGraphicChanges()
//{
//	resolution = graphicOptions_["Video Mode"].currentValue;
//
//	setResolution(resolution);
//
//	setFullScreen();
//
//	if (graphicOptions_["VSync"].currentValue == "Yes") {
//		vSync_ = true;
//	}
//	else
//		vSync_ = false;
//}
//
//void ElHornoBase::revertAdvancedGraphicChanges()
//{
//	fsaa = graphicOptions_["FSAA"].currentValue;
//
//	if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "Yes")
//		gamma_ = true;
//	else if (graphicOptions_["sRGB Gamma Conversion"].currentValue == "No")
//		gamma_ = false;
//}
//
//void ElHornoBase::setFarShadowDistance(float dist)
//{
//	ogreSceneManager_->setShadowFarDistance(dist);
//}
//
//float ElHornoBase::getFarShadowDistance()
//{
//	return ogreSceneManager_->getShadowFarDistance();
//}
