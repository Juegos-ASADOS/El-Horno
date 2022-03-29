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
		camPos = pos;
		lookAtVec = lookAt;
		bgColor = color;

		nearClipDistance = nearClDis;
		farClipDistance = farClDis;
	}

	CameraComponent::~CameraComponent()
	{
		Component::~Component();
		ElHornoBase::getGraphicsManager()->getRenderWindow()->removeViewport(vp->getZOrder());
		cam->getSceneManager()->destroyCamera("cam");
		//delete vp;
		vp = nullptr;
		cam = nullptr;
	}

	/*
	* Crea la camara, setea la distancia entre la que renderiza objetos (de 5 a 100000)
	* Los aspect ratio utilizan un default
	* La attachea al nodo del transform y coloca su posicion
	* Pone la camara (NO EL TRANSFORM QUE TAMB TIENE UN LOOKAT) mirando hacie el punto  //LA CAMARA NO TIENE LOOKAT, ESO ES DE OGREBITES//
	* Lo a�ade como viewport y seleccionames un color de fondo
	* Todas las variable est�n cableadas hasta la existencia de un json que setee los parametros
	*/
	void CameraComponent::start()
	{
		cam = ElHornoBase::getGraphicsManager()->getSceneManager()->createCamera("cam");
		cam->setNearClipDistance(nearClipDistance);
		cam->setFarClipDistance(farClipDistance);
		cam->setAutoAspectRatio(true);

		tr_ = entity_->getComponent<Transform>("transform");
		tr_->getNode()->attachObject(cam);
		tr_->setPosition(camPos);

		//ESTO NO VA
		tr_->lookAt(lookAtVec);

		vp = ElHornoBase::getGraphicsManager()->getRenderWindow()->addViewport(cam);
		vp->setBackgroundColour(bgColor);
	}

	Ogre::Camera* CameraComponent::getCamera()
	{
		return cam;
	}
}