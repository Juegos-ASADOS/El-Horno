#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <iostream>
#include "CheckMl.h"

using namespace Ogre;

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 scal)
{ 
	pPos = pos;
	pRot = rot;
	pScal = scal;
}

Transform::~Transform()
{
	delete node_;
	node_ = nullptr;
}

void Transform::start()
{
	node_ = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setPosition(pPos);

	//LA OTRA FORMA ESTABA ROTA
	setRotationAxis(pRot.x, Vector3(1,0,0));
	setRotationAxis(pRot.y, Vector3(0,1,0));
	setRotationAxis(pRot.z, Vector3(0,0,1));
	
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

// Funciones
void Transform::lookAt(Vector3 targetPos)
{
	node_->lookAt(targetPos, Node::TS_PARENT);
}