#include "ParticleSystem.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Scene.h"

ParticleSystem::ParticleSystem(std::string& name, std::string& temp, float timelim, bool destroyTL)
{
	particleSystemName_ = name;
	particleSystemTemplate_ = temp;
	timeLimit_ = timelim;
	destroyOnTimeLimit_ = destroyTL;
	particleSystemOrderedName_ = particleSystemName_;
}

ParticleSystem::~ParticleSystem()
{
	particleSystem_->clear();
	particleSystem_->detachFromParent();
	ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->destroyParticleSystem(particleSystemOrderedName_);
	particleSystem_ = nullptr;
}

void ParticleSystem::start()
{
	// Crea el siguiente nombre del particleSystem
	int i = 1;
	while (ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->hasParticleSystem(particleSystemOrderedName_)) {
		particleSystemOrderedName_ = particleSystemName_ + std::to_string(i);
		i++;
	}

	// Inicializa en el SceneManager de Ogre
	particleSystem_ = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->createParticleSystem(particleSystemOrderedName_, particleSystemTemplate_);
	particleSystem_->setEmitting(false);
	particleSystem_->setKeepParticlesInLocalSpace(true);

	entity_->getComponent<Transform>("transform")->getNode()->attachObject(particleSystem_);
}

void ParticleSystem::onEnable()
{
	particleSystem_->setEmitting(true);
}

void ParticleSystem::onDisable()
{
	particleSystem_->setEmitting(false);
}

void ParticleSystem::update()
{
	//if (timeLimit_ <= 0)
	//	return;

	//if (timer_ < timeLimit_) 
	//	timer_ += ElHornoBase::getInstance()->DeltaTime();
	//else {
	//	if (destroyOnTimeLimit_) 
	//		entity_->getMngr()->deleteEntity(entity_->getName());
	//	else 
	//		particleSystem_->setEmitting(false);
	//}
}

void ParticleSystem::emit()
{
	timer_ = 0;
	//setEnabled(true);
}