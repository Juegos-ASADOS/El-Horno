#include "Transform.h"
#include "OgreEntity.h"
#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "../ElHornoBase.h"

using namespace Ogre;

Transform::Transform(nlohmann::json& args)
{
	Vector3 position = Vector3(0,0,0);
	Ogre::Vector3 rotation = Vector3(0, 0, 0);
	Vector3 scale = Vector3(0, 0, 0);

	if (!args["position"].is_null())
	{
		position.x = args["position"][0];
		position.y = args["position"][1];
		position.z = args["position"][2];
	}
	if (!args["rotation"].is_null())
	{
		rotation.x = args["rotation"][0];
		rotation.y = args["rotation"][1];
		rotation.z = args["rotation"][2];
	}
	if (!args["scale"].is_null())
	{
		scale.x = args["scale"][0];
		scale.y = args["scale"][1];
		scale.z = args["scale"][2];
	}

	setPosition(position);
	setRotation(Quaternion::Quaternion(&rotation));
	setScale(scale);
}

Transform::~Transform()
{
	delete node_;
	node_ = nullptr;
}

void Transform::start()
{
	//Aqui va la incializacion del nodo pero no estan las cosas que tienen que estar todavia
	//node = ElHornoBase::getInstance()->getSceneManager()...
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