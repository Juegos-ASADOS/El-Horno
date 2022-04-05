#include "ElHornoBase.h"; 
#include "AnimatorController.h"

#include "GraphicsManager.h"; 
#include "SceneManager.h"; 
#include "OgreSceneManager.h"

#include "CameraComponent.h"
#include <OgreCamera.h>
#include "Transform.h"
#include "Entity.h"
#include "Mesh.h"
#include "HornoConversions.h"
#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include "Timer.h"
#include "CheckMl.h"
#include <iostream>

namespace El_Horno {

	AnimatorController::AnimatorController()
	{
		// Despues hay que coger cada animacion del mapa de ogre y setear los parametros de los propios estados que ha generado la malla
		/*
		* animStatesMap_.at(name).setLoop(loop);
		* animStatesMap_.at(name).setSpeed(speed);
		*/

		// Activar todas 
		/*
		auto it = animStatesMap_->getAnimationStateIterator().begin();
		while (it != animStatesMap_->getAnimationStateIterator().end())
		{
			auto s = it->first; ++it;
		}*/

		// PARA EL SINBAD
		//// RunBase -> IdleBase
		//std::string state = "RunBase";
		//std::string nextState = "IdleBase";
		//TransitionMap t1;
		//t1.insert(std::pair<std::string, bool>(nextState, false));
		//animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t1));

		//// IdleBase -> RunBase
		//state = "IdleBase";
		//nextState = "RunBase";
		//TransitionMap t2;
		//t2.insert(std::pair<std::string, bool>(nextState, false));
		//// IdleBase -> Dance
		//state = "IdleBase";
		//nextState = "Dance";
		//t2.insert(std::pair<std::string, bool>(nextState, false));
		//animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t2));

		//// Dance -> IdleBase
		//state = "Dance";
		//nextState = "IdleBase";
		//TransitionMap t3;
		//t3.insert(std::pair<std::string, bool>(nextState, false));
		//animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t3));

		//// AnyState -> Dance
		//state = "AnyState";
		//nextState = "Dance";
		//TransitionMap t4;
		//t4.insert(std::pair<std::string, bool>(nextState, false));
		//animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t4));


		// PARA PIPO
		// RunBase -> IdleBase
		std::string state = "PipoWalkBien";
		std::string nextState = "PipoIdleBien";
		TransitionMap t1;
		t1.insert(std::pair<std::string, bool>(nextState, false));
		animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t1));

		// IdleBase -> RunBase
		state = "PipoIdleBien";
		nextState = "PipoWalkBien";
		TransitionMap t2;
		t2.insert(std::pair<std::string, bool>(nextState, false));
		// IdleBase -> Dance
		state = "PipoIdleBien";
		nextState = "Baile";
		t2.insert(std::pair<std::string, bool>(nextState, false));
		animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t2));

		// Dance -> IdleBase
		state = "Baile";
		nextState = "PipoIdleBien";
		TransitionMap t3;
		t3.insert(std::pair<std::string, bool>(nextState, false));
		animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t3));

		// AnyState -> Dance
		state = "AnyState";
		nextState = "Baile";
		TransitionMap t4;
		t4.insert(std::pair<std::string, bool>(nextState, false));
		animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t4));
	}


	AnimatorController::~AnimatorController()
	{

	}

	void AnimatorController::start()
	{
		// Obtenemos los componentes y entidades necesarios
		tr_ = entity_->getComponent<Transform>("transform");
		mesh_ = entity_->getComponent<Mesh>("mesh");
		node_ = tr_->getNode();
		ogreEntity_ = mesh_->getOgreEntity();

		// Recogemos todos los estados que traiga la malla
		animStatesMap_ = ogreEntity_->getAllAnimationStates();

		//LO DEL SINBAD
		// CurrentState (Dance)
		/*currentState_.name = "IdleBase";
		currentState_.state = animStatesMap_->getAnimationState("IdleBase");

		animStatesMap_->getAnimationState("RunBase")->setEnabled(true);
		animStatesMap_->getAnimationState("RunBase")->setLoop(true);
		animStatesMap_->getAnimationState("IdleBase")->setEnabled(true);
		animStatesMap_->getAnimationState("IdleBase")->setLoop(true);
		animStatesMap_->getAnimationState("Dance")->setEnabled(true);
		animStatesMap_->getAnimationState("Dance")->setLoop(true);*/

		//LO DEL PIPO
		currentState_.name = "PipoIdleBien";
		currentState_.state = animStatesMap_->getAnimationState("PipoIdleBien");

		animStatesMap_->getAnimationState("PipoWalkBien")->setEnabled(true);
		animStatesMap_->getAnimationState("PipoWalkBien")->setLoop(true);
		animStatesMap_->getAnimationState("PipoIdleBien")->setEnabled(true);
		animStatesMap_->getAnimationState("PipoIdleBien")->setLoop(true);
		animStatesMap_->getAnimationState("Baile")->setEnabled(true);
		animStatesMap_->getAnimationState("Baile")->setLoop(true);


	}

	void AnimatorController::update()
	{
		// Actualizamos la animacion actual
		currentState_.state->addTime(ElHornoBase::getInstance()->getDeltaTime());

		manageTransitions();
	}

	/*
	* Mira si alguna de las transiciones desde el currentState o desde el anyState estan activas para cambiar el estado de animacion actual
	*/
	void AnimatorController::manageTransitions()
	{
		// ANYSTATE
		for (auto nextPossiblesStates : animationStateMachine_.at("AnyState"))
		{
			int a = 0;
			// Si alguna de las transiciones desde el anyState estan a true cambiamos el estado
			if (nextPossiblesStates.second == true)
			{
				// Restauramos la transicion a false
				currentState_.state->setEnabled(false);
				currentState_.state->setLoop(false);
				animationStateMachine_.at("AnyState").at(nextPossiblesStates.first) = false;
				// Seteamos el nuevo estado
				currentState_.state = animStatesMap_->getAnimationState(nextPossiblesStates.first);
				currentState_.name = nextPossiblesStates.first;
				currentState_.state->setEnabled(true);
				currentState_.state->setLoop(true);

				return; // cortamos el metodo
			}

			// CURRENTSTATE
			for (auto nextPossiblesStates : animationStateMachine_.at(currentState_.name))
			{
				// Si alguna de las transiciones desde el currentState estan a true cambiamos el estado
				if (nextPossiblesStates.second == true)
				{
					// Restauramos la transicion a false
					currentState_.state->setEnabled(false);
					currentState_.state->setLoop(false);
					animationStateMachine_.at(currentState_.name).at(nextPossiblesStates.first) = false;
					// Seteamos el nuevo estado
					currentState_.state = animStatesMap_->getAnimationState(nextPossiblesStates.first);
					currentState_.name = nextPossiblesStates.first;
					currentState_.state->setEnabled(true);
					currentState_.state->setLoop(true);

					return; // cortamos el metodo
				}
			}
		}
	}

	// Usar para cambios de animaciones 
	void AnimatorController::setAnimBool(std::string state, std::string nextState, bool value)
	{
		animationStateMachine_.at(state).at(nextState) = value;
	}

	bool AnimatorController::getAnimBool(std::string state, std::string nextState)
	{
		return animationStateMachine_.at(state).at(nextState);
	}

	// Comprueba si la animacion actual ha terminado
	// Para que funcione el metodo deben ser animaciones no loopeadas
	bool AnimatorController::getHasEnded()
	{
		return currentState_.state->hasEnded();
	}
}