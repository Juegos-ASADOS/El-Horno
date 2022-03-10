#pragma once
#ifndef _CAMERA_COMPONENT_H
#define _CAMERA_COMPONENT_H

#include "Component.h"
#include <OgreVector3.h>
#include <vector>
#include <string>
#include "json.hpp"

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

#endif _CAMERA_COMPONENT_H