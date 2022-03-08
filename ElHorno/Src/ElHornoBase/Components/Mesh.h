#pragma once
#ifndef _MESH_H
#define _MESH_H

#include <string>
#include "../ECS/Component.h"
#include "../json.hpp"
#include "OgreAxisAlignedBox.h"

class Mesh : public Component
{
public:

	Mesh(nlohmann::json& arg);
	~Mesh();

	void init(nlohmann::json& args);
	void redefine(nlohmann::json& args);

	void onEnable() override;
	void onDisable() override;

	//Metodos de Ogre
	Ogre::AxisAlignedBox getAABB() const;
	Ogre::Real getAABBRadius() const;
	Ogre::Entity* getOgreEntity() const;
	Ogre::Mesh* getMesh() const;

	bool isMeshAnimated() const;
private:
	Ogre::Entity* ogreEntity;
	bool isAnimated;
	bool castShadow;		

	Ogre::String meshFile;
	Ogre::String materialName;
};

#endif _MESH_H