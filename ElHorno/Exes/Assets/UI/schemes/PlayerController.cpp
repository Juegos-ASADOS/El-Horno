#include "GameFactories.h"
#include "PlayerController.h"
#include "Rigibody.h"
#include "Entity.h"
#include "InputManager.h"
#include "ElHornoBase.h"
#include "btBulletCollisionCommon.h"

void El_Horno::PlayerController::start()
{
	rb = entity_->getComponent<RigidBody>("rigidbody");
	rb->setAngularFactor(0.0f);
	rb->setSleepingThresholds(0, 0);
	rb->setFriction(0.7);
	input = ElHornoBase::getInstance()->getInputManager();
}

void El_Horno::PlayerController::update()
{
	float x = -speed * input->isKeyDown(SDL_SCANCODE_A) + speed * input->isKeyDown(SDL_SCANCODE_D);
	float z = -speed * input->isKeyDown(SDL_SCANCODE_S) + speed * input->isKeyDown(SDL_SCANCODE_W);
	rb->applyForce(btVector3(x, 0, -z));
}
