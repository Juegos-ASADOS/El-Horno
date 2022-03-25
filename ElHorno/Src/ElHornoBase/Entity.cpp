#include "Entity.h"
#include "Component.h"
#include "FactoryCreator.h"
#include "Scene.h"
#include <string>
#include "CheckMl.h"

Entity::Entity(std::string n, Scene* m, Entity* p) : name_(n), mngr_(m), active_(true), comp_(), compRef_() {
	parent_ = p;

	if (parent_ != nullptr) {
		parent_->addChild(this);
	}
}

Entity::~Entity() {
	for (Component* c : compRef_)
		c = nullptr;
	comp_.clear();
	for (Entity* e : children_)
		delete e;

	mngr_ = nullptr;
	if (parent_ != nullptr) {
		parent_->removeChild(this);
		parent_ = nullptr;
	}
}

void Entity::addComponent(nlohmann::json& args)
{
	std::string tag = args["type"];

	// Si la entidad no tiene el componente
	if (!hasComponent(tag))
	{
		// Miramos si esta en el json
		Component* c(FactoryCreator::getInstance()->getComponentFromJson(tag, args));
		if (c == nullptr)
			return;

		// Si esta lo metemos lo a�adimos a la entidad
		comp_.insert({ tag, c });
		compRef_.push_back(c);
		c->setEntity(this);
	}
	// Si ya existe 
	else
	{
		throw "Componente " + tag + " duplicado para la entidad " + name_;
	}
}

bool Entity::hasComponent(std::string name) {
	return comp_.find(name) != comp_.end();
}

void Entity::removeComponent(std::string name) {
	if (hasComponent(name)) {
		for (Component* c : compRef_)
			if (c->getName() == name) delete c;
		comp_.erase(name);
	}
}

void Entity::removeComponent() {
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

void Entity::start()
{
	std::size_t n = compRef_.size();
	for (auto i = 0u; i < n; i++) {
		if (compRef_[i]->isActive())
			compRef_[i]->start();
	}
}

void Entity::update() {
	std::size_t n = compRef_.size();
	for (auto i = 0u; i < n; i++) {
		if (compRef_[i]->isActive())
			compRef_[i]->update();
	}
}

void Entity::render() {
	std::size_t n = compRef_.size();
	for (auto i = 0u; i < n; i++) {
		if (compRef_[i]->isActive())
			compRef_[i]->render();
	}
}
