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

	RigidBody::RigidBody()
	{
	}

	RigidBody::~RigidBody()
	{
		delete rigid_->getMotionState();
		//delete rigid_->getCollisionShape();
		rigid_->setUserPointer(nullptr);
		phManager_->removeBody(rigid_);
		delete rigid_; rigid_ = nullptr;
		delete bttrasform_; bttrasform_ = nullptr;
	}

	//Crea el rigidbody de Bullet y guarda los valores importantes como:
	//- Manager, transform, forma de collider, transform (bullet), friccion y restitucion, si es trigger, ID 

	void RigidBody::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "mass") {
				mass_ = stof(parameters[i].second);
			}
			else if (parameters[i].first == "group") {
				group_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "mask") {
				mask_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "isTrigger") {
				isKinematic_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "isKinematic") {
				isTrigger_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "colShape") {
				colShape_ = stoi(parameters[i].second);
			}
		}
	}

	void RigidBody::start()
	{
		phManager_ = PhysicsManager::getInstance();

		transform_ = entity_->getComponent<Transform>("transform");

		btVector3 size(1, 1, 1);
		//Si tiene mesh, la utilizamos para tomar el tama�o por defecto
		if (entity_->getComponent<Mesh>("mesh")) {
			Ogre::Entity* obj = entity_->getComponent<Mesh>("mesh")->getOgreEntity();
			//Usamos la BoundingBox de la malla
			size += OgreVectorToBullet(obj->getBoundingBox().getHalfSize());

			//Ajuste de tama�o
			size *= 0.975;
		}//De lo contrario tomamos el tama�o del transform (no deber�a entrar aqu� de normal)
		else {
			size += OgreVectorToBullet(transform_->getScale());
		}

		shape_ = phManager_->createShape(transform_, &size, (ColliderShape)colShape_);

		//Transform de bullet
		bttrasform_ = new btTransform(QuaternionToBullet(transform_->getRotation()), OgreVectorToBullet(transform_->getGlobalPosition()));

		//Por defecto
		friction_ = 0.3f;

		restitution_ = 0.1f;

		//Creaci�n del objeto en Bullet
		rigid_ = phManager_->createRigidBody(bttrasform_, shape_, userIdx_, mass_);

		//Guardamos referencia en el rb a nuestro rigidbody
		//para usarlo en el callback de colisiones
		rigid_->setUserPointer(this);

		//Valores varios del rb
		rigid_->setRestitution(restitution_);
		rigid_->setFriction(friction_);

		//Necesario indicarle al manager que lo agregue al mundo de Bullet (y a�ada sus flags)
		/*if (group_ != -1 && mask_ != -1)
			phManager_->addBody(rigid_, group_, mask_);
		else
			phManager_->addBody(rigid_);*/

		if (isKinematic_)
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);

		//En funci�n de si es trigger o no, se activan las flags
		if (isTrigger_)
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	//Cogemos el valor del Transform y se lo damos a Bullet en preupdate (permite movimiento kinem�tico)
	void RigidBody::preUpdate()
	{
		if (mass_ > 0) {
			//phManager_->removeBody(rigid_);
			Ogre::Vector3 pos = transform_->getGlobalPosition();
			Ogre::Quaternion rot = transform_->getRotation();

			rigid_->getWorldTransform().setOrigin(OgreVectorToBullet(pos));
			rigid_->getWorldTransform().setRotation(QuaternionToBullet(rot));
			//phManager_->addBody(rigid_);
		}
	}

	//Tras los c�lculos, Bullet devuelve la nueva posici�n y rotaci�n del body
	void RigidBody::update()
	{
		if (!isKinematic_) {
			btVector3 pos;
			//btQuaternion rot;

			pos = rigid_->getWorldTransform().getOrigin();
			//rot = rigid_->getWorldTransform().getRotation();
			transform_->setGlobalPosition(BulletVectorToOgre(pos));
			//transform_->setRotation(QuaternionToOgre(rot));
		}
	}

	void RigidBody::applyForce(const btVector3& force)
	{
		rigid_->applyCentralForce(force);
	}

	void RigidBody::applyForce(const HornoVector3& force)
	{
		applyForce(HornoVectorToBullet(force));
	}

	void RigidBody::applyImpulse(const btVector3& force)
	{
		rigid_->applyCentralImpulse(force);
	}

	void RigidBody::applyImpulse(const HornoVector3& force)
	{
		applyImpulse(HornoVectorToBullet(force));
	}

	void RigidBody::applyPush(const btVector3& force)
	{
		rigid_->applyCentralPushImpulse(force);
	}

	void RigidBody::applyPush(const HornoVector3& force)
	{
		applyPush(HornoVectorToBullet(force));
	}

	void RigidBody::applyTorque(const btVector3& torque)
	{
		rigid_->applyTorque(torque);
	}

	void RigidBody::applyTorque(const HornoVector3& torque)
	{
		applyTorque(HornoVectorToBullet(torque));
	}

	void RigidBody::applyTorqueImpulse(const btVector3& torque)
	{
		rigid_->applyTorqueImpulse(torque);
	}

	void RigidBody::applyTorqueImpulse(const HornoVector3& torque)
	{
		applyTorqueImpulse(HornoVectorToBullet(torque));
	}

	void RigidBody::applyTorqueTurn(const btVector3& torque)
	{
		rigid_->applyTorqueTurnImpulse(torque);
	}

	void RigidBody::applyTorqueTurn(const HornoVector3& torque)
	{
		applyTorqueTurn(HornoVectorToBullet(torque));
	}

	void RigidBody::setTrigger(bool isTrigger)
	{
		if (isTrigger_ != isTrigger) {
			if (isTrigger)
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

	void RigidBody::setGravity(const El_Horno::HornoVector3& g)
	{
		rigid_->setGravity(HornoVectorToBullet(g));
	}

	btVector3 RigidBody::getGravity() const
	{
		return rigid_->getGravity();
	}

	HornoVector3 RigidBody::getHornoGravity() const
	{
		return BulletVectorToHorno(rigid_->getGravity());
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

	void RigidBody::setLinearVelocity(const HornoVector3& l)
	{
		setLinearVelocity(HornoVectorToBullet(l));
	}

	void RigidBody::setAngularVelocity(const btVector3& a)
	{
		rigid_->setAngularVelocity(a);
	}

	void RigidBody::setAngularVelocity(const HornoVector3& a)
	{
		setAngularVelocity(HornoVectorToBullet(a));
	}

	void RigidBody::setKinematic(bool kin)
	{
		isKinematic_ = kin;
		if (isKinematic_)
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		else
			rigid_->setCollisionFlags(rigid_->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
	}

	float RigidBody::getDamping() const
	{
		return (float)rigid_->getLinearDamping();
	}

	btVector3 RigidBody::getLinearVelocity() const
	{
		return rigid_->getLinearVelocity();
	}

	HornoVector3 RigidBody::getHornoLinearVelocity() const
	{
		return BulletVectorToHorno(getLinearVelocity());
	}


	btVector3 RigidBody::getAngularVelocity() const
	{
		return rigid_->getAngularVelocity();
	}

	HornoVector3 RigidBody::getHornoAngularVelocity() const
	{
		return BulletVectorToHorno(getAngularVelocity());
	}

	btVector3 RigidBody::getScale() const
	{
		return rigid_->getCollisionShape()->getLocalScaling();
	}

	HornoVector3 RigidBody::getHornoScale() const
	{
		return BulletVectorToHorno(getScale());
	}

	void RigidBody::setGroup(int g)
	{
		btBroadphaseProxy* proxy = rigid_->getBroadphaseProxy();
		proxy->m_collisionFilterGroup = g;
	}

	void RigidBody::setMask(int m)
	{
		btBroadphaseProxy* proxy = rigid_->getBroadphaseProxy();
		proxy->m_collisionFilterMask = m;
	}

	int RigidBody::getGroup()
	{
		btBroadphaseProxy* proxy = rigid_->getBroadphaseProxy();
		return proxy->m_collisionFilterGroup;
	}

	int RigidBody::getMask()
	{
		btBroadphaseProxy* proxy = rigid_->getBroadphaseProxy();
		return proxy->m_collisionFilterMask;
	}

	void RigidBody::setScale(const btVector3& s)
	{
		phManager_->removeBody(rigid_);
		rigid_->getCollisionShape()->setLocalScaling(s);
		phManager_->addBody(rigid_);
	}

	void RigidBody::setScale(const HornoVector3& s)
	{
		setScale(HornoVectorToBullet(s));
	}

	//Sincroniza el tama�o del collider con el de la malla (poco preciso)
	void RigidBody::syncScale()
	{
		Ogre::Entity* obj = entity_->getComponent<Mesh>("mesh")->getOgreEntity();
		Ogre::Vector3 scale = transform_->getScale();
		btVector3 size(1, 1, 1);
		//Usamos la BoundingBox de la malla
		size += OgreVectorToBullet(obj->getBoundingBox().getHalfSize());
		rigid_->getCollisionShape()->setLocalScaling(size * OgreVectorToBullet(scale));
	}
	void RigidBody::onEnable()
	{
		if (group_ != -1 && mask_ != -1)
			phManager_->addBody(rigid_, group_, mask_);
		else
			phManager_->addBody(rigid_);
	}
	void RigidBody::onDisable()
	{
		if (rigid_ != nullptr)
			phManager_->removeBody(rigid_);
	}
}