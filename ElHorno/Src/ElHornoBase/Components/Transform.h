#pragma once
#include "../ECS/Component.h"
#include "../json.hpp"
#include <OgreVector3.h>

namespace Ogre {}

class Transform : public Component
{
public:
	Transform(nlohmann::json& args);
	~Transform();

	virtual void start() override;
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

	Ogre::SceneNode* getNode() { return node_; }
private:
	// Nodo de ogre base
	Ogre::SceneNode* node_ = nullptr;
};


