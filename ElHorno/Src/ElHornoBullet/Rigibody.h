#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Component.h"
#include "Bullet3Common/b3Vector3.h"
#include "HornoVector3.h"

class btRigidBody;
class btGhostObject;
class btTransform;
class btCollisionShape;
class btCollisionObject;
class btVector3;
class btQuaternion;
class PhysicsManager;
class Transform;

namespace El_Horno {

	class _declspec(dllexport) RigidBody : public Component
	{
	public:
		RigidBody(float mass, bool isTrigger, bool isKinematic, int colShape);
		RigidBody(float mass, int group, int mask, bool isTrigger, bool isKinematic,int colShape);
		RigidBody();
		~RigidBody();

		virtual void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		virtual void start() override;
		virtual void update() override;
		virtual void preUpdate() override;

		void applyForce(const btVector3& force);
		void applyForce(const HornoVector3& force);
		void applyImpulse(const btVector3& force);
		void applyImpulse(const HornoVector3& force);
		void applyPush(const btVector3& force);
		void applyPush(const HornoVector3& force);
		
		void applyTorque(const btVector3& torque);
		void applyTorque(const HornoVector3& torque);
		void applyTorqueImpulse(const btVector3& torque);
		void applyTorqueImpulse(const HornoVector3& torque);
		void applyTorqueTurn(const btVector3& torque);
		void applyTorqueTurn(const HornoVector3& torque);

		inline float getFriction() const { return friction_; };
		inline float getRestitution() const { return restitution_; };
		inline float getMass() const { return mass_; };

		void setTrigger(bool isTrigger);
		inline bool isTrigger() const { return isTrigger_; };

		void setGravity(const btVector3& g);
		void setGravity(const HornoVector3& g);
		btVector3 getGravity() const;
		HornoVector3 getHornoGravity() const;

		btQuaternion getOrientation();

		void setDamping(const float& linear, const float& angular);
		void setFriction(const float& f);
		void setRestitution(const float& r);
		void setMass(const float& m);
		void setAngularFactor(const float& f);
		void setSleepingThresholds(const float& linear, const float& angular);

		void setLinearVelocity(const btVector3& l);
		void setLinearVelocity(const HornoVector3& l);
		void setAngularVelocity(const btVector3& a);
		void setAngularVelocity(const HornoVector3& a);
		void setKinematic(bool kin);
		
		float getDamping() const;
		btVector3 getLinearVelocity() const;
		HornoVector3 getHornoLinearVelocity() const;
		btVector3 getAngularVelocity() const;
		HornoVector3 getHornoAngularVelocity() const;

		btVector3 getScale() const;
		HornoVector3 getHornoScale() const;

		void setGroup(int g);
		void setMask(int m);

		int getGroup();
		int getMask();

		/*void setRotConstraints(int i, bool value);
		void setPosConstraints(int i, bool value);*/

		void setScale(const btVector3& s);
		void setScale(const HornoVector3& s);
		void syncScale();

	private:
		//Masa por defecto 
		//[DINAMICO > 0 | ESTATICO == 0]
		float mass_ = 1.0f;

		float friction_;

		float restitution_;

		bool isTrigger_ = false;

		bool isKinematic_ = false;

		//Colision Masks
		int group_ = -1;

		int mask_ = -1;

		//Rigidbody de bullet
		btRigidBody* rigid_;

		//Forma b�sica del collider + Enum del PhysicsManager
		btCollisionShape* shape_ = nullptr;
		int colShape_ = 0;

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