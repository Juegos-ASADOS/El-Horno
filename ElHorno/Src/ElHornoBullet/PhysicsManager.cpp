#include "PhysicsManager.h"
#include "btBulletDynamicsCommon.h"
//#include "../ElHornoBase/Transform.h"


/*
* Se tiene que llamar varias veces por frame
* Hacer timers en bucle principal 
* Se llama 0.02 
* Frame rate 60
* Dibuja los objetos para debuguearlos
*/
void PhysicsManager::update(const float& dt)
{
	world->stepSimulation(dt);
	//if(DEBUG)
	world->debugDrawWorld();
}

void PhysicsManager::addBody(btRigidBody* body)
{	
	world->addRigidBody(body);
}

/*
* Con bits, desde el componente rigidBody se implementa como en este ejemplo:
* 
* #define BASE_GROUP    1<<0
* #define WHEEL_GROUP   1<<1
* #define BALL_GROUP    1<<2
*
* const short ball_group = BALL_GROUP ///< la pelota pertenece a este grupo
* const short ball_mask  = BASE_GROUP | WHEEL_GROUP | BALL_GROUP  ///< la pelota choca con estos grupos
*
* const short wheel_group = WHEEL_GROUP
* const short wheel_mask =  BALL_GROUP   ///< la rueda solo choca con la pelota
* 
* ---------------------
* 
* Máximo de 15 capas de colisión : (usa un short por eso)
* 
*/
void PhysicsManager::addBody(btRigidBody* body, const short& group, const short& layerMask)
{
	world->addRigidBody(body, group, layerMask);
}

btRigidBody* PhysicsManager::createRigidBody(Transform* tr, const float& mass = 0, ColliderShape sha = ColliderShape::Box)
{
	/*float mass;
	btDefaultMotionState* state = new btDefaultMotionState({ tr->getRotation(), tr->getPosition()});

	btCollisionShape* shape;
	switch (sha) {
		case ColliderShape::Box :
			shape = new btBoxShape(tr->getScale());
			break;
		case ColliderShape::Sphere :
			shape = new btSphereShape(tr->getScale());
			break;
		case ColliderShape::Cylinder:
			shape = new btCylinderShape(tr->getScale());
			break;
		case ColliderShape::Capsule:
			shape = new btCapsuleShape(tr->getScale());
			break;
	}

	btRigidBody* body = new btRigidBody(mass, state, shape);
	return body;*/
	return nullptr;
}

//btRigidBody::setAngularFactor evita rotaciones 

//CollideMasks:
//world.setGroupCollisionFlag(0, 0, False)
//bodyNP.setCollideMask(BitMask32.bit(0))