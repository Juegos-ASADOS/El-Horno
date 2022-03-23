#pragma once
#ifndef _AnimatorController_H
#define _AnimatorController_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>

namespace Ogre {
	class AnimationState;
	class AnimationStateSet;
}
class Mesh;
class Transform;

class AnimatorController : public Component
{
public:

	AnimatorController();
	~AnimatorController();

	void start() override;
	void update()override;

	void onEnable() override {};
	void onDisable()override {};


private:
	
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
	Ogre::AnimationState* currentState_;

};

#endif _AnimatorController_H