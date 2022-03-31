#include "LuaManager.h"

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include "LuaBridge.h"

#include <memory>
#include <iostream>

#include "Entity.h"
#include "Transform.h"
#include "ParticleSystem.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include "AudioComponent.h"
#include "AudioListenerComponent.h"
#include "CheckML.h"

namespace El_Horno {

LuaManager* LuaManager::instance;

LuaManager* LuaManager::getInstance()
{
    if (instance == 0)
        return nullptr;

    return instance;
}

bool LuaManager::setupInstance()
{
    if (instance == 0) {
        instance = new LuaManager();
        return true;
    }
    return false;
}

void LuaManager::erase()
{  
    delete instance;
}

void LuaManager::init()
{
    // create a Lua state
   luaState = luaL_newstate();

    // load standard libs
    luaL_openlibs(luaState);

    luabridge::getGlobalNamespace(luaState)
        .beginClass<Example>("Example")
        .addConstructor<void(*) (const std::string& name)>()
        .addFunction("printName", &(Example::printName))
        .endClass();

    exposeEntity();
}

void LuaManager::report_errors(int status)
{
    if (status == 0) {
        return;
    }

    std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

    // remove error message from Lua state
    lua_pop(luaState, 1);
}

void LuaManager::reedLuaScript(const std::string& path)
{
    // load some code from Lua file
    int scriptLoadStatus = luaL_dofile(luaState, path.c_str());

    // define error reporter for any Lua error
    report_errors(scriptLoadStatus);
}

luabridge::LuaRef LuaManager::getFromLua(std::string name)
{
    std::string s = SCRIPTS_PATH + name + FILE_EXTENSION;
    return luabridge::getGlobal(luaState, s.c_str());
}

template<typename T>
void LuaManager::pushToLua(T var, std::string name) {
    luabridge::push(luaState, var);
    lua_setglobal(luaState, name.c_str());
}

LuaManager::~LuaManager()
{
    lua_close(luaState);
}

void LuaManager::exposeEntity()
{
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Entity>("Entity")
        .addConstructor<void(*) (std::string n, Scene* m, Entity* p)>()
        .addConstructor<void(*) (Scene* m)>()
        //.addFunction("addComponent", &(Entity::addComponent<>))
        .addFunction("setParent", &(Entity::setParent))
        .addFunction("addChild", &(Entity::addChild))
        .addFunction("setActive", &(Entity::setActive))
        .endClass();
}

std::string Example::getName() const
{
	return m_name;
}

void Example::printName()
{
	std::cout << "[C++ CODE] Hello, my name is " << m_name << "!" << "\n";
}
}
// create a global variable (an instance of a Greeter class) in Lua scope
//auto globalGreeter = std::make_unique<Example>("noname");
//std::error_code e = std::error_code();
//luabridge::push(luaState, globalGreeter.get(), e);
//lua_setglobal(luaState, "example");