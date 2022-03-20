#include "PhysicsManager.h"
#include "HornoConversions.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "Transform.h"


PhysicsManager* PhysicsManager::getInstance()
{
	if (instance == 0)
		return nullptr;

	return instance;
}

bool PhysicsManager::setupInstance()
{
	if (instance == 0) {
		instance = new PhysicsManager();
		return true;
	}
	return false;
}

void PhysicsManager::erase()
{
	delete instance;
}

void PhysicsManager::start(const std::string& initialScene)
{

}

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

void PhysicsManager::addCollisionObject(btCollisionObject* col, const short& group, const short& layerMask)
{
	world->addCollisionObject(col, group, layerMask);
}

PhysicsManager::PhysicsManager()
{
	//dispatcher = new btDispatcher();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphaseInterface, constraintSolver, collisionConfiguration);
}

PhysicsManager::~PhysicsManager()
{
	delete world;
}

btCollisionShape* PhysicsManager::createShape(Transform* tr, ColliderShape sha = ColliderShape::Box)
{
	btCollisionShape* shape = nullptr;
	switch (sha) {
	case ColliderShape::Box: //HALF-EXTENTS = Transform.Escala
		shape = new btBoxShape(VectorToBullet(tr->getScale()));
		break;
	case ColliderShape::Sphere: //RADIO = Transform.Scale.Length
		shape = new btSphereShape(VectorToBullet(tr->getScale()).length());
		break;
	case ColliderShape::Cylinder: //HALF-EXTENTS = Transform.Escala
		shape = new btCylinderShape(VectorToBullet(tr->getScale()));
		break;
	case ColliderShape::Capsule: //RADIO = Transform.Scale.X --- ALTURA = Transform.Scale.Y
		shape = new btCapsuleShape(VectorToBullet(tr->getScale()).x(), VectorToBullet(tr->getScale()).y());
		break;
	}
	return shape;
}

btGhostObject* PhysicsManager::createTrigger(Transform* tr, ColliderShape sha = ColliderShape::Box)
{
	btGhostObject* gO = new btGhostObject();
	gO->setInterpolationWorldTransform(btTransform(QuaternionToBullet(tr->getRotation()),
		VectorToBullet(tr->getPosition())));

	btCollisionShape* shape = createShape(tr, sha);

	gO->setCollisionShape(shape);
	return gO;

}

btRigidBody* PhysicsManager::createRigidBody(Transform* tr, const float& mass = 0, ColliderShape sha = ColliderShape::Box)
{
	//MotionState generado a partir de un Transform de bullet, 
	//generado a partir de un componente Transform 
	//======
	//	-SI FALLA ES PORQUE NO GUARDAMOS EL TRANSFORM QUE SE CREA DIRECTAMENTE EN LA LLAMADA AL MÉTODO
	//	-PARA ARREGLAR ESO HABRÍA QUE ALMACENARLO EN ALGÚN LADO
	//======
	btDefaultMotionState* state = new btDefaultMotionState(btTransform(QuaternionToBullet(tr->getRotation()), 
																	   VectorToBullet(tr->getPosition())));

	btCollisionShape* shape = createShape(tr, sha);

	btRigidBody* body = new btRigidBody(mass, state, shape);
	return body;
}

//btRigidBody::setAngularFactor evita rotaciones 

//CollideMasks:
//world.setGroupCollisionFlag(0, 0, False)
//bodyNP.setCollideMask(BitMask32.bit(0))