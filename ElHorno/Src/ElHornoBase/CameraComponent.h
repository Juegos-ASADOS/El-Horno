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
class HornoVector3;

	class _declspec(dllexport) CameraComponent : public Component
	{
	public:

		//lo uncio necesario para recoger input del teclado a traves de SDL
		CameraComponent(HornoVector3 pos, HornoVector3 lookAt, HornoVector3 color, float alpha, int nearClDis, int farClDis);
		~CameraComponent();

		virtual void start() override;

		Ogre::Camera* getCamera();
	private:
		bool lookingAt = false;
		bool following = false;

		Ogre::Camera* camera_;
		Ogre::Viewport* viewport_;
		Transform* tr_ = nullptr;

		Ogre::Vector3 camPos_;
		Ogre::Vector3 lookAtVec_;
		Ogre::ColourValue bgColor_;

		int nearClipDistance_;
		int farClipDistance_;
	};
}
#endif _CAMERA_COMPONENT_H