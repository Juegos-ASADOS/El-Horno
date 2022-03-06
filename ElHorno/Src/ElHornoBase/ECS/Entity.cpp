#include "Entity.h"
#include "Component.h"
#include "FactoryCreator.h"

Entity::Entity(string n, Manager* m, Entity* p) : name_(n), mngr_(m), active_(true), comp_(), compRef_() {
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

void Entity::addComponent(json& args) {
	string tag = args["type"];

	//if it doesn't exist, it's created
	if (!hasComponent(tag)) {
		Component* c(FactoryCreator::getInstance()->getComponentFromJson(tag, args));
		if (c == nullptr)
			return;

		comp_.insert({ tag, c });
		compRef_.push_back(c);
		c->setEntity(this);
	}
	//if it already exists, it's being redefined (ideally only used with prefabs)
	else {
		throw "Componente " + tag + " duplicado para la entidad " + name_;
	}
}

bool Entity::hasComponent(string name) {
	return comp_.find(name) != comp_.end();
}

Component* Entity::getComponent(string name) {
	auto it = comp_.find(name);
	if (it == comp_.end())
		throw "No se ha encontrado el componente " + name + " en la entidad " + name_;
	return it->second;
}

void Entity::removeComponent(string name) {
	if (hasComponent(name)) {
		for (Component* c : compRef_)
			if (c->getName() == name) delete c;
		comp_.erase(name);
	}
}

Entity* Entity::getChild(string name) {
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
