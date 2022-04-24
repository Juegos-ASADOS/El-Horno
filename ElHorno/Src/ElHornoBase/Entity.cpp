#include "Entity.h"
#include "Component.h"
#include "FactoryCreator.h"
#include "Scene.h"
#include "SceneManager.h"
#include <string>
#include "CheckML.h"
#include "Transform.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include <OgreSceneManager.h>

namespace El_Horno {

	Entity::Entity(std::string n, Scene* m, Entity* p) : name_(n), scene_(m), active_(true), comp_(), compRef_() {
		if (p != nullptr) {
			p->addChild(this);
		}
	}

	// Elimina componentes, entidades hijas y se elimina del padre
	Entity::~Entity() {

		for (Component* c : compRef_) {
			delete c;
			c = nullptr;
		}
		comp_.clear();
		/*	for (Entity* e : children_)
				delete e;*/
		children_.clear();

		scene_ = nullptr;
		if (parent_ != nullptr) {
			parent_->removeChild(this);
			parent_ = nullptr;
		}
	}

	// Inicializa componentes
	void Entity::start()
	{
		std::size_t n = compRef_.size();
		for (auto i = 0u; i < n; i++) {
			if (compRef_[i]->isActive())
				compRef_[i]->start();
		}
	}

	// Preuodate de componentes
	void Entity::preUpdate()
	{
		std::size_t n = compRef_.size();
		for (auto i = 0u; i < n; i++) {
			if (compRef_[i]->isActive())
				compRef_[i]->preUpdate();
		}
	}

	// Update de componentes
	void Entity::update() {
		std::size_t n = compRef_.size();
		for (auto i = 0u; i < n; i++) {
			if (compRef_[i]->isActive())
				compRef_[i]->update();
		}
	}

	// Renderiza
	void Entity::render() {
		std::size_t n = compRef_.size();
		for (auto i = 0u; i < n; i++) {
			if (compRef_[i]->isActive())
				compRef_[i]->render();
		}
	}

	void Entity::addComponent(std::string name, std::vector<pair<string, string>> parameters)
	{
		auto components = SceneManager::getInstance()->getComponents();
		auto it = components.find(name);
		Component* c = (it->second)(parameters);
	}

	bool Entity::hasComponent(std::string name) const {
		return comp_.find(name) != comp_.end();
	}

	void Entity::removeComponent(std::string name) {
		if (hasComponent(name)) {
			for (Component* c : compRef_)
				if (c->getName() == name) delete c;
			comp_.erase(name);
		}
	}

	void Entity::removeComponents() {
		for (Component* c : compRef_)
			delete c;
		comp_.clear();
	}

	inline void Entity::setParent(Entity* p)
	{
		parent_ = p;
		Transform* t = getComponent<Transform>("transform");

		if (p->getComponent<Transform>("transform")->getNode() != NULL) {
			if (p == nullptr) {
				Ogre::SceneNode* sc = ElHornoBase::getInstance()->getGraphicsManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				t->setNode(sc);
			}
			else
				t->setNode(p->getComponent<Transform>("transform")->getNode()->createChildSceneNode());
		}
	};

	Entity* Entity::getChild(std::string name) {
		for (Entity* e : children_)
			if (e->getName() == name) return e;

		return nullptr;
	}

	void Entity::addChild(Entity* c) {
		children_.push_back(c);
		c->setParent(this);
	}

	void Entity::removeChild(Entity* e) {
		int i = 0;
		for (Entity* c : children_) {
			if (c == e) {
				children_.erase(children_.begin() + i);
				return;
			}
			i++;
		}
	}
}