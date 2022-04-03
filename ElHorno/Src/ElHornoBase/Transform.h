#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Component.h"
#include <OgreVector3.h>

namespace El_Horno {

	class Transform : public Component
	{
	public:
		Transform(Ogre::Vector3 pos, Ogre::Vector3 rot, Ogre::Vector3 scal);
		~Transform();

		virtual void start() override;
		virtual void render() override {};

		// Getters
		Ogre::Vector3 getPosition();
		Ogre::Vector3 getScale();
		Ogre::Quaternion getRotation();
		Ogre::SceneNode* getNode() { return node_; }

		// Setters
		void setPosition(Ogre::Vector3 pos);
		void setScale(Ogre::Vector3 sca);
		void setDirection(Ogre::Vector3 dir);
		void setRotation(Ogre::Quaternion rot);
		void setRotationAxis(Ogre::Real angle, Ogre::Vector3 axis);
		void rotateX(Ogre::Real angle);
		void rotateY(Ogre::Real angle);
		void rotateZ(Ogre::Real angle);
		void lookAt(Ogre::Vector3 targetPos);

	private:
		// Nodo de ogre base
		Ogre::SceneNode* node_ = nullptr;

		Ogre::Vector3 pPos_;
		Ogre::Vector3 pRot_;
		Ogre::Vector3 pScal_;
	};
}
#endif _TRANSFORM_H