#pragma once
#include "../ECS/Component.h"
#include <OgreVector3.h>



#include <vector>

class Transform : public Component
{
public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	Transform();

	virtual void start() override {};
	virtual void update() override {};
	virtual void render() override {};
	Ogre::Vector3 a;

	~Transform();

	Ogre::SceneNode* getNode() { return node; }
private:


	Ogre::Vector3 position_;
	Ogre::Vector3 velocity_;
	Ogre::Vector3 scale_;

	Ogre::SceneNode* node = nullptr;

	//pendiente de agregar mandos



};


