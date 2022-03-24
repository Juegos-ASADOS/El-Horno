#include "ElHornoBase.h"; 
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "Entity.h"
#include "Mesh.h"
#include "Transform.h"
#include <OgreFileSystemLayer.h>

Mesh::Mesh(nlohmann::json& args) : Component(args) {}

/*
Desconecta el nodo del padre y destruye la entidad
*/
Mesh::~Mesh()
{
	Ogre::SceneNode* node = ogreEntity_->getParentSceneNode();
	if (node != nullptr)
		node->detachAllObjects();
	ElHornoBase::getInstance()->getSceneManager()->destroyEntity(ogreEntity_->getName());
}

/*
Coge desde un json la malla y crea una entidad. Establece:
	- Material
	- Casteo de sombras
	- Animación
Se le adjunta al nodo del transform
*/
void Mesh::start()
{
	if (!args_["mesh"].is_null())
	{
		meshName_ = "cube.mesh";
		ogreEntity_ = ElHornoBase::getInstance()->getSceneManager()->createEntity(meshName_);
		castShadow_ = false;
	}
	materialName_ = "";
	ogreEntity_->setMaterialName(materialName_);
	entity_->getComponent<Transform>("transform")->getNode()->attachObject(ogreEntity_); 
}

/*
Reestablece varibles de init para recomponer la malla
*/
void Mesh::redefine(nlohmann::json& args)
{
	/*entity_->getComponent<Transform>("Transform")->getNode()->detachObject(ogreEntity_);

	delete ogreEntity_;
	ogreEntity_ = nullptr;

	if (args["mesh"].is_null())
		args["mesh"] = meshName_;

	if (args["material"].is_null())
		args["material"] = materialName_;

	if (args["isAnimated_"].is_null())
		args["isAnimated_"] = isAnimated_;

	args_ = args;
	start();*/
}

void Mesh::onEnable()
{
	ogreEntity_->setVisible(true);
}

void Mesh::onDisable()
{
	ogreEntity_->setVisible(false);
}

Ogre::AxisAlignedBox Mesh::getAABB() const
{
	return ogreEntity_->getBoundingBox();
}

Ogre::Real Mesh::getAABBRadius() const
{
	return ogreEntity_->getBoundingRadius();
}

Ogre::Entity* Mesh::getOgreEntity() const
{
	return ogreEntity_;
}

/*
Devuelve ptr de SharedPtr<Mesh>
*/
Ogre::Mesh* Mesh::getMesh() const
{
	return ogreEntity_->getMesh().get();
}

bool Mesh::isMeshAnimated() const
{
	return isAnimated_;
}
