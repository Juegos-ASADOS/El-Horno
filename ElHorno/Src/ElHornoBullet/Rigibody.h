#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Component.h"

class btRigidBody;
class btGhostObject;
class btTransform;
class btCollisionShape;
class btCollisionObject;
class btVector3;

class PhysicsManager;

class Transform;

namespace El_Horno {
	class RigidBody : public Component
	{
	public:
		RigidBody(float mass, bool isTrigger, bool isKinematic,int colShape);
		~RigidBody();

		virtual void start() override;
		virtual void update() override;
		//virtual void preUpdate() override;

		void applyForce(btVector3* force);
		void applyImpulse(btVector3* force);
		void applyPush(btVector3* force);

		inline float getFriction() const { return friction_; };
		inline float getRestitution() const { return restitution_; };
		inline float getMass() const { return mass_; };

		void setTrigger(bool isTrigger);
		inline bool isTrigger() const { return isTrigger_; };

		void setFriction(const float& f);
		void setRestitution(const float& r);
		void setMass(const float& m);
		void setAngularFactor(const float& f);
		void setSleepingThresholds(const float& linear, const float& scalar);

		void setRotConstraints(int i, bool value);
		void setPosConstraints(int i, bool value);

		void syncScale();

	private:
		//Masa por defecto 
		//[DIN�MICO > 0 | EST�TICO == 0]
		float mass_ = 1.0f;

		float friction_;

		float restitution_;

		bool isTrigger_ = false;

		bool isKinematic_ = false;

		//Rigidbody de bullet
		btRigidBody* rigid_;

		//Forma b�sica del collider + Enum del PhysicsManager
		btCollisionShape* shape_ = nullptr;
		btVector3* size_ = nullptr;
		int colShape_ = 0;

		//Array de constraints de rotacion en x y z
		bool rotationConstraints[3]{ false, false, false };

		//Array de constraints de traslacion en x y z
		bool positionConstraints[3]{ false, false, false };

		//Transform de bullet para generar el rigidbody de bullet
		btTransform* bttrasform_ = nullptr;

		//Transform de la entidad 
		Transform* transform_ = nullptr;

		//Referencia al manager de f�sica
		PhysicsManager* phManager_ = nullptr;

		//Indice en Bullet
		int userIdx_;
	};
}


#endif _RIGIDBODY_H