#pragma once
#include "../ECS/Component.h"
#include <OgreVector3.h>
#include <vector>
#include <OgreCamera.h>

class HornoCamera : public Component
{
public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	HornoCamera();

	virtual void start() override {};
	virtual void update() override {};
	virtual void render() override {};
	Ogre::Vector3 a;

	~HornoCamera();

private:


	
	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	Ogre::SceneNode* node = nullptr;

	//pendiente de agregar mandos



};


