#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <iostream>
#include "Entity.h"
#include "CheckML.h"

using namespace Ogre;
namespace El_Horno {

	Transform::Transform(HornoVector3 pos, HornoVector3 rot, HornoVector3 scal)
	{
		pPos_ = HornoVectorToOgre(pos);
		pRot_ = HornoVectorToOgre(rot);
		pScal_ = HornoVectorToOgre(scal);
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
		Ogre::SceneNode* parent = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode();
		Ogre::Vector3 parPos = { 0,0,0 };
		if (entity_->getParent() != nullptr) {
			Transform* pTr = entity_->getParent()->getComponent<Transform>("transform");
			parent = pTr->getNode();
			//parPos = pTr->getPosition();
		}
		
		node_ = parent->createChildSceneNode();
		setPosition(parPos + pPos_);

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