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
#include <string>
#include <vector>

using namespace Ogre;
namespace El_Horno {

	Transform::Transform(HornoVector3 pos, HornoVector3 rot, HornoVector3 scal, bool bAttach)
	{
		pPos_ = HornoVectorToOgre(pos);
		pRot_ = HornoVectorToOgre(rot);
		pScal_ = HornoVectorToOgre(scal);
		boneAttached_ = bAttach;
	}

	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
		if (!boneAttached_) {
			ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->destroySceneNode(node_);
			node_ = nullptr;
		}
	}

	void Transform::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "position") {
				pPos_ = StringToVector(parameters[i].second);
			}
			else if (parameters[i].first == "rotation") {
				pRot_ = StringToVector(parameters[i].second);
			}
			else if (parameters[i].first == "scale") {
				pScal_ = StringToVector(parameters[i].second);
			}
		}
	}

	void Transform::awake()
	{
		if (!boneAttached_) {
			Ogre::SceneNode* parent = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode();
			Ogre::Vector3 parPos = { 0,0,0 };
			if (entity_->getParent() != nullptr) {
				Transform* pTr = entity_->getParent()->getComponent<Transform>("transform");
				parent = pTr->getNode();
			}

			node_ = parent->createChildSceneNode();

			setPosition(parPos + pPos_);

			rotateX(pRot_.x);
			rotateY(pRot_.y);
			rotateZ(pRot_.z);

			setScale(pScal_);
		}
		//node_->showBoundingBox(true);
	}

	/*
	Se establece la rotacion, la posicion, la escala y se muestra la bounding box (debug)
	*/
	void Transform::start()
	{
	}

	// Getters
	Vector3 Transform::getPosition() //Local
	{
		return node_->getPosition();
	}
	Vector3 Transform::getGlobalPosition() //Global
	{
		return node_->getParent()->convertLocalToWorldPosition(node_->getPosition());
	}
	HornoVector3 Transform::getHornoGlobalPosition()
	{
		return OgreVectorToHorno(node_->getParent()->convertLocalToWorldPosition((node_->getPosition())));
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

	void Transform::setGlobalPosition(Ogre::Vector3 pos)
	{
		node_->setPosition(node_->getParent()->convertWorldToLocalPosition(pos));
	}

	void Transform::addPosition(Ogre::Vector3 pos)
	{
		pPos_ += pos;
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
		pRot_.x = angle;
		node_->pitch(Ogre::Angle(angle));
	}

	void Transform::rotateY(Ogre::Real angle)
	{
		pRot_.y += angle;
		node_->yaw(Ogre::Angle(angle));
	}

	void Transform::rotateZ(Ogre::Real angle)
	{
		pRot_.z += angle;
		node_->roll(Ogre::Angle(angle));
	}

	// Funciones
	void Transform::lookAt(Vector3 targetPos)
	{
		node_->lookAt(targetPos, Node::TS_PARENT);
	}
}