#pragma once
#include "../ECS/Component.h"
#include <OgreVector3.h>

namespace Ogre {
	class Vector3;
	class Quaternion;
	class SceneNode;
}

class Transform : public Component
{
public:

	Transform();

	virtual void init() override {};
	virtual void start() override {};
	virtual void update() override {};
	virtual void render() override {};

	// Getters
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getScale();
	Ogre::Quaternion getRotation();

	// Setters
	void setPosition(Ogre::Vector3 pos);
	void setScale(Ogre::Vector3 sca);
	void setRotation(Ogre::Quaternion rot);
	void lookAt(Ogre::Vector3 targetPos);


	~Transform();

	Ogre::SceneNode* getNode() { return node; }
private:

	// Variables de transformacion
	Ogre::Vector3 position_;
	Ogre::Vector3 scale_;
	Ogre::Vector3 rotation_;

	// Nodo de ogre base
	Ogre::SceneNode* node = nullptr;

};


