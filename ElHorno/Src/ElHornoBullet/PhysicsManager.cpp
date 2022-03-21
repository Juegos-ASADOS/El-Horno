#include "PhysicsManager.h"
#include "HornoConversions.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "Transform.h"

PhysicsManager* PhysicsManager::instance;

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
	if (world) {
		world->stepSimulation(dt);
	}
}

void PhysicsManager::updateDebug(const int& debugFlags)
{
	if (world && world->getDebugDrawer()) {
		world->getDebugDrawer()->setDebugMode(debugFlags);
		world->debugDrawWorld();
	}
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

void PhysicsManager::deleteBody(btRigidBody* body)
{
	world->removeRigidBody(body);
	btMotionState* ms = body->getMotionState();
	delete body;
	delete ms;
}

PhysicsManager::PhysicsManager()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	broadphaseInterface = new btDbvtBroadphase();

	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	constraintSolver = sol;

	world = new btDiscreteDynamicsWorld(dispatcher, broadphaseInterface, constraintSolver, collisionConfiguration);

	//world->setGravity(gravity);
}

PhysicsManager::~PhysicsManager()
{
	//Borrado en reverso, de último creado a primero
	
	//No tenemos constraints, así que no se borran de momento 
	
	//int i;
	//for (i = world->getNumConstraints() - 1; i >= 0; i--){
	//	world->removeConstraint(m_dynamicsWorld->getConstraint(i));
	//}

	//Borrado de los rigidbodies

	for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
			delete body->getMotionState();
		world->removeCollisionObject(obj);
		delete obj;
	}

	//Borrado de las Collision Shape

	for (int j = 0; j < collisionShapes->size(); j++) {
		btCollisionShape* shape = (*collisionShapes)[j];
		(*collisionShapes)[j] = 0;
		delete shape;
	}
	collisionShapes->clear();

	delete world; world = nullptr;

	delete constraintSolver; constraintSolver = nullptr;

	delete broadphaseInterface; broadphaseInterface = nullptr;

	delete dispatcher; dispatcher = nullptr;

	delete collisionConfiguration; collisionConfiguration = nullptr;
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

btGhostObject* PhysicsManager::createTrigger(btTransform* tr, btCollisionShape* shape, int& userIdx)
{
	//Si la forma es inv�lida, tira la ejecuci�n
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	collisionShapes->push_back(shape);

	btGhostObject* body = new btGhostObject();
	
	body->setInterpolationWorldTransform(*tr);

	body->setCollisionShape(shape);

	return body;

}

btRigidBody* PhysicsManager::createRigidBody(btTransform* tr, btCollisionShape* shape, int& userIdx, const float& mass)
{
	//Si la forma es inv�lida, tira la ejecuci�n
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//Rigidbody es din�mico si la masa es distinta de cero, si no, est�tico
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);

	collisionShapes->push_back(shape);

	//Solo si es din�mico se calcula la inercia
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);
	
	//Crea el Rigidbody a partir de: 
	//- Un MotionState (interno de Bullet)
	//- Un ConstructionInfo (interno de Bullet)

	btDefaultMotionState* state = new btDefaultMotionState(*tr);

	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, state, shape, localInertia);

	btRigidBody* body = new btRigidBody(cInfo);

	//Guardamos y sumamos para el siguiente
	userIdx = userIdxCount;

	body->setUserIndex(userIdxCount++);

	return body;
}

//btRigidBody::setAngularFactor evita rotaciones 

//CollideMasks:
//world.setGroupCollisionFlag(0, 0, False)
//bodyNP.setCollideMask(BitMask32.bit(0))