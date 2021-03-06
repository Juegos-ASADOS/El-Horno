#include "ParticleSystem.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Scene.h"
#include "Timer.h"
#include "CheckML.h"

namespace El_Horno {

	// Nombre, template en .particle, tiempo de vida y si es destruido al acabar ese tiempo
	ParticleSystem::ParticleSystem(const std::string& name, const std::string& temp, float ttl, bool destroyTL)
	{
		particleSystemName_ = name;
		particleSystemTemplate_ = temp;
		timeToLive_ = ttl;
		destroyOnTimeLimit_ = destroyTL;
		particleSystemOrderedName_ = particleSystemName_;
		timer_ = new Timer();
	}

	ParticleSystem::ParticleSystem()
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		particleSystem_->clear();
		particleSystem_->detachFromParent();
		ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->destroyParticleSystem(particleSystemOrderedName_);
		particleSystem_ = nullptr;
		delete timer_; timer_ = nullptr;
	}

	void ParticleSystem::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "name") {
				particleSystemName_ = parameters[i].second;
				particleSystemOrderedName_ = particleSystemName_;
			}
			else if (parameters[i].first == "template") {
				particleSystemTemplate_ = parameters[i].second;
			}
			else if (parameters[i].first == "ttl") {
				timeToLive_ = stof(parameters[i].second);
			}
			else if (parameters[i].first == "destroyTL") {
				destroyOnTimeLimit_ = stoi(parameters[i].second);
			}
		}
		timer_ = new Timer();
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

		particleSystem_->setEmitting(true);
		//Esto deber?a ser asi pero empieza a true para hacer pruebas
		//particleSystem_->setEmitting(false);
		particleSystem_->setKeepParticlesInLocalSpace(true);

		entity_->getComponent<Transform>("transform")->getNode()->attachObject(particleSystem_);
	}

	void ParticleSystem::onEnable()
	{
		particleSystem_->setEmitting(true);
		timer_->resetTimer();
	}

	void ParticleSystem::onDisable()
	{
		particleSystem_->setEmitting(false);
		// ttl ahora es el tiempo que queda cuando se desactiva el componente
		timeToLive_ -= timer_->getTime();
	}

	// Si el timer acaba, deja de emitir o destruye la entidad
	void ParticleSystem::update()
	{
		if (timeToLive_ <= 0)
			return;

		if (timer_->getTime() >= timeToLive_) {
			if (destroyOnTimeLimit_)
				entity_->getScene()->deleteEntity(entity_->getName());
			else
				setActive(false);
		}
	}

	// Activa el componente
	void ParticleSystem::emit()
	{
		setActive(true);
	}
}