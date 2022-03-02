#pragma once
#ifndef _EL_HORNO_BASE_EL_HORNO_BASE_H
#define _EL_HORNO_BASE_EL_HORNO_BASE_H

#include <map>
#include <string>

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
	void setFullScreen(bool fullScreen);
	bool getFullScreen();

	bool getVSync();
	std::string getVSync(bool value);
	void setVSync(bool value);
	void setVSync(std::string value);
	void setVSyncOn();
	void setVSyncOff();
	void writeGraphicOptions();
	json writeExtraOptions();
	std::string getScreenProportion();
	std::string getFullScreen(bool value);
	void setScreenProportion(std::string value);
	void setScreenProportion(int height);
	std::string getResolution();
	void setResolution(std::string value);
	int getScreenWidth();
	int getScreenHeight();
	std::string getFSAA();
	void setFSAA(int value);
	void setFSAA(std::string value);
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
	void setShadowTechnique(Ogre::ShadowTechnique type);
	float getFarShadowDistance();
	Ogre::ShadowTechnique getShadowTechnique();

	//void setVolumeSFX(float value);
	//float getVolumeSFX();
	//void setVolumeMusic(float value);
	//float getVolumeMusic();
private:
	ElHornoBase();
	void setup();

	static ElHornoBase* instance_;
	OurFrameListener* frameListener_;

	void currentSceneCleanup();

	void setupWindow(std::string windowName);
	void setupRoot();
	void setup();
	void shutdown();
	void pollEvents();
	//void extraConfig(json& j);
	void setupFactories();

	// Ogre
	Ogre::Root* root_;
	Ogre::SceneManager* ogreSceneManager_;
	Ogre::RenderWindow* ogreWindow_;

	// SDL
	SDL_Window* sdlWindow_;

	// Config de pantalla
	std::map<std::string, Ogre::ConfigOption> graphicOptions_, 
										defaultGraphicOptions_;
	int screenWidth,
		screenHeight;

	// 
	bool paused_;

	//json ExtraConfig;
	//json BackupExtraConfig;

};

#endif _EL_HORNO_BASE_EL_HORNO_BASE_H