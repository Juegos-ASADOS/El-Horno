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

    exposeComponents();
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
        //.addFunction("addComponent", &())
        .addFunction("setParent", &(Entity::setParent))
        .addFunction("addChild", &(Entity::addChild))
        .addFunction("setActive", &(Entity::setActive))
        .endClass();
}

void LuaManager::exposeComponents()
{
    luabridge::getGlobalNamespace(luaState)
        .beginClass<Transform>("Transform")
        .addConstructor<void(*) (Ogre::Vector3 pos, Ogre::Vector3 rot, Ogre::Vector3 scal)>()
        .addFunction("setPosition", &(Transform::setPosition))
        .addFunction("setScale", &(Transform::setScale))
        .addFunction("setRotation", &(Transform::setRotation))
        .addFunction("lookAt", &(Transform::lookAt))
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<ParticleSystem>("ParticleSystem")
        .addConstructor<void(*) (const std::string& name,const std::string& temp, float timelim, bool destroyTL)>()
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<Mesh>("Mesh")
        .addConstructor<void(*) (std::string name, bool castShadow, bool isAnimated)>()
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<CameraComponent>("CameraComponent")
        .addConstructor<void(*) (Ogre::Vector3 pos, Ogre::Vector3 lookAt, Ogre::ColourValue color, int nearClDis, int farClDis)>()
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<AudioComponent>("AudioComponent")
        .addConstructor<void(*) ()>()
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<AudioListenerComponent>("AudioListenerComponent")
        .addConstructor<void(*) ()>()
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

// create a global variable (an instance of a Greeter class) in Lua scope
//auto globalGreeter = std::make_unique<Example>("noname");
//std::error_code e = std::error_code();
//luabridge::push(luaState, globalGreeter.get(), e);
//lua_setglobal(luaState, "example");