#pragma once
#ifndef _LightComponent_H
#define _LightComponent_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>
#include <map>

namespace Ogre {
	class ColourValue;
}
class Mesh;
class Transform;


namespace El_Horno {
	class HornoVector3;

	class _declspec(dllexport) LightComponent : public Component
	{
	public:

		LightComponent(int type, HornoVector3 dirLight/*, Ogre::ColourValue colourLight*/);
		~LightComponent();

		void start() override;
		void update()override;

		void onEnable() override {};
		void onDisable()override {};

	private:

		// Acceso al nodo, Entidad de Ogre y Transform
		Ogre::SceneNode* node_ = nullptr;
		Ogre::Entity* ogreEntity_;
		Transform* tr_ = nullptr;

		// Luz de ogre
		Ogre::Light* light_;
		int type_;
		Ogre::Vector3 dirLight_;
		//Ogre::ColourValue colourLight_;
	};
}
#endif _LightComponent_H