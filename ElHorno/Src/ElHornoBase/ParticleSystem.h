#pragma once
#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include "Component.h"
#include <string>

namespace El_Horno {
	class Timer;
}

namespace Ogre {
	class ParticleSystem;
}

namespace El_Horno {
	class _declspec(dllexport) ParticleSystem : public Component
	{
	public:

		ParticleSystem(const std::string& name, const std::string& temp, float ttl, bool destroyTL);
		~ParticleSystem();

		void start() override;
		void onEnable() override;
		void onDisable() override;
		void update() override;

		void emit();
	private:
		Ogre::ParticleSystem* particleSystem_ = nullptr;
		std::string particleSystemName_, 
					particleSystemOrderedName_, 
					particleSystemTemplate_;

		bool destroyOnTimeLimit_ = false;
		float timeToLive_;
		Timer* timer_;
	};
}
#endif _PARTICLE_SYSTEM_H