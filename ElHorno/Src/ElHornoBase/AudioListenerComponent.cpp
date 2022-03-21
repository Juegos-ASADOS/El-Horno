//#include "ElHornoBase.h"; 
//#include "AudioListenerComponent.h"
//
////#include "OgreEntity.h"
//#include "CameraComponent.h"
//#include <OgreCamera.h>
//#include "Transform.h"
//#include "Entity.h"
//
//
//AudioListenerComponent::AudioListenerComponent() {}
//
//AudioListenerComponent::~AudioListenerComponent() {}
//
//void AudioListenerComponent::update()
//{
//	pos_.x = entity_->getComponent<Transform>("Transform")->getPosition().x;
//	pos_.y = entity_->getComponent<Transform>("Transform")->getPosition().y;
//	pos_.z = entity_->getComponent<Transform>("Transform")->getPosition().z;
//
//	forward_ = -1 * entity_->getComponent<CameraComponent>("CameraComponent")->getCamera()->getRealDirection();
//
//	up_.x = entity_->getComponent<CameraComponent>("CameraComponent")->getCamera()->getRealUp().x;
//	up_.y = entity_->getComponent<CameraComponent>("CameraComponent")->getCamera()->getRealUp().y;
//	up_.z = entity_->getComponent<CameraComponent>("CameraComponent")->getCamera()->getRealUp().z;
//
//	vel_.x = 0;
//	vel_.y = 0;
//	vel_.z = 0;
//	ElHornoBase::getInstance()->getAudioManager()->updateListener(listenerNumber_, pos_, vel_, forward_, up_);
//
//}
//
//
