#pragma once
#ifndef _MESH_H
#define _MESH_H

#include <string>
#include "../json.hpp"
#include "../ECS/Component.h"

namespace Ogre {
	class AxisAlignedBox;
	class Entity;
	class Mesh;
}

class Mesh : public Component
{
public:

	Mesh(nlohmann::json& args);
	~Mesh();

	virtual void start() override;
	void redefine(nlohmann::json& args);

	void onEnable() override;
	void onDisable() override;

	float getAABBRadius() const;

	//Metodos de Ogre
	Ogre::AxisAlignedBox getAABB() const;
	Ogre::Entity* getOgreEntity() const;
	Ogre::Mesh* getMesh() const;

	bool isMeshAnimated() const;
private:
	Ogre::Entity* ogreEntity_;
	bool isAnimated_;
	bool castShadow_;

	std::string meshName_;
	std::string materialName_;
};

#endif _MESH_H