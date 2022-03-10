#pragma once
#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <array>
#include <map>
#include <string>
#include <bitset>

#include "json.hpp"

class Component;
class Manager;

class Entity
{
private:
	std::string name_;
	bool active_;
	
	Manager* mngr_;

	std::map<std::string, Component*> comp_;
	std::vector<Component*> compRef_;
	//bitset<ecs::maxGroup> groups_;
	
	Entity* parent_;
	std::vector<Entity*> children_;
public:
	Entity(std::string n, Manager* m, Entity* p = nullptr);
	Entity(Manager* m) : name_(""), mngr_(m), parent_(nullptr), compRef_(), comp_(), active_(true) {};
	~Entity();

	void update();
	void render();

	//Métodos para añadir/quitar/comprobar sobre los compoenentes de la entidad
	void addComponent(nlohmann::json& args);

	bool hasComponent(std::string name);
	template <typename T>
	T* getComponent(std::string name);
	void removeComponent(std::string name);
	void removeComponent();

	//Get/Set entidad padres
	inline Entity* getParent() { return parent_; };
	inline void setParent(Entity* p) { parent_ = p; };

	//Get/Set de los hijos
	Entity* getChild(std::string name);
	void addChild(Entity* c);
	inline int getChildCount() { return children_.size(); };
	void removeChild(Entity* e);
	//Este no sabemos aun
	inline std::vector<Entity*> getChildren() { return children_; };
	//Decidiremos
	//DEVOLVER LISTA DE HIJOS CON T COMPONENTE
	template<typename T>
	std::vector<Entity*> getChildrenWithComponent();

	//Get/Set del bool active
	inline bool isActive() { return active_; };
	inline void setActive(bool act) { active_ = act; };

	//Get/Set del nombre de la entidad
	inline std::string getName() { return name_; };
	inline Manager* getMngr() { return mngr_; };


	bool dontDestroyOnLoad = false;

	//GROUPS, layers, transform
};

#endif _ENTITY_H