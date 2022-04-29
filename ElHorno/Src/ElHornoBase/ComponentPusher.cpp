#include "ComponentPusher.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "AnimatorController.h"
#include "AudioComponent.h"
#include "AudioListenerComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "ParticleSystem.h"
#include "Rigibody.h"
#include "UIPushButton.h"

void El_Horno::ComponentPusher::pushComponents()
{
	SceneManager::getInstance()->possibleComponents.emplace("transform", &SceneManager::getInstance()->createComponent<Transform>);
	SceneManager::getInstance()->possibleComponents.emplace("mesh", &SceneManager::getInstance()->createComponent<Mesh>);
	SceneManager::getInstance()->possibleComponents.emplace("animatorcontroller", &SceneManager::getInstance()->createComponent<AnimatorController>);
	SceneManager::getInstance()->possibleComponents.emplace("audiocomponent", &SceneManager::getInstance()->createComponent<AudioComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("audiolistener", &SceneManager::getInstance()->createComponent<AudioListenerComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("camera", &SceneManager::getInstance()->createComponent<CameraComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("light", &SceneManager::getInstance()->createComponent<LightComponent>);
	SceneManager::getInstance()->possibleComponents.emplace("particlesystem", &SceneManager::getInstance()->createComponent<ParticleSystem>);
	SceneManager::getInstance()->possibleComponents.emplace("rigidbody", &SceneManager::getInstance()->createComponent<RigidBody>);
	SceneManager::getInstance()->possibleComponents.emplace("uipushbutton", &SceneManager::getInstance()->createComponent<UIPushButton>);
}
