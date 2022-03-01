#pragma once
#ifndef _EL_HORNO_BASE_EL_HORNO_BASE_H
#define _EL_HORNO_BASE_EL_HORNO_BASE_H

// Ogre includes
class Ogre::Root;
class Ogre::SceneManager;
class Ogre::RenderWindow;

class SDL_Window;
class OurFrameListener;

class ElHornoBase {
public:
	void init();
	~ElHornoBase();

	// Gestion de instancias
	static ElHornoBase* getInstance();
	static bool setInstance();


	void processFrame();

private:
	void setup();

	static ElHornoBase* instance_;
	OurFrameListener* frameListener_;

	// Ogre
	Ogre::Root* root_;
	Ogre::SceneManager* ogreSceneManager_;
	Ogre::RenderWindow ogreWindow_;

	// SDL
	SDL_Window* sdlWindow_;

	// Config de pantalla
	std::map<std::string, ConfigOption> graphicOptions_,
										ConfigOption> defaultGraphicOptions_;
	int screenWidth,
		screenHeight;

	// 
	bool paused_;

};

#endif _EL_HORNO_BASE_EL_HORNO_BASE_H