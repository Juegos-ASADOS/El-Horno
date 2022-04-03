#pragma once
#ifndef _PHYSICS_CALLBACKS_H
#define _PHYSICS_CALLBACKS_H
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "Rigibody.h"

#include "Event.h"
#include "EventManager.h"


namespace El_Horno {

	//Indica como debe actuar la fisica al empezar una colision trigger
	void contactStartBullet(btPersistentManifold* const& manifold) {
		//Tomamos los dos rb guardados previamente en UserPointer
		RigidBody* rb1 = static_cast<RigidBody*>(manifold->getBody0()->getUserPointer());
		RigidBody* rb2 = static_cast<RigidBody*>(manifold->getBody1()->getUserPointer());

		//Si existen
		if (rb1 && rb2) {
			Event* e;
			
			//Guarda en el mensaje la referencia al otro, 
			//eligiendo el mensaje en funcion de si es trigger
			if (rb1->isTrigger()) e = new rbTriggerEnter(rb2->getEntity());
			else e = new rbCollisionEnter(rb2->getEntity());

			//Y le envía el evento al primero
			EventManager::getInstance()->sendEntityEvent(rb1->getEntity(), e);

			//Así con el otro también
			if (rb2->isTrigger()) e = new rbTriggerEnter(rb1->getEntity());
			else e = new rbCollisionEnter(rb1->getEntity());

			EventManager::getInstance()->sendEntityEvent(rb2->getEntity(), e);
		}
	}
	

	//Indica como debe actuar la fisica al empezar una colision
	bool contactProcessedBullet(btManifoldPoint& cp, void* body0, void* body1) {
		btCollisionObject* colObj0 = static_cast<btCollisionObject*>(body0);
		btCollisionObject* colObj1 = static_cast<btCollisionObject*>(body1);

		RigidBody* rb1 = static_cast<RigidBody*>(colObj0->getUserPointer());
		RigidBody* rb2 = static_cast<RigidBody*>(colObj1->getUserPointer());

		if (rb1 && rb2) {
			Event* e;

			if (rb1->isTrigger()) e = new rbTriggerStay(rb2->getEntity());
			else e = new rbCollisionStay(rb2->getEntity());

			EventManager::getInstance()->sendEntityEvent(rb1->getEntity(), e);

			if (rb2->isTrigger()) e = new rbTriggerStay(rb1->getEntity());
			else e = new rbCollisionStay(rb1->getEntity());

			EventManager::getInstance()->sendEntityEvent(rb2->getEntity(), e);
		}
		
		return true; //no importa su valor
	}


	//Indica como debe actuar la fisica al salir una colision trigger
	void contactExitBullet(btPersistentManifold* const& manifold) {
		RigidBody* rb1 = static_cast<RigidBody*>(manifold->getBody0()->getUserPointer());
		RigidBody* rb2 = static_cast<RigidBody*>(manifold->getBody1()->getUserPointer());

		if (rb1 && rb2) {
			Event* e;
			
			if (rb1->isTrigger()) e = new rbTriggerExit(rb2->getEntity());
			else e = new rbCollisionExit(rb2->getEntity());
			
			EventManager::getInstance()->sendEntityEvent(rb1->getEntity(), e);
			
			if (rb2->isTrigger()) e = new rbTriggerExit(rb1->getEntity());
			else e = new rbCollisionExit(rb1->getEntity());

			EventManager::getInstance()->sendEntityEvent(rb2->getEntity(), e);
		}
	}

}


#endif _PHYSICS_CALLBACKS_H