#include "ElHornoLua.h"

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "LuaBridge.h"

#include <memory>
#include <iostream>

ElHornoLua* ElHornoLua::instance;

ElHornoLua* ElHornoLua::getInstance()
{
    if (instance == 0)
        return nullptr;

    return instance;
}

bool ElHornoLua::setupInstance()
{
    if (instance == 0) {
        instance = new ElHornoLua();
        return true;
    }
    return false;
}

void ElHornoLua::erase()
{
    delete instance;
}

void ElHornoLua::init()
{
    // create a Lua state
    lua_State* luaState = luaL_newstate();

    // load standard libs
    luaL_openlibs(luaState);

    // expose the Example class to the Lua scripts
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Example>("Example")
        .addConstructor<void(*) (const std::string&)>()
        .addFunction("getName", &(Example::getName))
        .addFunction("printName", &(Example::printName))
        .endClass();

    // create a global variable (an instance of a Greeter class) in Lua scope
    auto globalGreeter = std::make_unique<Example>("noname");
    std::error_code e = std::error_code();
    luabridge::push(luaState, globalGreeter.get(), e);
    lua_setglobal(luaState, "example");

    // load some code from Lua file
    int scriptLoadStatus = luaL_dofile(luaState, "C:/Users/almuf/OneDrive/Documentos/Repos/El-Horno/ElHorno/Src/ElHornoLua/sample.lua");

    // define error reporter for any Lua error
    report_errors(luaState, scriptLoadStatus);
}

void ElHornoLua::report_errors(lua_State* luaState, int status)
{
    if (status == 0) {
        return;
    }

    std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

    // remove error message from Lua state
    lua_pop(luaState, 1);
}

std::string Example::getName() const
{
	return m_name;
}

void Example::printName()
{
	std::cout << "[C++ CODE] Hello, my name is " << m_name << "!" << "\n";
}
