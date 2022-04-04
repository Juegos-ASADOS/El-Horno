#pragma once
#ifndef _AudioListenerComponent_H
#define _AudioListenerComponent_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>

namespace Ogre {
}

namespace El_Horno {
	class _declspec(dllexport) AudioListenerComponent : public Component
	{
	public:

		AudioListenerComponent();
		~AudioListenerComponent();

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
}
#endif _AudioListenerComponent_H