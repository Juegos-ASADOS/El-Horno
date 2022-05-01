#pragma once
#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <array>
#include <map>
#include <string>
#include <bitset>

#include "FactoryCreator.h"

namespace El_Horno {
	class Scene;
	class Component;

	class _declspec(dllexport) Entity
	{
	private:
		std::string name_;
		bool active_;

		Scene* scene_;

		std::map<std::string, Component*> comp_;
		std::vector<Component*> compRef_;
		std::string group_;

		Entity* parent_;
		std::vector<Entity*> children_;
	public:
		Entity(std::string n, Scene* m, Entity* p = nullptr);
		Entity(Scene* m) : name_(""), scene_(m), parent_(nullptr), compRef_(), comp_(), active_(true) {};
		~Entity();

		void awake();
		void start();
		void preUpdate();
		void update();
		void render();

		//Métodos para añadir/quitar/comprobar sobre los componentes de la entidad
		template<typename T, typename ...Ts>
		void addComponent(const std::string& type, Ts &&...args)
		{
			// Si la entidad no tiene el componente
			if (!hasComponent(type))
			{
				// Miramos si existe el componente
				T* c(FactoryCreator::getInstance()->getComponent<T>(type, args...));
				if (c == nullptr)
					return;

				// Si esta lo metemos lo asociamos a la entidad
				comp_.insert({ type, c });
				compRef_.push_back(c);
				c->setEntity(this);
			}
			// Si ya existe 
			else
			{
				throw "Componente " + type + " duplicado para la entidad " + name_;
			}
		}

		void addComponent(std::string name, std::vector<pair<string, string>> parameters);

		bool hasComponent(std::string name) const;

		template <typename T>
		inline T* getComponent(std::string name) {
			auto it = comp_.find(name);
			if (it == comp_.end())
				return nullptr;
			return static_cast<T*>(it->second);
		}

		std::vector<Component*> getComponents() { return compRef_; };

		void removeComponent(std::string name);
		void removeComponents();

		//Get/Set entidad padres
		inline Entity* getParent() { return parent_; };
		inline void setParent(Entity* p); 

		//Get/Set de los hijos
		Entity* getChild(std::string name);
		void addChild(Entity* c);
		inline int getChildCount() { return children_.size(); };

		void removeChild(Entity* e);

		inline std::vector<Entity*> getChildren() { return children_; };

		//DEVOLVER LISTA DE HIJOS CON T COMPONENTE - Decidiremos si es necesario
		template<typename T>
		std::vector<Entity*> getChildrenWithComponent();

		//Get/Set del bool active
		inline bool isActive() { return active_; };
		void setActive(bool act);
		void changeVisibility(bool vis);

		//Get/Set del nombre de la entidad
		inline std::string getName() { return name_; };
		inline Scene* getScene() { return scene_; };

		inline void setGroup(const std::string& g) { group_ = g; };
		inline std::string getGroup() { return group_; };

		bool dontDestroyOnLoad = false;
	};
}
#endif _ENTITY_H