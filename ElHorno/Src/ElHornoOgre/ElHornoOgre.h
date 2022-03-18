#pragma once
#ifndef _EL_HORNO_OGRE_EL_HORNO_OGRE_H
#define _EL_HORNO_OGRE_EL_HORNO_OGRE_H

#include <string>
#include <map>

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
	struct ConfigOption;
};

// Ogre includes

class SDL_Window;
class OurFrameListener;

class ElHornoOgre
{
public:
	ElHornoOgre() {};
	~ElHornoOgre();

	static ElHornoOgre* getInstance();
	static bool setInstance();
	static void erase();

	void init();
	void start();
	void exit();
	void setup();
	void pollEvents();

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSceneManager();
	Ogre::RenderWindow* getRenderWindow();
	SDL_Window* getSDLWindow();

	void resizeScreen(int width, int height);
	void setFullScreen();
	bool getFullScreen();

	bool getVSync();
	void setVSync(bool val);
	void toggleVSync();

	std::string getResolution();
	void setResolution(std::string value);
	int getScreenWidth();
	int getScreenHeight();
	std::string getFSAA();
	void setFSAA(int value);
	bool getGamma();
	void setGamma(bool value);

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

	static ElHornoOgre* instance_;

	void setupWindow();
	void setupRoot();

	void shutdown();

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

	bool fullScreen_,
		vSync_,
		gamma_;
};

#endif _EL_HORNO_OGRE_EL_HORNO_OGRE_H



