#pragma once
#ifndef _LightComponent_H
#define _LightComponent_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>
#include <map>

namespace Ogre {
	
}
class Mesh;
class Transform;



class LightComponent : public Component
{
public:

	LightComponent(int type);
	~LightComponent();

	void start() override;
	void update()override;

	void onEnable() override {};
	void onDisable()override {};



private:

	// Acceso al nodo, Entidad de Ogre y Transform
	Ogre::SceneNode* node_;
	Ogre::Entity* ogreEntity_;
	Transform* tr_ = nullptr;

	// Luz de ogre
	Ogre::Light* light_;

};

#endif _LightComponent_H