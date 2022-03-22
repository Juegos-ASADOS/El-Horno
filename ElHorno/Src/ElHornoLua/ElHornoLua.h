#pragma once
#ifndef _EL_HORNO_BULLET_EL_HORNO_LUA_H
#define _EL_HORNO_BULLET_EL_HORNO_LUA_H

#include <string>

class lua_State;

class Example {
public:
    Example(std::string name) : m_name(name) {}

    std::string getName() const;

    void printName();

private:
    std::string m_name;
};

class ElHornoLua {
public:
    static ElHornoLua* getInstance();
    static bool setupInstance();
    static void erase();

	void init();
    void report_errors(lua_State* luaState, int status);
private:
    static ElHornoLua* instance;
};

#endif _EL_HORNO_BULLET_EL_HORNO_LUA_H