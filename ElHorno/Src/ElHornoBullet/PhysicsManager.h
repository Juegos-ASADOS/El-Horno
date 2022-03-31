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

namespace El_Horno {
class Transform;

enum ColliderShape {
	Box,
	Sphere,
	Cylinder,
	Capsule
};

	class OgreDebugDrawer;
	class PhysicsManager
	{
	public:
		static PhysicsManager* getInstance();
		static bool setupInstance();
		static void erase();

		void start(const std::string& initialScene);
		void debugStart();
		void update(const float& dt);
		void updateDebug(const int& debugFlags);
		void removeDebug();

		btRigidBody* createRigidBody(btTransform* tr, btCollisionShape* shape, int& userIdx_, const float& mass = 1.0f);
		btGhostObject* createTrigger(btTransform* tr, btCollisionShape* shape, int& userIdx_);
		btCollisionShape* createShape(Transform* tra, btVector3* size, ColliderShape sha);

		//Para añadir al mundo de Bullet rigidbodies
		void addBody(btRigidBody* body);
		void addBody(btRigidBody* body, const short& group, const short& layerMask);

		void preUpdateBody(btRigidBody* body);

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

		int userIdxCount_ = 0;

		btVector3* gravity_ = nullptr;

		//Mundo de las físicas de bullet
		btDiscreteDynamicsWorld* dynamicsWorld_;

		//Configuración necesaria del mundo
		btDispatcher* dispatcher_;
		btBroadphaseInterface* broadphaseInterface_;
		btConstraintSolver* constraintSolver_;
		btCollisionConfiguration* collisionConfiguration_;

		//Array de las formas de colisión (necesario para borrarlas)
		btAlignedObjectArray<btCollisionShape*>* collisionShapes_;

		//Necesaria para renderizar el debug
		OgreDebugDrawer* debugDrawer_ = nullptr;
	};
}

#endif _PHYSHICS_MANAGER_H