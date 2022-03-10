#pragma once
#ifndef _EL_HORNO_BASE_EL_HORNO_BASE_H
#define _EL_HORNO_BASE_EL_HORNO_BASE_H

#include <map>
#include <string>
#include "json.hpp"

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
	struct ConfigOption;
};

// Ogre includes

class SDL_Window;
class OurFrameListener;

class ElHornoBase {
public:
	ElHornoBase();
	~ElHornoBase();

	// Gestion de instancias
	static ElHornoBase* getInstance();
	static bool setInstance();
	static void erase();

	void init();

	void start();
	void exit();
	void processFrame();

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSceneManager();
	Ogre::RenderWindow* getRenderWindow();
	SDL_Window* getSDLWindow();
	//GUI_Manager* getGUIManager();
	//ResourceManager* getResourceManager();

	//Propios
	//SceneManager* getSceneManager();
	//InputManager* getInputManager();
	//AudioManager* getAudioManager();

	float getTime();
	float deltaTime();
	void resetTimer();

	void pause();
	bool isPaused();

	void resizeScreen(int width, int height);
	void setFullScreen();
	bool getFullScreen();

	bool getVSync();
	void setVSync(bool val);
	void toggleVSync();
	void saveGraphicOptions();
	nlohmann::json saveExtraOptions();
	std::string getResolution();
	void setResolution(std::string value);
	int getScreenWidth();
	int getScreenHeight();
	std::string getFSAA();
	void setFSAA(int value);
	bool getGamma();
	void setGamma(bool value);

	void setInvertedAxisX(bool value);
	void setInvertedAxisY(bool value);
	bool getInvertedAxisXInput();
	bool getInvertedAxisYInput();
	bool getInvertedAxisXTemp();
	bool getInvertedAxisYTemp();

	void changeBasicOptions();
	void revertBasicOptions();
	void changeGraphicComponents();
	void changeAdvancedGraphicComponents();
	void revertGraphicChanges();
	void revertAdvancedGraphicChanges();

	void setFarShadowDistance(float dist);
	//void setShadowTechnique(Ogre::ShadowTechnique type);
	float getFarShadowDistance();
	//Ogre::ShadowTechnique getShadowTechnique();

private:
	void setup();

	static ElHornoBase* instance_;
	OurFrameListener* frameListener_;

	void cleanScene();

	void setupWindow();
	void setupRoot();
	
	void shutdown();
	void pollEvents();
	void extraConfig(nlohmann::json& j);
	void setupFactories();

	void setConfigOptions();

	// Ogre
	Ogre::Root* root_;
	Ogre::SceneManager* ogreSceneManager_;
	Ogre::RenderWindow* ogreWindow_;

	// SDL
	SDL_Window* sdlWindow_;

	// Config de pantalla
	std::map<std::string, Ogre::ConfigOption> graphicOptions_;

	std::string resolution,
				fsaa;
	int screenWidth_,
		screenHeight_;

	bool paused_,
		fullScreen_,
		vSync_,
		gamma_,
		invertedAxisX_,
		invertedAxisY_;

	nlohmann::json ExtraConfig;
};

#endif _EL_HORNO_BASE_EL_HORNO_BASE_H