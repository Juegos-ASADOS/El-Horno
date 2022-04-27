#include "ElHornoBase.h"; 
#include "GraphicsManager.h"; 
#include "SceneManager.h"; 
#include "OgreSceneManager.h"
#include <OgreEntity.h>
#include "Entity.h"
#include "Mesh.h"
#include "Transform.h"
#include <OgreFileSystemLayer.h>
#include "CheckML.h"
#include <OgreLogManager.h>
#include <iostream>

namespace El_Horno {
	Mesh::Mesh(std::string name, bool castShadow, bool isAnimated)
	{
		meshName_ = name + ".mesh";
		materialName_ = name + ".mesh";
		castShadow_ = castShadow;
		isAnimated_ = isAnimated;
	}

	/*
	Desconecta el nodo del padre y destruye la entidad
	*/
	Mesh::~Mesh()
	{
		Ogre::SceneNode* node = ogreEntity_->getParentSceneNode();
		if (node != nullptr)
			node->detachAllObjects();
		ElHornoBase::getGraphicsManager()->getSceneManager()->destroyEntity(ogreEntity_->getName());
	}

	void Mesh::setParameters(std::vector<std::pair<std::string, std::string>> parameters)
	{
		for (int i = 0; i < parameters.size(); i++) {
			if (parameters[i].first == "name") {
				meshName_ = parameters[i].second + ".mesh";
				materialName_ = parameters[i].second + ".mesh";
			}
		}
		castShadow_ = true;
		isAnimated_ = false;
	}

	/*
	Crea una entidad. Establece:
		- Material
		- Casteo de sombras
		- Animación
	Se le adjunta al nodo del transform
	*/
	void Mesh::start()
	{
		try {

			ogreEntity_ = ElHornoBase::getInstance()->getGraphicsManager()->createEntity(meshName_);
		}
		catch (Ogre::Exception& e) {
			Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
			return;
		}
		//ogreEntity_->setMaterialName(materialName_);
		ogreEntity_->setCastShadows(castShadow_);

		/* Enseña las animaciones posibles del skeleton
		for (auto s : ogreEntity_->getAnimableValueNames()) {
			std::cout << s;
		};*/
		if (entity_->getComponent<Transform>("transform")->getNode() != NULL)
			entity_->getComponent<Transform>("transform")->getNode()->attachObject(ogreEntity_);
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

	void Mesh::attachObject(std::string bone, Entity* obj)
	{
		ogreEntity_->attachObjectToBone(bone, obj->getComponent<Mesh>("mesh")->ogreEntity_);
	}

	void Mesh::detachObject(Entity* obj)
	{
		ogreEntity_->detachObjectFromBone(obj->getComponent<Mesh>("mesh")->ogreEntity_);
	}

	bool Mesh::isMeshAnimated() const
	{
		return isAnimated_;
	}
}