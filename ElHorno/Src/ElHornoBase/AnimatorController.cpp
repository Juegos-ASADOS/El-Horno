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
#include "CheckMl.h"

AnimatorController::AnimatorController() 
{
	// Aqui le deberia entrar un archivo de configuracion de animaciones para setear los parametros que sean necesarios
	// Formato:
	/*
	* name: danceState
	* loop: true
	* speed: 1 ...
	*/

	// Despues hay que coger cada animacion del mapa de ogre y setear los parametros de los propios estados que ha generado la malla
	/*
	* animStatesMap_.at(name).setLoop(loop);
	* animStatesMap_.at(name).setSpeed(speed);
	*/
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
	// ANYSTATE
	for (auto t : transitionsMap_.at("anyState"))
	{
		// Si alguna de las transiciones desde el anyState estan a true cambiamos el estado
		if (t.second->cond)
		{
			currentState_.state = animStatesMap_->getAnimationState(t.second->nextState);
			return; // cortamos el metodo
		}
	}

	// CURRENTSTATE
	for (auto t : transitionsMap_.at(currentState_.name))
	{
		// Si alguna de las transiciones desde el currentState estan a true cambiamos el estado
		if (t.second->cond)
		{
			currentState_.state = animStatesMap_->getAnimationState(t.second->nextState);
			return; // cortamos el metodo
		}
	}
}

// Usar para cambios de animaciones 
void AnimatorController::setAnimBool(std::string state, std::string conditionName, bool value)
{
	transitionsMap_.at(state).at(conditionName)->cond = value;
}

bool AnimatorController::getAnimBool(std::string state, std::string conditionName)
{
	return transitionsMap_.at(state).at(conditionName)->cond;
}


