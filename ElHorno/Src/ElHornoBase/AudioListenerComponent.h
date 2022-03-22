#pragma once
#ifndef _AudioListenerComponent_H
#define _AudioListenerComponent_H

#include <string>
#include "Component.h"

namespace Ogre {
	/*class AxisAlignedBox;
	class Entity;
	class Mesh;*/
	//class Camera;
	class Vector3;
}

class AudioListenerComponent : public Component
{
public:

	AudioListenerComponent();
	~AudioListenerComponent();

	//void start() override;
	void update()override;

	void onEnable() override {};
	void onDisable()override {};

private:
	Ogre::Vector3 forward_;
	Ogre::Vector3 up_;
	Ogre::Vector3 pos_;
	Ogre::Vector3 vel_;

	int listenerNumber_;
};

#endif _AudioListenerComponent_H