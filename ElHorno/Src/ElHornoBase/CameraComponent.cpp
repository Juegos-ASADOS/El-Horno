#include "CameraComponent.h"
#include "ElHornoBase.h"
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "Entity.h"
#include "Transform.h"
#include <OgreSceneNode.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>

CameraComponent::CameraComponent(nlohmann::json& args) : Component(args)
{
}

CameraComponent::~CameraComponent()
{
	Component::~Component();
	ElHornoBase::getInstance()->getRenderWindow()->removeViewport(vp->getZOrder());
	cam->getSceneManager()->destroyCamera("cam");
	delete vp;
	vp = nullptr;
	cam = nullptr;
}

/*
* Crea la camara, setea la distancia entre la que renderiza objetos (de 5 a 100000)
* Los aspect ratio utilizan un default
* La attachea al nodo del transform y coloca su posicion
* Pone la camara (NO EL TRANSFORM QUE TAMB TIENE UN LOOKAT) mirando hacie el punto 
* Lo añade como viewport y seleccionames un color de fondo
* Todas las variable están cableadas hasta la existencia de un json que setee los parametros
*/
void CameraComponent::start()
{
	int camNearClipDistance = 1;
	int setFarClipDistance = 10000;

	Ogre::Vector3 camPos = Ogre::Vector3(100, 100, 100);
	Ogre::Vector3 lookAtVec = Ogre::Vector3(0, 0, 0);
	Ogre::ColourValue bgColor = Ogre::ColourValue(0, 0, 1, 1);

	/*if (!args_["nearClipDistance"].is_null())	
		camNearClipDistance = args_["nearClipDistance"];
	if (!args_["farClipDistance"].is_null())	
		setFarClipDistance = args_["farClipDistance"];
	if (!args_["lookAt"].is_null())
	{
		lookAtVec.x = args_["lookAt"][0];
		lookAtVec.y = args_["lookAt"][1];
		lookAtVec.z = args_["lookAt"][2];
	}
	if (!args_["bgColor"].is_null())
	{
		bgColor.r = args_["bgColor"][0];
		bgColor.g = args_["bgColor"][1];
		bgColor.b = args_["bgColor"][2];
		bgColor.a = args_["bgColor"][3];
	}
	else if (!args_["bgColour"].is_null())
	{
		bgColor.r = args_["bgColour"][0];
		bgColor.g = args_["bgColour"][1];
		bgColor.b = args_["bgColour"][2];
		bgColor.a = args_["bgColour"][3];
	}*/

	cam = ElHornoBase::getInstance()->getSceneManager()->createCamera("cam");
	cam->setNearClipDistance(camNearClipDistance);
	cam->setFarClipDistance(setFarClipDistance);
	cam->setAspectRatio(true); 

	tr_ = entity_->getComponent<Transform>("transform");
	tr_->getNode()->attachObject(cam);
	tr_->setPosition(camPos);
	tr_->lookAt(lookAtVec);

	vp = ElHornoBase::getInstance()->getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(bgColor);
}

Ogre::Camera* CameraComponent::getCamera()
{
	return cam;
}
