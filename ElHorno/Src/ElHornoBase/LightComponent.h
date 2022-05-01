#pragma once
#ifndef _LightComponent_H
#define _LightComponent_H

#include "Component.h"
#include <OgreVector3.h>
//#include <map>

namespace El_Horno {
	class HornoVector3;
	class Transform;

	class _declspec(dllexport) LightComponent : public Component
	{
	public:

		LightComponent(int type, HornoVector3 dirLight/*, Ogre::ColourValue colourLight*/);
		LightComponent();
		~LightComponent();

		void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		void start() override;

	private:

		// Acceso al nodo, Entidad de Ogre y Transform
		Transform* tr_ = nullptr;

		// Luz de ogre
		Ogre::Light* light_ = nullptr;
		int type_;
		Ogre::Vector3 dirLight_;
		//Ogre::ColourValue colourLight_;
	};
}
#endif _LightComponent_H