#include "ElHornoBase.h"; 
#include "GraphicsManager.h"; 
#include "SceneManager.h"; 
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "Entity.h"
#include "Mesh.h"
#include "Transform.h"
#include <OgreFileSystemLayer.h>
#include "CheckML.h"
#include <OgreLogManager.h>

namespace El_Horno {
	Mesh::Mesh(std::string name, bool castShadow, bool isAnimated)
	{
		meshName_ = name + ".mesh";
		//materialName_ = name + ".mesh";
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
		//ogreEntity_->setMaterialName("Sandokan");
		ogreEntity_->setCastShadows(castShadow_);
		entity_->getComponent<Transform>("transform")->getNode()->attachObject(ogreEntity_);
	}

	/*
	Reestablece varibles de init para recomponer la malla
	*/
	void Mesh::redefine()
	{

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
}