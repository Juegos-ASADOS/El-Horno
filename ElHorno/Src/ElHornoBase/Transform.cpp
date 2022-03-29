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

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 scal)
{ 
	pPos = pos;
	pRot = rot;
	pScal = scal;
}

Transform::~Transform()
{
	ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->destroySceneNode(node_);
	node_ = nullptr;
}

void Transform::start()
{
	node_ = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setPosition(pPos);

	//LA OTRA FORMA ESTABA ROTA (Y ESTA TAMBIÉN)
	rotateX(pRot.x);
	rotateY(pRot.y);
	rotateZ(pRot.z);
	
	
	setScale(pScal);
}

void Transform::update()
{
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