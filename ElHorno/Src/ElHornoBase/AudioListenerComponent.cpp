#include "ElHornoBase.h"; 
#include "AudioListenerComponent.h"

//#include "OgreEntity.h"
#include "CameraComponent.h"
#include <OgreCamera.h>
#include "Transform.h"
#include "Entity.h"
#include "AudioManager.h"
#include "HornoConversions.h"
#include "fmod.h"
#include "CheckML.h"

namespace El_Horno {
	AudioListenerComponent::AudioListenerComponent() {}

	AudioListenerComponent::~AudioListenerComponent() {}

	void AudioListenerComponent::update()
	{
		pos_.x = entity_->getComponent<Transform>("transform")->getPosition().x;
		pos_.y = entity_->getComponent<Transform>("transform")->getPosition().y;
		pos_.z = entity_->getComponent<Transform>("transform")->getPosition().z;

		forward_ = -1 * entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealDirection();

		up_.x = entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealUp().x;
		up_.y = entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealUp().y;
		up_.z = entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealUp().z;

		vel_.x = 0;
		vel_.y = 0;
		vel_.z = 0;

		ElHornoBase::getInstance()->getAudioManager()->updateListener(listenerNumber_, VectorToFmod(pos_), VectorToFmod(vel_), VectorToFmod(forward_), VectorToFmod(up_));

	}
}