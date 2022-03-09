#pragma once
#include "../ECS/Component.h"
#include <OgreVector3.h>
#include <vector>
#include <string>

class OgreCamera;
class Transform;

class HornoCamera : public Component
{
public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	HornoCamera();
	~HornoCamera();

	virtual void init() override;
	Ogre::Vector3 a;

	Ogre::Camera* getCamera();
private:
	bool lookingAt = false;
	bool following = false;
	
	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	Ogre::SceneNode* node = nullptr;
	Transform* tr_ = nullptr;
};