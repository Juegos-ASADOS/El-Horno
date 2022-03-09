#include "HornoCamera.h"
#include "../ElHornoBase.h"
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "../ECS/Entity.h"
#include "Transform.h"
#include <OgreSceneNode.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>

HornoCamera::HornoCamera()
{
}

HornoCamera::~HornoCamera()
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
void HornoCamera::start()
{
	cam = ElHornoBase::getInstance()->getSceneManager()->createCamera("cam");
	cam->setNearClipDistance(5);
	cam->setFarClipDistance(100000);
	//cam->setAspectRatio();

	tr_ = entity_->getComponent<Transform>("Transform");
	tr_->getNode()->attachObject(cam);
	tr_->setPosition(Ogre::Vector3(100, 100, 100));
	tr_->lookAt(Ogre::Vector3(0, 0, 0));

	vp = ElHornoBase::getInstance()->getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0, 1));

	//Es el deafult
	//cam->setAspectRatio(
	//	Ogre::Real(vp->getActualWidth()) /
	//	Ogre::Real(vp->getActualHeight()));
}

Ogre::Camera* HornoCamera::getCamera()
{
	return cam;
}
