#pragma once
#include "../ECS/Component.h"
#include <OgreVector3.h>



#include <vector>

using namespace Ogre;

class Transform : public Component
{
public:

	//lo uncio necesario para recoger input del teclado a traves de SDL
	Transform();

	virtual void start() {};
	virtual void update() {};
	virtual void render() {};
	Vector3 a;

	~Transform();

private:


	Vector3 position_;
	Vector3 velocity_;
	Vector3 scale_;

	SceneNode* node = nullptr;

	//pendiente de agregar mandos



};


