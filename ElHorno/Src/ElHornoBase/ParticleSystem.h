#pragma once
#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include "Component.h"
#include <string>

namespace Ogre {
	class ParticleSystem;
}

class ParticleSystem : public Component
{
public:

	ParticleSystem(std::string& name, std::string& temp, float timelim, bool destroyTL);
	~ParticleSystem();

	void start() override;
	void onEnable() override;
	void onDisable() override;
	void update() override;

	void emit();
private:
	Ogre::ParticleSystem* particleSystem_ = nullptr;
	std::string particleSystemName_, particleSystemOrderedName_, particleSystemTemplate_;

	bool destroyOnTimeLimit_ = false;
	float timeLimit_ = 0, timer_ = 0;
};

#endif _PARTICLE_SYSTEM_H