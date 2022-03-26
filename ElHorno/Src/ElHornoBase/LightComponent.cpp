#include "LightComponent.h"
#include "ElHornoBase.h"; 


#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "Mesh.h"
#include "Entity.h"
#include "HornoConversions.h"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include "CheckMl.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

LightComponent::LightComponent(int type, Ogre::Vector3 dirLight, Ogre::ColourValue colourLight)
{
	type_ = type;
	dirLight_ = dirLight;
	colourLight_ = colourLight;
}

LightComponent::~LightComponent()
{

}

void LightComponent::start()
{
	// Creamos la luz
	light_ = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->createLight();

	// Seteamos su tipo
	switch (type_)
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
		light_->setSpotlightNearClipDistance(1);
		light_->setSpotlightInnerAngle(Ogre::Degree(15));
		light_->setSpotlightOuterAngle(Ogre::Degree(90.0f));

	}
	break;
	}

	// A�adimos sus parametros basicos
	light_->setDiffuseColour(colourLight_);
	node_ = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(light_);
	node_->setDirection(dirLight_);

}

void LightComponent::update()
{

}

