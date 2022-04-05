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
#include "CheckML.h"

namespace El_Horno {

	AudioComponent::AudioComponent() {}

	AudioComponent::~AudioComponent() {}

	void AudioComponent::update()
	{
		pos_ = entity_->getComponent<Transform>("transform")->getPosition();

		vel_.x = 0;
		vel_.y = 0;
		vel_.z = 0;

		ElHornoBase::getInstance()->getAudioManager()->updateSound(OgreVectorToFmod(pos_), OgreVectorToFmod(vel_), nChannel_);
	}

	void AudioComponent::playSound(std::string path)
	{
		nChannel_ = ElHornoBase::getInstance()->getAudioManager()->playSound(path, OgreVectorToFmod(pos_), 25.0f);
	}
}