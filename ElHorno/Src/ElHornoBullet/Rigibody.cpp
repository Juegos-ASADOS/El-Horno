#include "PhysicsManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "HornoConversions.h"
#include "Transform.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

RigidBody::RigidBody(float mass, bool isTrigger, int colShape) : Component()
{
	this->mass = mass;
	this->isTrigger = isTrigger;
	this->colShape = colShape;
}

RigidBody::~RigidBody()
{
}

void RigidBody::start()
{
	phManager = PhysicsManager::getInstance();
	
	transform = entity_->getComponent<Transform>("Transform");

	shape = phManager->createShape(transform, (ColliderShape) colShape);

	bttrasform = new btTransform(QuaternionToBullet(transform->getRotation()), VectorToBullet(transform->getPosition()));

	if (!isTrigger) {
		rb.rigid = phManager->createRigidBody(bttrasform, shape, mass);
	}
	else {
		rb.ghost = phManager->createTrigger(bttrasform, shape);
	}

}

void RigidBody::update()
{
	btVector3 pos;
	btQuaternion rot;
	if (!isTrigger) {
		pos = rb.rigid->getWorldTransform().getOrigin();
		rot = rb.ghost->getWorldTransform().getRotation();
	}
	else {
		pos = rb.ghost->getWorldTransform().getOrigin();
		rot = rb.ghost->getWorldTransform().getRotation();
	}

	transform->setPosition(VectorToOgre(pos));
	transform->setRotation(QuaternionToOgre(rot));
}
