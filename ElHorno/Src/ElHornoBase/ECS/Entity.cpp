#include "Entity.h"
#include "Component.h"

Entity::Entity(string n, Manager* m, Entity* p) : name_(n), mngr_(m), compRef_(), active_(true) {
	parent_ = p;
	
	if (parent_ != nullptr) {
		parent_->addChild(this);
	}
}

Entity::~Entity(){
	for (Component* c : comp_)
		delete c;
	for (Entity* e : children_)
		delete e;

	mngr_ = nullptr;
	if (parent_ != nullptr) {
		parent_->removeChild(this);
		parent_ = nullptr;
	}
}

template<typename T, typename ...Ts>
T* Entity::addComponent(Ts && ...args){
	T* c = new T(std::forward<Ts>(args)...);
	c->setEntity(this);
	c->start();
	constexpr auto id = 0;// ecs::cmpIdx<T>;

	//Si se quieren componentes duplicados modificar aqui
	if (compRef_[id] != nullptr) {
		removeComponent<T>();
	}

	compRef_[id] = c;
	comp_.emplace_back(c);

	return c;
}

template<typename T>
bool Entity::hasComponent(){
	auto id = 0;// ecs::cmpIdx<T>;
	return compRef_[id] != nullptr;
}

template<typename T>
T* Entity::getComponent(){
	auto id = 0;// ecs::cmpIdx<T>;
	return static_cast<T*>(compRef_[id]);
}

template<typename T>
void Entity::removeComponent(){
	auto id = 0;// ecs::cmpIdx<T>;
	if (compRef_[id] != nullptr) {
		Component* old_cmp = compRef_[id];
		compRef_[id] = nullptr;
		comp_.erase(
			std::find_if( 
				comp_.begin(),
				comp_.end(),
				[old_cmp](const Component* c) { 
					return c == old_cmp;
				}));
		delete old_cmp;
	}
}

Entity* Entity::getChild(string name){
	for (Entity* e : children_)
		if (e->getName() == name) return e;

	return nullptr;
}

void Entity::addChild(Entity* c){
	children_.push_back(c);
}

void Entity::removeChild(Entity* e){
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
	std::size_t n = comp_.size();
	for (auto i = 0u; i < n; i++) {
		if (comp_[i]->isActive()) 
			comp_[i]->update();
	}
}

void Entity::render() {
	std::size_t n = comp_.size();
	for (auto i = 0u; i < n; i++) {
		if (comp_[i]->isActive()) 
			comp_[i]->render();
	}
}
