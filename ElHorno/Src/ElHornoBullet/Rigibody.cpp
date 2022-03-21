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

	//Por defecto
	friction = 0.3f;

	restitution = 0.1f;

	if (!isTrigger) {
		rb.rigid = phManager->createRigidBody(bttrasform, shape, userIdx, mass);
		rb.rigid->setRestitution(restitution);
		rb.rigid->setFriction(friction);
		phManager->addBody(rb.rigid);
	}
	else {
		rb.ghost = phManager->createTrigger(bttrasform, shape, userIdx);
		rb.ghost->setRestitution(restitution);
		rb.ghost->setFriction(friction);
		phManager->addCollisionObject(rb.ghost);
	}
}

void RigidBody::update()
{
	btVector3 pos;
	btQuaternion rot;
	if (!isTrigger) {
		pos = rb.rigid->getWorldTransform().getOrigin();
		rot = rb.rigid->getWorldTransform().getRotation();
	}
	else {
		pos = rb.ghost->getWorldTransform().getOrigin();
		rot = rb.ghost->getWorldTransform().getRotation();
	}

	transform->setPosition(VectorToOgre(pos));
	transform->setRotation(QuaternionToOgre(rot));
}

void RigidBody::setFriction(const float& f)
{
	friction = f;

	!isTrigger ? rb.rigid->setFriction(f) : rb.ghost->setFriction(f);
}

void RigidBody::setRestitution(const float& r)
{
	restitution = r;

	!isTrigger ? rb.rigid->setRestitution(r) : rb.ghost->setRestitution(r);
}

void RigidBody::setMass(const float& m)
{
	mass = m;

	btVector3 inertia;
	if (!isTrigger) {
		phManager->removeBody(rb.rigid);
		rb.rigid->getCollisionShape()->calculateLocalInertia(mass, inertia);
		rb.rigid->setMassProps(mass, inertia);
		phManager->addBody(rb.rigid);
	}

	//GhostObject no permite cambio de masa <<<
	
	//else {
	//	phManager->removeCollisionObject(rb.ghost);
	//	rb.ghost->getCollisionShape()->calculateLocalInertia(mass, inertia);
	//	
	//	phManager->addCollisionObject(rb.ghost);
	//}

}
