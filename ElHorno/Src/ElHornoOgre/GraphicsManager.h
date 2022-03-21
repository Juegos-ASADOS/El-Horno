#pragma once
#ifndef _GRAPHICS_MANAGER_GRAPHICS_MANAGER_H
#define _GRAPHICS_MANAGER_GRAPHICS_MANAGER_H

#include <string>
#include <map>

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
	class Entity;
	struct ConfigOption;
};

// Ogre includes

class SDL_Window;
class OurFrameListener;

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	static GraphicsManager* getInstance();
	static bool setInstance();
	static void erase();

	void init();
	void start();
	void exit();
	void setup();
	bool pollEvents();

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

	void saveGraphicOptions();
	void revertBasicOptions();
	void changeGraphicComponents();
	void changeAdvancedGraphicComponents();
	void revertGraphicChanges();
	void revertAdvancedGraphicChanges();

	void setFarShadowDistance(float dist);
	float getFarShadowDistance();
	//void setShadowTechnique(Ogre::ShadowTechnique type);
	//Ogre::ShadowTechnique getShadowTechnique();
	Ogre::Entity* createEntity(std::string meshName);

private:

	static GraphicsManager* instance_;

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

#endif _GRAPHICS_MANAGER_GRAPHICS_MANAGER_H



