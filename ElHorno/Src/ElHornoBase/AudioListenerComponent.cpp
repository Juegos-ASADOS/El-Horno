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
		pos_ = entity_->getComponent<Transform>("transform")->getPosition();

		forward_ = -1 * entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealDirection();

		up_ = entity_->getComponent<CameraComponent>("camera")->getCamera()->getRealUp();

		vel_.x = 0;
		vel_.y = 0;
		vel_.z = 0;

		ElHornoBase::getInstance()->getAudioManager()->updateListener(listenerNumber_, OgreVectorToFmod(pos_), OgreVectorToFmod(vel_), OgreVectorToFmod(forward_), OgreVectorToFmod(up_));
		ElHornoBase::getInstance()->getAudioManager()->moveChanelTo(OgreVectorToFmod(pos_), OgreVectorToFmod(vel_));
	}
}