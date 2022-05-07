#pragma once
#ifndef _LightComponent_H
#define _LightComponent_H

#include "Component.h"
#include "HornoVector3.h"
//#include <OgreVector3.h>
//#include <map>

namespace Ogre {
	class Light;
}

namespace El_Horno {
	class Transform;

	class _declspec(dllexport) LightComponent : public Component
	{
	public:

		LightComponent(int type, HornoVector3 dirLight, HornoVector3 diffuse = HornoVector3(0.5,0.5,0.5), HornoVector3 specular = HornoVector3(0.5, 0.5, 0.5), float powerS = 1);
		LightComponent();
		~LightComponent();

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start() override;

		void setType(int type);
		
		void setDirection(const HornoVector3& dir);
		
		void setDiffuseColor(const HornoVector3& diffuse);
		void setSpecularColor(const HornoVector3& specular);

		void setPowerScale(float scale);
		void setSpotlightNearClipDistance(float distance);
		void setSpotlightInnerAngle(float degree);
		void setSpotlightOuterAngle(float degree);
		void setAttenuation(float range, float constant, float linear, float quadratic);
	private:

		// Acceso al nodo, Entidad de Ogre y Transform
		Transform* tr_ = nullptr;

		// Luz de ogre
		Ogre::Light* light_ = nullptr;
		int type_;
		HornoVector3 dirLight_;
		HornoVector3 diffuse_;
		HornoVector3 specular_;
		float powerScale_;
		//Ogre::ColourValue colourLight_;
	};
}
#endif _LightComponent_H