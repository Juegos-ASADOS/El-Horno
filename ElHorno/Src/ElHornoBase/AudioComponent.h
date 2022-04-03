#pragma once
#ifndef _AudioComponent_H
#define _AudioComponent_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>

namespace Ogre {
}

namespace El_Horno {
	class AudioComponent : public Component
	{
	public:

		AudioComponent();
		~AudioComponent();

		//void start() override;
		void update()override;

		void onEnable() override {};
		void onDisable()override {};

		virtual void playSound(std::string path);

	private:
		Ogre::Vector3 pos_;
		Ogre::Vector3 vel_;

		int nChannel_;
		std::string audioRoute_;
	};
}
#endif _AudioComponent_H