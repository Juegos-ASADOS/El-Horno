#pragma once
#include <vector>
#include <array>
#include <string>

using namespace std;

class Component;
class Entity
{
private:
	string name_;
	bool active_;
	vector<Component*> comp_;
	array<Component*, 1> compRef_;

	Entity* parent_;
	vector<Entity*> children_;
public:
	Entity();
	~Entity();

	template<typename T, typename ...Ts>
	T* addComponent(Ts &&... args);

	template<typename T>
	bool hasComponent();
	
	template<typename T>
	T* getComponent();

	void removeComponent();

	inline Entity* getParent() { return parent_; };
	inline void setParent(Entity* p) { parent_ = p; };

	//Este no sabemos aun
	inline vector<Entity*> getChildren() { return children_; };		

	Entity* getChild(string name);
	inline int getChildCount() { return children_.size(); };

	//Decidiremos
	//DEVOLVER LISTA DE HIJOS CON T COMPONENTE
	template<typename T>
	vector<Entity*> getChildrenWithComponent();

	//GROUPS, getName, layers, transform, constructoras, update, init

	inline void setActive(bool act) { active_ = act; };
};

