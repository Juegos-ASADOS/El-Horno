#pragma once
#ifndef _EL_HORNO_BASE_EL_HORNO_BASE_H
#define _EL_HORNO_BASE_EL_HORNO_BASE_H

#include <map>
#include <string>
#include "json.hpp"

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
	void update();

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

	void saveGraphicOptions();
	nlohmann::json saveExtraOptions();

	void setInvertedAxisX(bool value);
	void setInvertedAxisY(bool value);
	bool getInvertedAxisXInput();
	bool getInvertedAxisYInput();
	bool getInvertedAxisXTemp();
	bool getInvertedAxisYTemp();

private:
	void setup();

	static ElHornoBase* instance_;
	OurFrameListener* frameListener_;

	void cleanScene();
	
	void pollEvents();
	void extraConfig(nlohmann::json& j);
	void setupFactories();

	bool paused_,
		invertedAxisX_,
		invertedAxisY_,
		exit_;

	nlohmann::json ExtraConfig;
};

#endif _EL_HORNO_BASE_EL_HORNO_BASE_H