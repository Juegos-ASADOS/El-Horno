#pragma once
#ifndef _PHYSHICS_MANAGER_H
#define _PHYSHICS_MANAGER_H

#include <string>

class btDiscreteDynamicsWorld;
class btRigidBody;
class Transform;

enum ColliderShape {
	Box,
	Sphere,
	Cylinder,
	Capsule
};

class PhysicsManager
{
public:
	static PhysicsManager* getInstance();
	static bool setupInstance();
	static void erase();

	void start(const std::string& initialScene);
	void update(const float& dt);
	
	btRigidBody* createRigidBody(Transform* tr, const float& mass, ColliderShape shape);
	void addBody(btRigidBody* body);
	void addBody(btRigidBody* body, const short& group, const short& layerMask);
private:
	static PhysicsManager* instance;

	PhysicsManager();
	~PhysicsManager();


	float fixedTimeStep = 0.0f;

	btDiscreteDynamicsWorld* world;
};

#endif _PHYSHICS_MANAGER_H