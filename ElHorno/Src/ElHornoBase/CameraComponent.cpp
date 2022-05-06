#include "AudioListenerComponent.h"
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
#include "SceneManager.h"
#include "Scene.h"
#include <math.h>

namespace El_Horno {

	CameraComponent::CameraComponent(HornoVector3 pos, HornoVector3 lookAt, HornoVector3 color, float alpha, int nearClDis, int farClDis)
	{
		camPos_ = HornoVectorToOgre(pos);
		lookAtVec_ = HornoVectorToOgre(lookAt);
		bgColor_ = Ogre::ColourValue(color.x_, color.y_, color.z_, alpha);

		nearClipDistance_ = nearClDis;
		farClipDistance_ = farClDis;
	}

	CameraComponent::CameraComponent()
	{
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
	void CameraComponent::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "position") {
				camPos_ = StringToVector(parameters[i].second);
			}
			else if (parameters[i].first == "lookAt") {
				lookAtVec_ = StringToVector(parameters[i].second);
			}
			else if (parameters[i].first == "color") {
				Ogre::Vector4 oG = StringToColor(parameters[i].second);
				bgColor_ = Ogre::ColourValue(oG.x, oG.y, oG.z, oG.w);
			}
			else if (parameters[i].first == "nearClDis") {
				nearClipDistance_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "farClDis") {
				farClipDistance_ = stoi(parameters[i].second);
			}
			else if (parameters[i].first == "target") {
				std::istringstream in(parameters[i].second);
				std::string val;         
				std::vector<std::string> values;          
				while (getline(in, val, ',')) 
					{ values.push_back(val); }
				if (SceneManager::getInstance()->getCurrentScene()->getEntity(values[0]) != nullptr) {
					target_ = SceneManager::getInstance()->getCurrentScene()->getEntity(values[0])->getComponent<Transform>("transform");
					following = true;
					lerpAmount_ = stof(values[1]);
					followDistance_ = HornoVector3(stof(values[2]), stof(values[3]), stof(values[4]));
				}
			}
		}
	}

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

	void CameraComponent::update()
	{
		if (following) {
			HornoVector3 targetPos = target_->getHornoGlobalPosition() + followDistance_;
			HornoVector3 actualPos = tr_->getHornoGlobalPosition();
			actualPos.x_ += (targetPos.x_ - actualPos.x_) * lerpAmount_;
			actualPos.z_ += (targetPos.z_ - actualPos.z_) * lerpAmount_;
			camPos_ = HornoVectorToOgre(actualPos);
			tr_->setGlobalPosition(camPos_);

		}
	}

	void CameraComponent::setFollow(Transform* tg, float lAmount, HornoVector3 fDistance)
	{
		following = true;
		target_ = tg;
		lerpAmount_ = lAmount;
		followDistance_ = fDistance;
	}

	Ogre::Camera* CameraComponent::getCamera()
	{
		return camera_;
	}
}