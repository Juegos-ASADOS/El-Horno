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

    LuaManager* LuaManager::instance_;

    LuaManager* LuaManager::getInstance()
    {
        if (instance_ == 0)
            return nullptr;

        return instance_;
    }

    bool LuaManager::setupInstance()
    {
        if (instance_ == 0) {
            instance_ = new LuaManager();
            return true;
        }
        return false;
    }

    void LuaManager::erase()
    {
        delete instance_;
    }

    void LuaManager::init()
    {
        // create a Lua state
        luaState = luaL_newstate();

        // load standard libs
        luaL_openlibs(luaState);
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

    lua_State* LuaManager::getLuaState()
    {
        return luaState;
    }

    void LuaManager::exposeFunct(std::string name, lua_CFunction(*func)(lua_State* L))
    {
        lua_register(luaState, name.c_str(), func(luaState));
    }

    int LuaManager::luaGetTop(lua_State* L)
    {
        return lua_gettop(L);
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
}
// create a global variable (an instance_ of a Greeter class) in Lua scope
//auto globalGreeter = std::make_unique<Example>("noname");
//std::error_code e = std::error_code();
//luabridge::push(luaState, globalGreeter.get(), e);
//lua_setglobal(luaState, "example");