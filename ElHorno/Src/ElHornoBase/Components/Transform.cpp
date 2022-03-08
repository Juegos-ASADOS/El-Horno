#include "Transform.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "../ElHornoBase.h"

using namespace Ogre;


void Transform::start()
{
	//Aqui va la incializacion del nodo pero no estan las cosas que tienen que estar todavia
	//node = ElHornoBase::getInstance()->getSceneManager()...
}

// Getters
Vector3 Transform::getPosition()
{
	return node->getPosition();
}
Vector3 Transform::getScale()
{
	return node->getScale();
}
Quaternion Transform::getRotation()
{
	return node->getOrientation();
}

// Setters
void Transform::setPosition(Vector3 pos)
{
	node->setPosition(pos);
}
void Transform::setScale(Vector3 sca)
{
	node->setScale(sca);
}
void Transform::setRotation(Quaternion rot)
{
	node->setOrientation(rot);
}

// Funciones
void Transform::lookAt(Vector3 targetPos)
{
	node->lookAt(targetPos);
}







