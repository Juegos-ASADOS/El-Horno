#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <iostream>

using namespace Ogre;

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 scal)
{ 
	setPosition(pos);
	setRotation(Quaternion::Quaternion(&rot));
	setScale(scal);
}

Transform::~Transform()
{
	delete node_;
	node_ = nullptr;
}

void Transform::start()
{
	node_ = ElHornoBase::getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
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

// Funciones
void Transform::lookAt(Vector3 targetPos)
{
	node_->lookAt(targetPos, Node::TS_PARENT);
}