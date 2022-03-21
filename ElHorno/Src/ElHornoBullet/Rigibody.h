#pragma once
#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include "Component.h"

class btRigidBody;
class btTransform;
class btCollisionShape;
class btCollisionObject;
class PhysicsManager;

class Transform;

union rb_union
{
	btRigidBody* rigid;
	btGhostObject* ghost;
};

class RigidBody : public Component
{
public:
	RigidBody(float mass, bool isTrigger, int colShape);
	~RigidBody();

	virtual void start() override;
	virtual void update() override;


private:
	//Masa por defecto 
	//[DINÁMICO > 0 | ESTÁTICO == 0]
	float mass = 1.0f;

	bool isTrigger = false;
	
	//Union de Rigidbody de bullet : Solo puede ser ghost (trigger) o rigid (normal)
	rb_union rb;

	//Forma básica del collider + Enum del PhysicsManager
	btCollisionShape* shape = nullptr;
	int colShape;

	//Transform de bullet para generar el rigidbody de bullet
	btTransform* bttrasform = nullptr;

	//Transform de la entidad 
	Transform* transform = nullptr;

	PhysicsManager* phManager = nullptr;
};



#endif _RIGIDBODY_H