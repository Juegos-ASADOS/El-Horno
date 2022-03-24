#pragma once
#ifndef _EL_HORNO_BULLET_LUA_MANAGER_H
#define _EL_HORNO_BULLET_LUA_MANAGER_H

#include <string>

class lua_State;

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
private:

    LuaManager() {};
    ~LuaManager();

    void exposeEntity();
    void exposeComponents();

    static LuaManager* instance;

    lua_State* luaState;
};

#endif _EL_HORNO_BULLET_LUA_MANAGER_H