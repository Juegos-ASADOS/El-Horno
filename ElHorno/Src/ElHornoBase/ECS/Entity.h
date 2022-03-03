#pragma once
#include <vector>
#include <array>
#include <string>
#include <bitset>

using namespace std;

class Component;
class Manager;

class Entity
{
private:
	string name_;
	bool active_;
	vector<Component*> comp_;
	
	Manager* mngr_;
	array<Component*, 1> compRef_;			//CAMBIAR EL 1 POR CANTIDAD DE COMPONENTES
	//bitset<ecs::maxGroup> groups_;
	
	Entity* parent_;
	vector<Entity*> children_;
public:
	Entity(string n, Manager* m, Entity* p = nullptr);
	Entity(Manager* m) : name_(""), mngr_(m), parent_(nullptr), compRef_(), active_(true) {};
	~Entity();

	void update();
	void render();

	//Métodos para añadir/quitar/comprobar sobre los compoenentes de la entidad
	template<typename T, typename ...Ts>
	T* addComponent(Ts &&... args);

	template<typename T>
	bool hasComponent();
	
	template<typename T>
	T* getComponent();

	template<typename T>
	void removeComponent();

	//Get/Set entidad padres
	inline Entity* getParent() { return parent_; };
	inline void setParent(Entity* p) { parent_ = p; };

	//Get/Set de los hijos
	Entity* getChild(string name);
	void addChild(Entity* c);
	inline int getChildCount() { return children_.size(); };
	void removeChild(Entity* e);
	//Este no sabemos aun
	inline vector<Entity*> getChildren() { return children_; };		
	//Decidiremos
	//DEVOLVER LISTA DE HIJOS CON T COMPONENTE
	template<typename T>
	vector<Entity*> getChildrenWithComponent();

	//Get/Set del bool active
	inline bool isActive() { return active_; };
	inline void setActive(bool act) { active_ = act; };

	//Get/Set del nombre de la entidad
	inline string getName() { return name_; };
	inline Manager* getMngr() { return mngr_; };

	//GROUPS, layers, transform
};