#pragma once
#ifndef _HORNOCAMERA_H
#define _HORNOCAMERA_H

#include "../ECS/Component.h"
#include <OgreVector3.h>
#include <vector>
#include <string>
#include "../json.hpp"

class OgreCamera;
class Transform;

class CameraComponent : public Component
{
public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	CameraComponent(nlohmann::json& args);
	~CameraComponent();

	virtual void start() override;
	Ogre::Vector3 a;

	Ogre::Camera* getCamera();
private:
	bool lookingAt = false;
	bool following = false;
	
	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	Ogre::SceneNode* node = nullptr;
	Transform* tr_ = nullptr;
};

#endif _HORNOCAMERA_H