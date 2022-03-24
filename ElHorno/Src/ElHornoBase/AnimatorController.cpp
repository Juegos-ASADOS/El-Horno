#include "ElHornoBase.h"; 
#include "AnimatorController.h"

//#include "OgreEntity.h"
#include "CameraComponent.h"
#include <OgreCamera.h>
#include "Transform.h"
#include "Mesh.h"
#include "Entity.h"
#include "HornoConversions.h"
#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include "Timer.h"

AnimatorController::AnimatorController() 
{
	
}

AnimatorController::~AnimatorController() 
{

}

void AnimatorController::start()
{
	// Obtenemos los componentes y entidades necesarios
	tr_ = entity_->getComponent<Transform>("Transform");
	mesh_ = entity_->getComponent<Mesh>("Mesh");
	node_ = tr_->getNode();
	ogreEntity_ = mesh_->getOgreEntity();

	// Recogemos todos los estados que traiga la malla
	animStatesMap_ = ogreEntity_->getAllAnimationStates();
	
}

void AnimatorController::update()
{
	// Cogemos el delta time
	float dt = ElHornoBase::getInstance()->getGlobalTime()->getTime();

	// Actualizamos la animacion actual
	currentState_.state->addTime(dt);

	// Miramos si hay que cambiar de estado de animacion
	manageTransitions();
}


/*
* Mira si alguna de las transiciones desde el currentState o desde el anyState estan activas para cambiar el estado de animacion actual
*/
void AnimatorController::manageTransitions()
{

	// AnyState (transiciones desde cualquier estado)
	int i = 0;
	while (!transitionsMap_.at("anyState")[i].cond && i < transitionsMap_.at("anyState").size())
		i++;
	// Si no hemos llegado al final es que hemos encontrado un estado al que hay que moverse
	if (i < transitionsMap_.at("anyState").size())
	{
		currentState_.state = animStatesMap_->getAnimationState(transitionsMap_.at("anyState")[i].nextState);
		return; //acabamos el metodo
	}


	//Desde el currentState
	i = 0;
	while (!transitionsMap_.at(currentState_.name)[i].cond && i < transitionsMap_.at(currentState_.name).size())
		i++;
	// Si no hemos llegado al final es que hemos encontrado un estado al que hay que moverse
	if (i < transitionsMap_.at(currentState_.name).size())
		currentState_.state = animStatesMap_->getAnimationState(transitionsMap_.at(currentState_.name)[i].nextState);


}

void AnimatorController::setAnimBool(std::string state, bool cond_, int numCond)
{
	transitionsMap_.at(state)[numCond].cond = cond_;
}

bool AnimatorController::getAnimBool(std::string state, int numCond)
{
	return transitionsMap_.at(state)[numCond].cond;
}


