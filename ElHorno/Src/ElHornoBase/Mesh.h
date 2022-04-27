#pragma once
#ifndef _MESH_H
#define _MESH_H

#include <string>
#include <vector>
#include "Component.h"

namespace Ogre {
	class AxisAlignedBox;
	class Entity;
	class Mesh;
}

namespace El_Horno {
	class _declspec(dllexport) Mesh : public Component
	{
	public:

		Mesh(std::string name, bool castShadow = true, bool isAnimated = false);
		Mesh() {};
		~Mesh();

		virtual void setParameters(std::vector<std::pair<std::string, std::string>> parameters) override;
		virtual void start() override;

		void onEnable() override;
		void onDisable() override;

		float getAABBRadius() const;

		//Metodos de Ogre
		Ogre::AxisAlignedBox getAABB() const;
		Ogre::Entity* getOgreEntity() const;
		Ogre::Mesh* getMesh() const;

		void attachObject(std::string bone, Entity* obj);
		void detachObject(Entity* obj);

		bool isMeshAnimated() const;
	private:
		Ogre::Entity* ogreEntity_;
		bool isAnimated_;
		bool castShadow_;

		std::string meshName_;
		std::string materialName_;
	};
}
#endif _MESH_H