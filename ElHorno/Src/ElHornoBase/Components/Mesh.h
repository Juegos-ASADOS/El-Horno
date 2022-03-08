#pragma once
#ifndef _MESH_H
#define _MESH_H
//
//#include <string>
//#include "../json.hpp"
//#include "../ECS/Component.h"
//
//namespace Ogre {
//	class AxisAlignedBox;
//	class Real;
//	class Entity;
//	class Mesh;
//}
//
//class Mesh : public Component
//{
//public:
//
//	Mesh(nlohmann::json& args);
//	~Mesh();
//
//	void init(nlohmann::json& args);
//	void redefine(nlohmann::json& args);
//
//	void onEnable() override;
//	void onDisable() override;
//
//	//Metodos de Ogre
//	Ogre::AxisAlignedBox getAABB() const;
//	//Ogre::Real getAABBRadius() const;
//	Ogre::Entity* getOgreEntity() const;
//	Ogre::Mesh* getMesh() const;
//
//	bool isMeshAnimated() const;
//private:
//	Ogre::Entity* ogreEntity_;
//	bool isAnimated_;
//	bool castShadow_;
//
//	Ogre::String meshFile_;
//	Ogre::String materialName_;
//};

#endif _MESH_H