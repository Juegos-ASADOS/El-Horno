#include "CameraComponent.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "Entity.h"
#include "Transform.h"
#include <OgreSceneNode.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include "CheckML.h"
namespace El_Horno {

	CameraComponent::CameraComponent(Ogre::Vector3 pos, Ogre::Vector3 lookAt, Ogre::ColourValue color, int nearClDis, int farClDis)
	{
		camPos_ = pos;
		lookAtVec_ = lookAt;
		bgColor_ = color;

		nearClipDistance_ = nearClDis;
		farClipDistance_ = farClDis;
	}

	CameraComponent::~CameraComponent()
	{
		Component::~Component();
		ElHornoBase::getGraphicsManager()->getRenderWindow()->removeViewport(viewport_->getZOrder());
		camera_->getSceneManager()->destroyCamera("cam");
		viewport_ = nullptr;
		camera_ = nullptr;
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
		camera_ = ElHornoBase::getGraphicsManager()->getSceneManager()->createCamera("cam");
		camera_->setNearClipDistance(nearClipDistance_);
		camera_->setFarClipDistance(farClipDistance_);
		camera_->setAutoAspectRatio(true);

		tr_ = entity_->getComponent<Transform>("transform");
		tr_->getNode()->attachObject(camera_);
		tr_->setPosition(camPos_);

		tr_->lookAt(lookAtVec_);

		viewport_ = ElHornoBase::getGraphicsManager()->getRenderWindow()->addViewport(camera_);
		viewport_->setBackgroundColour(bgColor_);
	}

	Ogre::Camera* CameraComponent::getCamera()
	{
		return camera_;
	}
}