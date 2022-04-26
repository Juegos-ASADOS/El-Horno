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
#include "CheckML.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreColourValue.h>

namespace El_Horno {
	LightComponent::LightComponent(int type, HornoVector3 dirLight/*, Ogre::ColourValue colourLight*/)
	{
		type_ = type;
		dirLight_ = HornoVectorToOgre(dirLight);
		//colourLight_ = colourLight;
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
			light_->setType(Ogre::Light::LT_POINT);
			break;

			// DIRECTIONAL
		case 1:
			light_->setType(Ogre::Light::LT_DIRECTIONAL);
			break;

			// FOCO
		case 2:
			light_->setType(Ogre::Light::LT_SPOTLIGHT);
			light_->setSpotlightNearClipDistance(1);
			light_->setSpotlightInnerAngle(Ogre::Degree(15));
			light_->setSpotlightOuterAngle(Ogre::Degree(90.0f));
			break;

		default:
			light_->setType(Ogre::Light::LT_POINT);
			break;
		}

		// Establecemos sus parametros basicos
		light_->setDiffuseColour(1.0, 1.0, 1.0);

		tr_ = entity_->getComponent<Transform>("transform");
		tr_->getNode()->attachObject(light_);
		//entity_->getComponent<Transform>("transform")->getNode()->attachObject(light_);
		tr_->setDirection(dirLight_);
	}

	void LightComponent::update()
	{

	}
}