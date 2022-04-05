#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Component.h"
#include <OgreVector3.h>
#include "HornoVector3.h"
#include "HornoConversions.h"

namespace El_Horno {

	class _declspec(dllexport) Transform : public Component
	{
	public:
		Transform(HornoVector3 pos, HornoVector3 rot, HornoVector3 scal);
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
		inline void setPosition(const HornoVector3 & pos) { setPosition(HornoVectorToOgre(pos)); };

		void setScale(Ogre::Vector3 sca);
		inline void setScale(const HornoVector3 & sca) { setScale(HornoVectorToOgre(sca)); };

		void setDirection(Ogre::Vector3 dir);
		inline void setDirection(const HornoVector3 & dir) { setDirection(HornoVectorToOgre(dir)); };

		void setRotation(Ogre::Quaternion rot);
		void setRotationAxis(Ogre::Real angle, Ogre::Vector3 axis);
		inline void setRotationAxis(Ogre::Real angle, const HornoVector3 & axis) { setRotationAxis(angle, HornoVectorToOgre(axis)); };

		void rotateX(Ogre::Real angle);
		void rotateY(Ogre::Real angle);
		void rotateZ(Ogre::Real angle);
		void lookAt(Ogre::Vector3 targetPos);
		inline void lookAt(const El_Horno::HornoVector3 & targetPos) { lookAt(HornoVectorToOgre(targetPos)); };

	private:
		// Nodo de ogre base
		Ogre::SceneNode* node_ = nullptr;

		Ogre::Vector3 pPos_;
		Ogre::Vector3 pRot_;
		Ogre::Vector3 pScal_;
	};
}
#endif _TRANSFORM_H