#pragma once
#ifndef _AnimatorController_H
#define _AnimatorController_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>
#include <map>

namespace Ogre {
	class AnimationState;
	class AnimationStateSet;
	class Entity;
	class SceneNode;
}

using TransitionMap = std::map<std::string, bool>;
using AnimationStateMachine = std::map<std::string, TransitionMap>;

struct AnimationStateInfo
{
	Ogre::AnimationState* state;
	std::string name;
};

namespace El_Horno {
	class Mesh;
	class Transform;

	class _declspec(dllexport) AnimatorController : public Component
	{
	public:

		AnimatorController(std::vector<std::pair<std::string, std::string>> animVector);
		AnimatorController();
		~AnimatorController();

		virtual void setParameters(std::vector<std::pair<std::string, std::string>> animVector) override;
		virtual void start() override;
		void update()override;

		// Setters
		void setAnimBool(std::string state, std::string conditionName, bool value);

		// Getters
		bool getAnimBool(std::string state, std::string conditionName);
		bool getHasEnded();

		void onEnable() override {};
		void onDisable()override {};

	private:

		// es un mapa con el estado y sus transiciones si es que tiene
		// nombre del estado   //nombre de la transicion
		AnimationStateMachine animationStateMachine_;

		// Acceso al nodo, Entidad de Ogre y Transform
		Ogre::SceneNode* node_;
		Ogre::Entity* ogreEntity_;
		Transform* tr_ = nullptr;
		Mesh* mesh_ = nullptr;

		// Mapa de Ogre con todas las animaciones de la malla 
		Ogre::AnimationStateSet* animStatesMap_;
		/* PARA RECORRER EL MAPA EN CASO NECESARIO
		auto it = animStatesMap_->getAnimationStateIterator().begin();
		while (it != animStatesMap_->getAnimationStateIterator().end())
		{
			auto s = it->first; ++it;
		}
		*/

		// Estado actual
		AnimationStateInfo currentState_;

		//// es un mapa con el estado y sus transiciones si es que tiene
		////nombre del estado   //nombre de la transicion
		//std::map<std::string, std::map<std::string, Transition*>> transitionsMap_;

		void manageTransitions();

	};
}
#endif _AnimatorController_H