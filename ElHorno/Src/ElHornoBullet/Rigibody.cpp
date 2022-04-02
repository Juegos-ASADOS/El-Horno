#include "PhysicsManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "HornoConversions.h"
#include "Transform.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include <iostream>
//#include "CheckML.h"


namespace El_Horno {

	//colShape: 
	//Box      == 0
	//Sphere   == 1
	//Cylinder == 2
	//Capsule  == 3
	RigidBody::RigidBody(float mass, bool isTrigger, bool isKinematic, int colShape) : Component()
	{
		this->mass_ = mass;
		this->isKinematic_ = isKinematic;
		this->isTrigger_ = isTrigger;
		this->colShape_ = colShape;
	}

	RigidBody::~RigidBody()
	{
		delete size_; size_ = nullptr;
		delete bttrasform_; bttrasform_ = nullptr;
	}

	//Crea el rigidbody de Bullet y guarda los valores importantes como:
	//- Manager, transform, forma de collider, transform (bullet), friccion y restitucion, si es trigger, ID 

	void RigidBody::start()
	{
		phManager_ = PhysicsManager::getInstance();
		
		transform_ = entity_->getComponent<Transform>("transform");

		size_ = new btVector3(0,0,0);
		//Si tiene mesh, la utilizamos para tomar el tamaño por defecto
		if (transform_->getNode()->getAttachedObjects().size() > 0) {
			Ogre::Entity* obj = static_cast<Ogre::Entity*>(transform_->getNode()->getAttachedObject(0));
			//Usamos la BoundingBox de la malla
			*size_ += VectorToBullet(obj->getBoundingBox().getSize());
			//Dividimos para hallar el tamaño real
			*size_ /= 2.0f;
		}//De lo contrario tomamos el tamaño del transform (no debería entrar aquí de normal)
		else{
			*size_ += VectorToBullet(transform_->getScale());
		}

		shape_ = phManager_->createShape(transform_, size_, (ColliderShape)colShape_);

		//Transform de bullet
		bttrasform_ = new btTransform(QuaternionToBullet(transform_->getRotation()), VectorToBullet(transform_->getPosition()));

		//Por defecto
		friction_ = 0.3f;

		restitution_ = 0.1f;

		//Creación del objeto en Bullet
		rigid_ = phManager_->createRigidBody(bttrasform_, shape_, userIdx_, mass_);

		//Guardamos referencia en el rb a nuestro rigidbody
		//para usarlo en el callback de colisiones
		rigid_->setUserPointer(this);

		//Valores varios del rb
		rigid_->setRestitution(restitution_);
		rigid_->setFriction(friction_);

		//Necesario indicarle al manager que lo agregue al mundo de Bullet
		phManager_->addBody(rigid_);

		if(isKinematic_)
			rigid_->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

		//En función de si es trigger o no, se activan las flags
		if (isTrigger_) 
			rigid_->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	////Cogemos el valor del Transform y se lo damos a Bullet en preupdate
	/*void RigidBody::preUpdate()
	{
		if (isKinematic_) {
			Ogre::Vector3 pos = transform_->getPosition();
			Ogre::Quaternion rot = transform_->getRotation();

			rigid_->getWorldTransform().setOrigin(VectorToBullet(pos));
			rigid_->getWorldTransform().setRotation(QuaternionToBullet(rot));
		}
	}*/

	//Tras los cálculos, Bullet devuelve la nueva posición y rotación del body
	void RigidBody::update()
	{
		btVector3 pos;
		btQuaternion rot;

		pos = rigid_->getWorldTransform().getOrigin();
		rot = rigid_->getWorldTransform().getRotation();

		transform_->setPosition(VectorToOgre(pos));
		transform_->setRotation(QuaternionToOgre(rot));
	}

	void RigidBody::applyForce(btVector3* force)
	{
		rigid_->applyCentralForce(*force);
	}

	void RigidBody::applyImpulse(btVector3* force)
	{
		rigid_->applyCentralImpulse(*force);
	}

	void RigidBody::applyPush(btVector3* force)
	{
		rigid_->applyCentralPushImpulse(*force);
	}

	void RigidBody::setTrigger(bool isTrigger)
	{
		if (isTrigger_ != isTrigger) {
			if(isTrigger)
				rigid_->setCollisionFlags(rigid_->getCollisionFlags() || btCollisionObject::CF_NO_CONTACT_RESPONSE);
			else
				rigid_->setCollisionFlags(rigid_->getCollisionFlags() - btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		isTrigger_ = isTrigger;
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

	void RigidBody::setAngularFactor(const float& f)
	{
		rigid_->setAngularFactor(f);
	}

	void RigidBody::setSleepingThresholds(const float& linear, const float& scalar)
	{
		rigid_->setSleepingThresholds(linear, scalar);
	}

	//x=0 y=1 z=2
	void RigidBody::setRotConstraints(int i, bool value) {
		if (i >= 0 && i <= 2) {
			rotationConstraints[i] = value;

		}
	}

	//x=0 y=1 z=2
	void RigidBody::setPosConstraints(int i, bool value) {
		if (i >= 0 && i <= 2) {
			positionConstraints[i] = value;
		}
	}

	void RigidBody::syncScale()
	{
		Ogre::Vector3 scale = transform_->getScale();
		rigid_->getCollisionShape()->setLocalScaling(*size_ * VectorToBullet(scale));
	}
}