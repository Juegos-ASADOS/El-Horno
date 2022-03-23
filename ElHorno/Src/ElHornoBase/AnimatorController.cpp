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

}


