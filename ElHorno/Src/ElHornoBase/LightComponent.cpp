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

	LightComponent::LightComponent()
	{
	}

	LightComponent::~LightComponent()
	{
		//Ogre::SceneNode* node = ogreEntity_->getParentSceneNode();
		//if (node != nullptr)
		//	node->detachAllObjects();
		ElHornoBase::getGraphicsManager()->getSceneManager()->destroyLight(light_);
		light_ = nullptr;
	}

	void LightComponent::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		// Creamos la luz
		light_ = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->createLight();

		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "type") {
				type_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "dirLight") {
				dirLight_ = StringToVector(parameters[i].second);
			}
		}
	}

	void LightComponent::start()
	{
		//// Creamos la luz
		//light_ = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->createLight();

		setType(type_);

		// Establecemos sus parametros basicos
		/*light_->setDiffuseColour(1.0, 1.0, 1.0);
		light_->setSpecularColour(.8, .7, .8);
		light_->setPowerScale(1);*/

		tr_ = entity_->getComponent<Transform>("transform");
		tr_->getNode()->attachObject(light_);
		//tr_->setDirection(Ogre::Vector3(0, -1, -0.3));
	}
	void LightComponent::setType(int type)
	{
		type_ = type;
		// Seteamos su tipo
		switch (type)
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
			break;

		default:
			light_->setType(Ogre::Light::LT_POINT);
			break;
		}
	}
	void LightComponent::setDirection(const HornoVector3& dir)
	{
		tr_->setDirection(dir);
	}
	void LightComponent::setDiffuseColor(const HornoVector3& diffuse)
	{
		light_->setDiffuseColour(diffuse.x_, diffuse.y_, diffuse.z_);
	}
	void LightComponent::setSpecularColor(const HornoVector3& specular)
	{
		light_->setSpecularColour(specular.x_, specular.y_, specular.z_);
	}
	void LightComponent::setPowerScale(float scale)
	{
		light_->setPowerScale(scale);
	}
	void LightComponent::setSpotlightNearClipDistance(float distance)
	{
		light_->setSpotlightNearClipDistance(distance);
	}
	void LightComponent::setSpotlightOuterAngle(float degree)
	{
		light_->setSpotlightOuterAngle(Ogre::Degree(degree));
	}
	void LightComponent::setSpotlightInnerAngle(float degree)
	{
		light_->setSpotlightInnerAngle(Ogre::Degree(degree));
	}
}