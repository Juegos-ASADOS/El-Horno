#include "PhysicsManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "HornoConversions.h"
#include "Transform.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "CheckMl.h"

//colShape: 
//Box      == 0
//Sphere   == 1
//Cylinder == 2
//Capsule  == 3
RigidBody::RigidBody(float mass, bool isTrigger, int colShape) : Component()
{
	this->mass_ = mass;
	this->isTrigger_ = isTrigger;
	this->colShape_ = colShape;
}

RigidBody::~RigidBody()
{
	delete bttrasform_; bttrasform_ = nullptr;
}

//Crea el rigidbody de Bullet y guarda los valores importantes como:
//- Manager, transform, forma de collider, transform (bullet), friccion y restitucion, si es trigger, ID 

void RigidBody::start()
{
	phManager_ = PhysicsManager::getInstance();
	
	transform_ = entity_->getComponent<Transform>("transform");

	shape_ = phManager_->createShape(transform_, (ColliderShape) colShape_);

	bttrasform_ = new btTransform(QuaternionToBullet(transform_->getRotation()), VectorToBullet(transform_->getPosition()));

	//Por defecto
	friction_ = 0.3f;

	restitution_ = 0.1f;

	//En función de si es trigger o no, se crea un body normal o un ghost_
	if (!isTrigger_) {
		//Creación del objeto en Bullet
		rb_.rigid_ = phManager_->createRigidBody(bttrasform_, shape_, userIdx_, mass_);
		
		//Guardamos referencia en el rb a nuestro rigidbody, para usarlo en el callback
		//de colisiones
		rb_.rigid_->setUserPointer(this);
		
		//Valores varios del rb
		rb_.rigid_->setRestitution(restitution_);
		rb_.rigid_->setFriction(friction_);
		
		//Necesario indicarle al manager que lo agregue al mundo de Bullet
		phManager_->addBody(rb_.rigid_);
	}
	else {
		//^^^^Idéntico al rigid^^^^^^//
		rb_.ghost_ = phManager_->createTrigger(bttrasform_, shape_, userIdx_);
		
		rb_.ghost_->setUserPointer(this);
		
		rb_.ghost_->setRestitution(restitution_);
		rb_.ghost_->setFriction(friction_);
		
		phManager_->addCollisionObject(rb_.ghost_);
	}
}

void RigidBody::update()
{
	btVector3 pos;
	btQuaternion rot;
	if (!isTrigger_) {
		pos = rb_.rigid_->getWorldTransform().getOrigin();
		rot = rb_.rigid_->getWorldTransform().getRotation();
	}
	else {
		pos = rb_.ghost_->getWorldTransform().getOrigin();
		rot = rb_.ghost_->getWorldTransform().getRotation();
	}

	transform_->setPosition(VectorToOgre(pos));
	transform_->setRotation(QuaternionToOgre(rot));
}

void RigidBody::setFriction(const float& f)
{
	friction_ = f;

	!isTrigger_ ? rb_.rigid_->setFriction(f) : rb_.ghost_->setFriction(f);
}

void RigidBody::setRestitution(const float& r)
{
	restitution_ = r;

	!isTrigger_ ? rb_.rigid_->setRestitution(r) : rb_.ghost_->setRestitution(r);
}

void RigidBody::setMass(const float& m)
{
	mass_ = m;

	btVector3 inertia;
	if (!isTrigger_) {
		phManager_->removeBody(rb_.rigid_);
		rb_.rigid_->getCollisionShape()->calculateLocalInertia(mass_, inertia);
		rb_.rigid_->setMassProps(mass_, inertia);
		phManager_->addBody(rb_.rigid_);
	}

	//GhostObject no permite cambio de masa <<<
	
	//else {
	//	phManager->removeCollisionObject(rb.ghost_);
	//	rb.ghost_->getCollisionShape()->calculateLocalInertia(mass, inertia);
	//	
	//	phManager->addCollisionObject(rb.ghost_);
	//}

}
