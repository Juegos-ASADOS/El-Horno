#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include <string>
#include "json.hpp"

namespace El_Horno {
class Entity;

	class _declspec(dllexport) Scene
	{
	public:
		Scene();
		~Scene();

		void setupScene(nlohmann::json& j) {};
		void setupProcess(nlohmann::json& j) {};

		Entity* getEntity(const std::string& name, const std::string& layer = "");

		Entity* addEntity(const std::string& name, const std::string& layer, Entity* parent = nullptr, const std::string& group = "default");

		bool deleteEntity(const std::string& name);
		void deleteInstances();

		void start();
		void preUpdate();
		void update();
		virtual void init() {};

		inline std::string getName() const { return name_; };

	protected:
		std::map<std::string, std::vector<Entity*>> entities_;
		std::map<std::string, std::vector<Entity*>> entitiesGroups_;
		std::vector<std::pair<std::string, Entity*>> entitiesToDestroy_;

		std::string name_;
		bool sceneLoaded_ = false;
		int addedEntitiesCounter_ = 0;

		//Buscar entidades por tag? , Eliminar/crear entidades e instancias, Crear en la entidad physicsUpdate,pausedUpdates etc...
	};
}
#endif _SCENE_H