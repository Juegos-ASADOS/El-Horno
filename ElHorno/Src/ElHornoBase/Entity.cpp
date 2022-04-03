#include "Entity.h"
#include "Component.h"
#include "FactoryCreator.h"
#include "Scene.h"
#include <string>
#include "CheckML.h"

namespace El_Horno {

	Entity::Entity(std::string n, Scene* m, Entity* p) : name_(n), scene_(m), active_(true), comp_(), compRef_() {
		parent_ = p;

		if (parent_ != nullptr) {
			parent_->addChild(this);
		}
	}

	// Elimina componentes, entidades hijas y se elimina del padre
	Entity::~Entity() {

		for (Component* c : compRef_) {
			delete c;
			c = nullptr;
		}
		comp_.clear();
		for (Entity* e : children_)
			delete e;

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

	bool Entity::hasComponent(std::string name) const{
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

	Entity* Entity::getChild(std::string name) {
		for (Entity* e : children_)
			if (e->getName() == name) return e;

		return nullptr;
	}

	void Entity::addChild(Entity* c) {
		children_.push_back(c);
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