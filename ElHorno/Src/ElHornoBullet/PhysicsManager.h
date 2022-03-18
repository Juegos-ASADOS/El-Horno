#pragma once
#ifndef _PHYSHICS_MANAGER_H
#define _PHYSHICS_MANAGER_H

#include <string>

class btDiscreteDynamicsWorld;
class btDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;
class btCollisionConfiguration;
class btRigidBody;
class btCollisionShape;
class btCollisionObject;
class btGhostObject;
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
	btGhostObject* createTrigger(Transform* tr_, ColliderShape sha);
	void addBody(btRigidBody* body);
	void addBody(btRigidBody* body, const short& group, const short& layerMask);
	void addCollisionObject(btCollisionObject* col, const short& group, const short& layerMask);
private:
	static PhysicsManager* instance;

	PhysicsManager();
	~PhysicsManager();

	btCollisionShape* createShape(Transform* tra, ColliderShape sha);

	float fixedTimeStep = 0.0f;

	btDiscreteDynamicsWorld* world;
	btDispatcher* dispatcher;
	btBroadphaseInterface* broadphaseInterface;
	btConstraintSolver* constraintSolver;
	btCollisionConfiguration* collisionConfiguration;
};

#endif _PHYSHICS_MANAGER_H