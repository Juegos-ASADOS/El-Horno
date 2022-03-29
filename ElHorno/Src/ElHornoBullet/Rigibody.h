#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Component.h"

class btRigidBody;
class btGhostObject;
class btTransform;
class btCollisionShape;
class btCollisionObject;

class PhysicsManager;
class Transform;

union rb_union
{
	btRigidBody* rigid_;
	btGhostObject* ghost_;
};

namespace El_Horno {
	class RigidBody : public Component
	{
	public:
		RigidBody(float mass, bool isTrigger, int colShape);
		~RigidBody();

		virtual void start() override;
		virtual void update() override;

		inline float getFriction() const { return friction_; };
		inline float getRestitution() const { return restitution_; };
		inline float getMass() const { return mass_; };


		void setFriction(const float& f);
		void setRestitution(const float& r);
		void setMass(const float& m);

	private:
		//Masa por defecto 
		//[DINÁMICO > 0 | ESTÁTICO == 0]
		float mass_ = 1.0f;

		float friction_;

		float restitution_;

		bool isTrigger_ = false;

		//Union de Rigidbody de bullet : Solo puede ser ghost (trigger) o rigid (normal)
		rb_union rb_;

		//Forma básica del collider + Enum del PhysicsManager
		btCollisionShape* shape_ = nullptr;
		int colShape_;

		//Transform de bullet para generar el rigidbody de bullet
		btTransform* bttrasform_ = nullptr;

		//Transform de la entidad 
		Transform* transform_ = nullptr;

		//Referencia al manager de física
		PhysicsManager* phManager_ = nullptr;

		//Indice en Bullet
		int userIdx_;
	};
}


#endif _RIGIDBODY_H