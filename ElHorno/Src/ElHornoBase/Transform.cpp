#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <iostream>
#include "CheckML.h"

using namespace Ogre;
namespace El_Horno {

	Transform::Transform(Vector3 pos, Vector3 rot, Vector3 scal)
	{
		pPos_ = pos;
		pRot_ = rot;
		pScal_ = scal;
	}

	Transform::~Transform()
	{
		ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->destroySceneNode(node_);
		node_ = nullptr;
	}

	/*
	Se establece la rotacion, la posicion, la escala y se muestra la bounding box (debug)
	*/
	void Transform::start()
	{
		node_ = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		setPosition(pPos_);

		rotateX(pRot_.x);
		rotateY(pRot_.y);
		rotateZ(pRot_.z);

		setScale(pScal_);

		//node_->showBoundingBox(true);
	}

	// Getters
	Vector3 Transform::getPosition()
	{
		return node_->getPosition();
	}
	Vector3 Transform::getScale()
	{
		return node_->getScale();
	}
	Quaternion Transform::getRotation()
	{
		return node_->getOrientation();
	}

	// Setters
	void Transform::setPosition(Vector3 pos)
	{
		node_->setPosition(pos);
	}

	void Transform::setScale(Vector3 sca)
	{
		node_->setScale(sca);
	}

	void Transform::setDirection(Ogre::Vector3 dir)
	{
		node_->setDirection(dir);
	}

	void Transform::setRotation(Quaternion rot)
	{
		node_->setOrientation(rot);
	}

	void Transform::setRotationAxis(Ogre::Real angle, Ogre::Vector3 axis)
	{
		node_->setOrientation(Quaternion::Quaternion(Ogre::Angle(angle), axis));
	}

	void Transform::rotateX(Ogre::Real angle)
	{
		node_->pitch(Ogre::Angle(angle));
	}

	void Transform::rotateY(Ogre::Real angle)
	{
		node_->yaw(Ogre::Angle(angle));
	}

	void Transform::rotateZ(Ogre::Real angle)
	{
		node_->roll(Ogre::Angle(angle));
	}

	// Funciones
	void Transform::lookAt(Vector3 targetPos)
	{
		node_->lookAt(targetPos, Node::TS_PARENT);
	}
}