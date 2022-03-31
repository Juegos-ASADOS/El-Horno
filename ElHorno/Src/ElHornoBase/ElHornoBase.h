#pragma once
#ifndef _EL_HORNO_BASE_EL_HORNO_BASE_H
#define _EL_HORNO_BASE_EL_HORNO_BASE_H

#include <map>
#include <string>
#include "json.hpp"

namespace El_Horno {

	class AudioManager;
	class GraphicsManager;
	class InputManager;
	class UIManager;
	class Timer;
	class SceneManager;

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
		void processFrame(const float dt);
		void update();

		// Managers
		//GUI_Manager* getGUIManager();
		//ResourceManager* getResourceManager();
		static SceneManager* getSceneManager();
		static InputManager* getInputManager();
		static GraphicsManager* getGraphicsManager();
		static AudioManager* getAudioManager();
		static UIManager* getUIManager();

		// Esto ahora lo lleva Timer (excepto deltaTime que lo lleva el bucle)
		/*float getTime();
		float deltaTime();
		void resetTimer();*/
		Timer* getGlobalTime();

		void pause();
		bool isPaused();

		void setInvertedAxisX(bool value);
		void setInvertedAxisY(bool value);
		bool getInvertedAxisXInput();
		bool getInvertedAxisYInput();
		bool getInvertedAxisXTemp();
		bool getInvertedAxisYTemp();

		void changeBasicOptions();

	private:
		void setup();

		static ElHornoBase* instance_;

		void cleanScene();

		void extraConfig(nlohmann::json& j);
		void setupFactories();

		bool paused_,
			invertedAxisX_,
			invertedAxisY_,
			exit_;

		Timer* globalTimer_;

		nlohmann::json ExtraConfig;
	};
}
#endif _EL_HORNO_BASE_EL_HORNO_BASE_H