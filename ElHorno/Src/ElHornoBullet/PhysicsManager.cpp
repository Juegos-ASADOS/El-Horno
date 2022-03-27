#include "PhysicsManager.h"
#include "HornoConversions.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "Transform.h"
#include "Rigibody.h"
//#include "EventManager.h"
//#include "Event.h"
//
////Funcion externa que analiza colisiones en Bullet
//bool collisionCallbackBullet(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0, int partId0, int index0, const btCollisionObjectWrapper* colObj1, int partId1, int index1) {
//	
//	//Aviso básico a sendos rigidbodies de que X entidad a colisionado con ellos
//	RigidBody* e1 = static_cast<RigidBody*>(colObj0->getCollisionObject()->getUserPointer());
//	RigidBody* e2 = static_cast<RigidBody*>(colObj1->getCollisionObject()->getUserPointer());
//	
//	RigidBodyCollision* evnt1 = new RigidBodyCollision(e1->getEntity());
//	RigidBodyCollision* evnt2 = new RigidBodyCollision(e2->getEntity());
//	
//	EventManager::getInstance()->sendTargetEvent(e2, evnt1);
//	EventManager::getInstance()->sendTargetEvent(e1, evnt2);
//}


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


PhysicsManager::PhysicsManager()
{
	//Funcion de callback en colision
	//gContactAddedCallback = collisionCallbackBullet;
	
	collisionShapes_ = new btAlignedObjectArray<btCollisionShape*>();

	collisionConfiguration_ = new btDefaultCollisionConfiguration();

	dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);

	broadphaseInterface_ = new btDbvtBroadphase();

	//Tipo por defecto de solver
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	constraintSolver_ = sol;

	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_, broadphaseInterface_, constraintSolver_, collisionConfiguration_);


	//Gravedad placeholder
	dynamicsWorld_->setGravity(btVector3(0, -9.8, 0));
}

PhysicsManager::~PhysicsManager()
{
	//Borrado en reverso, de último creado a primero
	//No tenemos constraints, pero las borramos de todos modos

	int i;
	for (i = dynamicsWorld_->getNumConstraints() - 1; i >= 0; i--) {
		dynamicsWorld_->removeConstraint(dynamicsWorld_->getConstraint(i));
	}

	//Borrado de los rigidbodies

	for (i = dynamicsWorld_->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = dynamicsWorld_->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
			delete body->getMotionState();
		dynamicsWorld_->removeCollisionObject(obj);
		delete obj;
	}

	//Borrado de las Collision Shape

	for (i = 0; i < collisionShapes_->size(); i++) {
		btCollisionShape* shape = (*collisionShapes_)[i];
		(*collisionShapes_)[i] = 0;
		delete shape;
	}
	collisionShapes_->clear();
	delete collisionShapes_; collisionShapes_ = nullptr;

	delete gravity_; gravity_ = nullptr;

	delete dynamicsWorld_; dynamicsWorld_ = nullptr;

	delete constraintSolver_; constraintSolver_ = nullptr;

	delete broadphaseInterface_; broadphaseInterface_ = nullptr;

	delete dispatcher_; dispatcher_ = nullptr;

	delete collisionConfiguration_; collisionConfiguration_ = nullptr;
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
	if (dynamicsWorld_) {
		dynamicsWorld_->stepSimulation(dt);
	}
}

void PhysicsManager::updateDebug(const int& debugFlags)
{
	if (dynamicsWorld_ && dynamicsWorld_->getDebugDrawer()) {
		dynamicsWorld_->getDebugDrawer()->setDebugMode(debugFlags);
		dynamicsWorld_->debugDrawWorld();
	}
}

void PhysicsManager::addBody(btRigidBody* body)
{	
	dynamicsWorld_->addRigidBody(body);
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
	dynamicsWorld_->addRigidBody(body, group, layerMask);
}

void PhysicsManager::addCollisionObject(btCollisionObject* col)
{
	dynamicsWorld_->addCollisionObject(col);
}

void PhysicsManager::addCollisionObject(btCollisionObject* col, const short& group, const short& layerMask)
{
	dynamicsWorld_->addCollisionObject(col, group, layerMask);
}

//Sólo elimina del mundo Bullet un rigidbody, pero no lo borra
void PhysicsManager::removeBody(btRigidBody* body) {
	dynamicsWorld_->removeRigidBody(body);
}

//Borra y elimina del mundo Bullet un rigidbody
void PhysicsManager::deleteBody(btRigidBody* body)
{
	dynamicsWorld_->removeRigidBody(body);
	btMotionState* ms = body->getMotionState();
	delete body;
	delete ms;
}

//Sólo elimina del mundo Bullet un collisionObject, pero no lo borra
void PhysicsManager::removeCollisionObject(btCollisionObject* body) {
	dynamicsWorld_->removeCollisionObject(body);
}

//Borra y elimina del mundo Bullet un collisionObject
void PhysicsManager::deleteCollisionObject(btCollisionObject* body)
{
	dynamicsWorld_->removeCollisionObject(body);
	delete body;
}


void PhysicsManager::setGravity(const btVector3& g)
{
	if (gravity_) delete gravity_;
	gravity_ = new btVector3(g);
	if(dynamicsWorld_) dynamicsWorld_->setGravity(*gravity_);
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

btGhostObject* PhysicsManager::createTrigger(btTransform* tr, btCollisionShape* shape, int& userIdx_)
{
	//Si la forma es inv�lida, tira la ejecuci�n
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	collisionShapes_->push_back(shape);

	btGhostObject* body = new btGhostObject();
	
	body->setInterpolationWorldTransform(*tr);

	body->setCollisionShape(shape);

	return body;

}

btRigidBody* PhysicsManager::createRigidBody(btTransform* tr, btCollisionShape* shape, int& userIdx_, const float& mass)
{
	//Si la forma es inv�lida, tira la ejecuci�n
	btAssert((!shape || shape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

	//Rigidbody es din�mico si la masa es distinta de cero, si no, est�tico
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);

	collisionShapes_->push_back(shape);

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
	userIdx_ = userIdxCount_;

	body->setUserIndex(userIdxCount_++);

	return body;
}

//btRigidBody::setAngularFactor evita rotaciones 

//CollideMasks:
//dynamicsWorld_.setGroupCollisionFlag(0, 0, False)
//bodyNP.setCollideMask(BitMask32.bit(0))