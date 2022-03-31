#pragma once
#ifndef _CAMERA_COMPONENT_H
#define _CAMERA_COMPONENT_H

#include "Component.h"
#include <OgreVector3.h>
#include <OgreColourValue.h>
#include <vector>
#include <string>

namespace El_Horno {
class Transform;

	class CameraComponent : public Component
	{
	public:

		//lo uncio necesario para recoger input del teclado a traves de SDL
		CameraComponent(Ogre::Vector3 pos, Ogre::Vector3 lookAt, Ogre::ColourValue color, int nearClDis, int farClDis);
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

		Ogre::Vector3 camPos;
		Ogre::Vector3 lookAtVec;
		Ogre::ColourValue bgColor;

		int nearClipDistance;
		int farClipDistance;
	};
}
#endif _CAMERA_COMPONENT_H