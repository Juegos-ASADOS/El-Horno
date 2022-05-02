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
#include <vector>

namespace El_Horno {

	AnimatorController::AnimatorController(std::vector<std::pair<std::string, std::string>> animVector)
	{
		// Generar la maquina de estados
		for (int i = 0; i < animVector.size(); i++)
		{
			std::string state = animVector[i].first;
			std::string nextState = animVector[i].second;
			TransitionMap t;
			t.insert(std::pair<std::string, bool>(nextState, false));

			// Si el estado no existe lo metemos
			if (!animationStateMachine_.count(state))
				animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t));
			// Si existe metemos otro estado a las transiones de ese
			else
				animationStateMachine_.at(state).insert(std::pair<std::string, bool>(nextState, false));
		}

		// Seteamos el estado incial al primero de la maquina de estados
		currentState_.name = animVector[0].first;
	}

	AnimatorController::AnimatorController()
	{
	}


	AnimatorController::~AnimatorController()
	{

	}

	void AnimatorController::setParameters(std::vector<std::pair<std::string, std::string>> animVector)
	{
		// Generar la maquina de estados
		for (int i = 0; i < animVector.size(); i++)
		{
			std::string state = animVector[i].first;
			std::string nextState = animVector[i].second;
			TransitionMap t;
			t.insert(std::pair<std::string, bool>(nextState, false));

			// Si el estado no existe lo metemos
			if (!animationStateMachine_.count(state))
				animationStateMachine_.insert(std::pair<std::string, TransitionMap>(state, t));
			// Si existe metemos otro estado a las transiones de ese
			else
				animationStateMachine_.at(state).insert(std::pair<std::string, bool>(nextState, false));
		}

		// Seteamos el estado incial al primero de la maquina de estados
		currentState_.name = animVector[0].first;
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

		// Seteamos el estado incial al primero de la maquina de estados
		currentState_.state = animStatesMap_->getAnimationState(currentState_.name);
		currentState_.state->setEnabled(true);
		currentState_.state->setLoop(true);

		//auto it = animStatesMap_->getAnimationStateIterator().begin();
		//while (it != animStatesMap_->getAnimationStateIterator().end())
		//{
		//	//it->second->setEnabled(true);
		//	//it->second->setLoop(true);
		//	++it;
		//}

	}

	void AnimatorController::update()
	{
		// Actualizamos la animacion actual
		currentState_.state->addTime(ElHornoBase::getInstance()->getDeltaTime() / 2);

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