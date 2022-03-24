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
}
class Mesh;
class Transform;

// info del siguiente estado y de la condicion para que pase
struct Transition
{
	std::string nextState;
	bool cond;
};

struct AnimationStateInfo
{
	Ogre::AnimationState* state;
	std::string name;
};


class AnimatorController : public Component
{
public:

	AnimatorController();
	~AnimatorController();

	void start() override;
	void update()override;

	void onEnable() override {};
	void onDisable()override {};

	// Setters
	void setAnimBool(std::string, bool cond_, int numCond);
	
	// Getters
	bool getAnimBool(std::string state, int numCond);


private:
	
	// Maneja el cambio de estados
	void manageTransitions();

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

	// es un mapa con el estado y sus transicion si es que tiene
	// el orden en el que metes las transciones en el vector influye para decidir si un estado es mas importante que otro
	std::map<std::string, std::vector<Transition>> transitionsMap_;
	//nombre del estado   //nombre de la transicion
	std::map<std::string, std::map<std::string, Transition>> transitionsMap2_;

};

#endif _AnimatorController_H