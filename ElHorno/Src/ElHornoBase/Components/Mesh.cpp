//#include "Mesh.h"
//#include "../ElHornoBase.h"; 
//
//
//#include "OgreSceneManager.h"
//#include "OgreEntity.h"
//#include "../ECS/Entity.h"
//#include "Transform.h"
//
//Mesh::Mesh(nlohmann::json& args) : Component() {}
//
//Mesh::~Mesh()
//{
//	Ogre::SceneNode* sn = ogreEntity_->getParentSceneNode();
//	if (sn != nullptr)
//		sn->detachAllObjects();
//	ElHornoBase::getInstance()->getSceneManager()->destroyEntity(ogreEntity_->getName());
//}
//
//void Mesh::init(nlohmann::json& args)
//{
//	std::string cast = args["mesh"];
//	meshFile_ = cast;
//	ogreEntity_ = ElHornoBase::getInstance()->getSceneManager()->createEntity(meshFile_);
//	castShadow_ = true;
//
//	if (!args["material"].is_null())
//	{
//		std::string aux = args["material"];
//		materialName_ = aux;
//		ogreEntity_->setMaterialName(args["material"], "Materials");
//	}
//
//	if (!args["castShadow_"].is_null())
//		castShadow_ = args["castShadow_"];
//
//	isAnimated_ = ((!args["isAnimated_"].is_null()) && (args["isAnimated_"]));
//
//	ogreEntity_->setCastShadows(castShadow_);
//	entity_->getComponent<Transform>("Transform")->getNode()->attachObject(ogreEntity_);
//}
//
//void Mesh::redefine(nlohmann::json& args)
//{
//	entity_->getComponent<Transform>("Transform")->getNode()->detachObject(ogreEntity_);
//
//	delete ogreEntity_;
//	ogreEntity_ = nullptr;
//
//	if (args["mesh"].is_null())
//		args["mesh"] = meshFile_;
//
//	if (args["material"].is_null())
//		args["material"] = materialName_;
//
//	if (args["isAnimated_"].is_null())
//		args["isAnimated_"] = isAnimated_;
//
//	init(args);
//}
//
//void Mesh::onEnable()
//{
//	ogreEntity_->setVisible(true);
//}
//
//void Mesh::onDisable()
//{
//	ogreEntity_->setVisible(false);
//}
//
//Ogre::AxisAlignedBox Mesh::getAABB() const
//{
//	return ogreEntity_->getBoundingBox();
//}
//
////Ogre::Real Mesh::getAABBRadius() const
////{
////	return ogreEntity_->getBoundingRadius();
////}
//
//Ogre::Entity* Mesh::getOgreEntity() const
//{
//	return ogreEntity_;
//}
//
//Ogre::Mesh* Mesh::getMesh() const
//{
//	return ogreEntity_->getMesh().get();
//}
//
//bool Mesh::isMeshAnimated() const
//{
//	return isAnimated_;
//}
