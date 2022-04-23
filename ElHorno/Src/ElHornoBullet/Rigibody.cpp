#include "PhysicsManager.h"
#include "Rigibody.h"
#include "Entity.h"
#include "HornoConversions.h"
#include "Transform.h"
#include "Mesh.h"
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

	RigidBody::RigidBody(float mass, int group, int mask, bool isTrigger, bool isKinematic, int colShape)
	{
		this->mass_ = mass;
		this->group_ = group;
		this->mask_ = mask;
		this->isKinematic_ = isKinematic;
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

		btVector3 size(1,1,1);
		//Si tiene mesh, la utilizamos para tomar el tamaño por defecto
		if (entity_->getComponent<Mesh>("mesh")) {
			Ogre::Entity* obj = entity_->getComponent<Mesh>("mesh")->getOgreEntity();
			//Usamos la BoundingBox de la malla
			size += OgreVectorToBullet(obj->getBoundingBox().getHalfSize());
			
			//Ajuste de tamaño
			size *= 0.975;
		}//De lo contrario tomamos el tamaño del transform (no debería entrar aquí de normal)
		else{
			size += OgreVectorToBullet(transform_->getScale());
		}

		shape_ = phManager_->createShape(transform_, &size, (ColliderShape)colShape_);

		//Transform de bullet
		bttrasform_ = new btTransform(QuaternionToBullet(transform_->getRotation()), OgreVectorToBullet(transform_->getPosition()));

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

		//Necesario indicarle al manager que lo agregue al mundo de Bullet (y añada sus flags)
		if(group_ != -1 && mask_ != -1)
			phManager_->addBody(rigid_, group_, mask_);
		else
			phManager_->addBody(rigid_);
		
		if(isKinematic_)
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() + btCollisionObject::CF_KINEMATIC_OBJECT);

		//En función de si es trigger o no, se activan las flags
		if (isTrigger_) 
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() + btCollisionObject::CF_NO_CONTACT_RESPONSE);

	}

	//Cogemos el valor del Transform y se lo damos a Bullet en preupdate (permite movimiento kinemático)
	void RigidBody::preUpdate()
	{
		if (mass_ > 0) {
			Ogre::Vector3 pos = transform_->getPosition();
			Ogre::Quaternion rot = transform_->getRotation();

			rigid_->getWorldTransform().setOrigin(OgreVectorToBullet(pos));
			rigid_->getWorldTransform().setRotation(QuaternionToBullet(rot));
		}
	}

	//Tras los cálculos, Bullet devuelve la nueva posición y rotación del body
	void RigidBody::update()
	{
		btVector3 pos;
		btQuaternion rot;

		pos = rigid_->getWorldTransform().getOrigin();
		rot = rigid_->getWorldTransform().getRotation();

		transform_->setPosition(BulletVectorToOgre(pos));
		transform_->setRotation(QuaternionToOgre(rot));
	}

	void RigidBody::applyForce(const btVector3& force)
	{
		rigid_->applyCentralForce(force);
	}

	void RigidBody::applyImpulse(const btVector3& force)
	{
		rigid_->applyCentralImpulse(force);
	}

	void RigidBody::applyPush(const btVector3& force)
	{
		rigid_->applyCentralPushImpulse(force);
	}

	void RigidBody::applyTorque(const btVector3& torque)
	{
		rigid_->applyTorque(torque);
	}

	void RigidBody::applyTorqueImpulse(const btVector3& torque)
	{
		rigid_->applyTorqueImpulse(torque);
	}

	void RigidBody::applyTorqueTurn(const btVector3& torque)
	{
		rigid_->applyTorqueTurnImpulse(torque);
	}

	void RigidBody::setTrigger(bool isTrigger)
	{
		if (isTrigger_ != isTrigger) {
			if(isTrigger)
				rigid_->setCollisionFlags(rigid_->getCollisionFlags() + btCollisionObject::CF_NO_CONTACT_RESPONSE);
			else
				rigid_->setCollisionFlags(rigid_->getCollisionFlags() ^ btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		isTrigger_ = isTrigger;
	}

	void RigidBody::setGravity(const btVector3& g)
	{
		rigid_->setGravity(g);
	}

	btVector3 RigidBody::getGravity() const
	{
		return rigid_->getGravity();
	}

	btQuaternion RigidBody::getOrientation()
	{
		return rigid_->getOrientation();
	}

	void RigidBody::setDamping(const float& linear, const float& angular)
	{
		rigid_->setDamping(linear, angular);
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

	void RigidBody::setSleepingThresholds(const float& linear, const float& angular)
	{
		rigid_->setSleepingThresholds(linear, angular);
	}

	void RigidBody::setLinearVelocity(const btVector3& l)
	{
		rigid_->setLinearVelocity(l);
	}

	void RigidBody::setAngularVelocity(const btVector3& a)
	{
		rigid_->setAngularVelocity(a);
	}

	btVector3 RigidBody::getLinearVelocity() const
	{
		return rigid_->getLinearVelocity();
	}

	btVector3 RigidBody::getAngularVelocity() const
	{
		return rigid_->getAngularVelocity();
	}

	btVector3 RigidBody::getScale() const
	{
		return rigid_->getCollisionShape()->getLocalScaling();
	}

	void RigidBody::setScale(const btVector3& s)
	{
		phManager_->removeBody(rigid_);
		rigid_->getCollisionShape()->setLocalScaling(s);
		phManager_->addBody(rigid_);
	}

	//Sincroniza el tamaño del collider con el de la malla (poco preciso)
	void RigidBody::syncScale()
	{
		Ogre::Entity* obj = entity_->getComponent<Mesh>("mesh")->getOgreEntity();
		Ogre::Vector3 scale = transform_->getScale();
		btVector3 size(1, 1, 1);
		//Usamos la BoundingBox de la malla
		size += OgreVectorToBullet(obj->getBoundingBox().getHalfSize());
		rigid_->getCollisionShape()->setLocalScaling(size * OgreVectorToBullet(scale));
	}
}