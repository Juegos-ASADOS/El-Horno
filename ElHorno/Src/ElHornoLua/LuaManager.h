#pragma once
#ifndef _EL_HORNO_BULLET_LUA_MANAGER_H
#define _EL_HORNO_BULLET_LUA_MANAGER_H

#define SCRIPTS_PATH "Assets/Scripts/"
#define FILE_EXTENSION ".lua"

#include <string>

namespace El_Horno {
	class Entity;
	class Scene;
}

class lua_State;
namespace luabridge {
	class LuaRef;
	class LuaResult;
}
typedef int (*lua_CFunction) (lua_State* L);

namespace El_Horno {
	class _declspec(dllexport) LuaManager {
	public:
		static LuaManager* getInstance();
		static bool setupInstance();
		static void erase();

		void init();
		void report_errors(int status);
		void readLuaScript(const std::string& path);

		template<typename T>
		void pushToLua(T* var, std::string name);

		void pushString(std::string var, std::string name);
		void pushBool(bool var, std::string name);
		void pushNumber(float var, std::string name);

		luabridge::LuaRef getFromLua(std::string name);
		lua_State* getLuaState();
		void exposeFunct(std::string name, lua_CFunction(*func)(lua_State* L));
		int luaGetTop(lua_State* L);
		void loadScene();
		Entity* loadPrefab(std::string name, bool handAt);
		void setParams(luabridge::LuaRef entity, Entity* ent, Scene* s, bool handAt);
		void callLuaFunction(std::string name);
		//void callLuaFunction(std::string name, int i);

		template<class ...Args>
		void callLuaFunction(std::string name, Args && ...);

		template <typename T>
		void pushCFunct(std::string classTypename, std::string name, void (*function)());
	private:

		LuaManager() {};
		~LuaManager();

		void exposeFunctions();

		static LuaManager* instance_;

		lua_State* luaState;
	};
}
#endif _EL_HORNO_BULLET_LUA_MANAGER_H
