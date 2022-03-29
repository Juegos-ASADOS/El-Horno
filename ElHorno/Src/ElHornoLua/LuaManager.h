#pragma once
#ifndef _EL_HORNO_BULLET_LUA_MANAGER_H
#define _EL_HORNO_BULLET_LUA_MANAGER_H

#include <string>

class lua_State;
namespace luabridge {
    class LuaRef;
}

class Example {
public:
    Example(const std::string& name) : m_name(name) {}

    std::string getName() const;

    void printName();

private:
    std::string m_name;
};

class LuaManager {
public:
    static LuaManager* getInstance();
    static bool setupInstance();
    static void erase();

	void init();
    void report_errors(int status);
    void reedLuaScript(const std::string& path);

    template<typename T>
    void pushToLua(T var, std::string name);
    luabridge::LuaRef getFromLua(std::string name);
private:

    LuaManager() {};
    ~LuaManager();

    void exposeEntity();

    static LuaManager* instance;

    lua_State* luaState;
};

#endif _EL_HORNO_BULLET_LUA_MANAGER_H
