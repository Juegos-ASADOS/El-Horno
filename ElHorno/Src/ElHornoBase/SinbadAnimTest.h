#pragma once
#ifndef _SinbadAnimTest_H
#define _SinbadAnimTest_H

#include <string>
#include "Component.h"
#include <OgreVector3.h>

namespace El_Horno {
	class Transform;
	class AnimatorController;
}
namespace El_Horno
{

	class SinbadAnimTest : public Component
	{
	public:

		SinbadAnimTest();
		~SinbadAnimTest();

		void start() override;
		void update()override;

		void onEnable() override {};
		void onDisable()override {};

		bool recieveEvent(Event* e) override;
	private:

		// Acceso al nodo, Entidad de Ogre y Transform
		Ogre::SceneNode* node_;
		Ogre::Entity* ogreEntity_;
		Transform* tr_ = nullptr;

		AnimatorController* anim_;

		bool dancing = false;
		bool walking = false;

	};
}

#endif _SinbadAnimTest_H