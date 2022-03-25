#include "ElHornoBase.h"; 
#include "AudioComponent.h"

//#include "OgreEntity.h"
#include "CameraComponent.h"
#include <OgreCamera.h>
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"
#include "HornoConversions.h"
#include "fmod.h"
#include "CheckMl.h"

AudioComponent::AudioComponent() {}

AudioComponent::~AudioComponent() {}

void AudioComponent::update()
{
	pos_.x = entity_->getComponent<Transform>("Transform")->getPosition().x;
	pos_.y = entity_->getComponent<Transform>("Transform")->getPosition().y;
	pos_.z = entity_->getComponent<Transform>("Transform")->getPosition().z;

	vel_.x = 0;
	vel_.y = 0;
	vel_.z = 0;
	ElHornoBase::getInstance()->getAudioManager()->updateSound(VectorToFmod(pos_), VectorToFmod(vel_), nChannel);
}

void AudioComponent::playSound(std::string path)
{
	nChannel = ElHornoBase::getInstance()->getAudioManager()->PlaySound(audioRoute, VectorToFmod(pos_), 5);
}


