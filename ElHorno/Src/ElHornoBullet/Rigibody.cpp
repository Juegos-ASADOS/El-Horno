#include "PhysicsManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "HornoConversions.h"
#include "Transform.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "CheckML.h"


namespace El_Horno {

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

		shape_ = phManager_->createShape(transform_, (ColliderShape)colShape_);

		bttrasform_ = new btTransform(QuaternionToBullet(transform_->getRotation()), VectorToBullet(transform_->getPosition()));

		//Por defecto
		friction_ = 0.3f;

		restitution_ = 0.1f;

		//Creación del objeto en Bullet
		rigid_ = phManager_->createRigidBody(bttrasform_, shape_, userIdx_, mass_);

		//Guardamos referencia en el rb a nuestro rigidbody, para usarlo en el callback
		//de colisiones
		rigid_->setUserPointer(this);

		//Valores varios del rb
		rigid_->setRestitution(restitution_);
		rigid_->setFriction(friction_);

		//Necesario indicarle al manager que lo agregue al mundo de Bullet
		phManager_->addBody(rigid_);

		//En función de si es trigger o no, se activan las flags
		if (isTrigger_) 
			rigid_->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	void RigidBody::update()
	{
		btVector3 pos;
		btQuaternion rot;

		pos = rigid_->getWorldTransform().getOrigin();
		rot = rigid_->getWorldTransform().getRotation();

		transform_->setPosition(VectorToOgre(pos));
		transform_->setRotation(QuaternionToOgre(rot));
	}

	void RigidBody::setFriction(const float& f)
	{
		friction_ = f;
		rigid_->setFriction(f);
	}

	void RigidBody::setRestitution(const float& r)
	{
		restitution_ = r;
		rigid_->setRestitution(r);
	}

	void RigidBody::setMass(const float& m)
	{
		mass_ = m;

		btVector3 inertia;
		
		phManager_->removeBody(rigid_);
		rigid_->getCollisionShape()->calculateLocalInertia(mass_, inertia);
		rigid_->setMassProps(mass_, inertia);
		phManager_->addBody(rigid_);
	}
}