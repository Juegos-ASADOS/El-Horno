#include "ElHornoBase.h"; 
#include "AnimatorController.h"

//#include "OgreEntity.h"
#include "CameraComponent.h"
#include <OgreCamera.h>
#include "Transform.h"
#include "LightComponent.h"
#include "Mesh.h"
#include "Entity.h"
#include "HornoConversions.h"
#include <OgreAnimationState.h>
#include <OgreEntity.h>
#include <OgreLight.h>
#include "Timer.h"

LightComponent::LightComponent(int type)
{
	switch (type)
	{
		// POINT
		case 0:
		{
			light_->setType(Ogre::Light::LT_POINT);
		}
		break;

		// DIRECTIONAL
		case 1:
		{
			light_->setType(Ogre::Light::LT_DIRECTIONAL);
		}
		break;

		// FOCO
		case 2:
		{
			light_->setType(Ogre::Light::LT_SPOTLIGHT);
		}
		break;
	}
}

LightComponent::~LightComponent()
{

}

void AnimatorController::start()
{
	// Obtenemos los componentes y entidades necesarios
	tr_ = entity_->getComponent<Transform>("Transform");
	mesh_ = entity_->getComponent<Mesh>("Mesh");
	node_ = tr_->getNode();
	ogreEntity_ = mesh_->getOgreEntity();

}

void AnimatorController::update()
{

}

