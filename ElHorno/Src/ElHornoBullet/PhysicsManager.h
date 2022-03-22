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
class btTransform;
class btVector3;

template<typename T>
class btAlignedObjectArray;

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
	void updateDebug(const int& debugFlags);
	
	btRigidBody* createRigidBody(btTransform* tr, btCollisionShape* shape, int& userIdx, const float& mass = 1.0f);
	btGhostObject* createTrigger(btTransform* tr, btCollisionShape* shape, int& userIdx);
	btCollisionShape* createShape(Transform* tra, ColliderShape sha);
	
	//Para añadir al mundo de Bullet rigidbodies
	void addBody(btRigidBody* body);
	void addBody(btRigidBody* body, const short& group, const short& layerMask);
	
	//Para objetos que no son rigidbodies
	void addCollisionObject(btCollisionObject* col);
	void addCollisionObject(btCollisionObject* col, const short& group, const short& layerMask);

	void removeBody(btRigidBody* body);
	void deleteBody(btRigidBody* body);

	void removeCollisionObject(btCollisionObject* body);

	void deleteCollisionObject(btCollisionObject* body);

	void setGravity(const btVector3& g);
private:
	static PhysicsManager* instance;

	PhysicsManager();
	~PhysicsManager();

	float fixedTimeStep = 0.0f;

	int userIdxCount = 0;

	btVector3* gravity = nullptr;

	btDiscreteDynamicsWorld* world;
	btDispatcher* dispatcher;
	btBroadphaseInterface* broadphaseInterface;
	btConstraintSolver* constraintSolver;
	btCollisionConfiguration* collisionConfiguration;

	//Para borrarlas al terminar
	btAlignedObjectArray<btCollisionShape*>* collisionShapes;
};

#endif _PHYSHICS_MANAGER_H