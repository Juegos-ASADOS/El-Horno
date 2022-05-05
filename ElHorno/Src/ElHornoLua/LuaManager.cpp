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
#include "SceneManager.h"
#include "AudioManager.h"
#include "ElHornoBase.h"
#include "GraphicsManager.h"
#include "Scene.h"
#include "CheckML.h"


#include "UIManager.h"

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

        exposeFunctions();
        readLuaScript("shop");
        readLuaScript("prefabs");
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

    void LuaManager::readLuaScript(const std::string& path)
    {
        std::string s = SCRIPTS_PATH + path + FILE_EXTENSION;
        // load some code from Lua file
        int scriptLoadStatus = luaL_dofile(luaState, s.c_str());

        // define error reporter for any Lua error
        report_errors(scriptLoadStatus);
    }

    void LuaManager::pushString(std::string var, std::string name)
    {
        lua_pushstring(luaState, var.c_str());
        lua_setglobal(luaState, name.c_str());
    }

    void LuaManager::pushBool(bool var, std::string name)
    {
        lua_pushboolean(luaState, (int)var);
        lua_setglobal(luaState, name.c_str());
    }

    void LuaManager::pushNumber(float var, std::string name)
    {
        lua_pushnumber(luaState, var);
        lua_setglobal(luaState, name.c_str());
    }

    luabridge::LuaRef LuaManager::getFromLua(std::string name)
    {
        return luabridge::getGlobal(luaState, name.c_str());

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

    void LuaManager::loadScene()
    {
        Scene* s = SceneManager::getInstance()->getCurrentScene();
        readLuaScript(s->getName());

        luabridge::LuaRef allEnts = getFromLua("entities");
        int numEnts = allEnts.length();

        for (int i = 1; i <= numEnts; i++) {
            luabridge::LuaRef entity = getFromLua(allEnts[i]);
            Entity* ent = s->getEntity(allEnts[i]);
            if (ent == nullptr) {
                ent = s->addEntity(allEnts[i], "prueba");
                ent->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));
            }
            setParams(entity, ent, s);
        }
    }

    Entity* LuaManager::loadPrefab(std::string name)
    {
        Scene* s = SceneManager::getInstance()->getCurrentScene();

        luabridge::LuaRef entity = getFromLua(name);
        Entity* ent = s->addEntity(name, "prueba");
        ent->addComponent<Transform>("transform", HornoVector3(0, 0, 0), HornoVector3(0, 0, 0), HornoVector3(0, 0, 0));

        setParams(entity, ent, s);
        ent->awake();
        ent->start();
        return ent;
    }

    void LuaManager::setParams(luabridge::LuaRef entity, Entity* ent, Scene* s)
    {
        lua_pushnil(entity);
        while (lua_next(entity, 0) != 0) {
            std::string compName = lua_tostring(entity, -2);

            std::string key;

            luabridge::LuaRef component = entity[compName];
            lua_pushnil(component);

            if (compName == "dontDestroyOnLoad") {
                ent->setDontDestryOnLoad(true);
                lua_pop(component, 1);
                continue;
            }

            std::vector<std::pair<std::string, std::string>> parameters;

            while (lua_next(component, 0) != 0) {
                std::string key = lua_tostring(entity, -2);
                std::string val = lua_tostring(entity, -1);

                if (compName == "parent") {
                    s->getEntity(val, "prueba")->addChild(ent);
                    lua_pop(component, 1);
                    continue;
                }

                parameters.push_back({ key, val });
                lua_pop(component, 1);
            }

            if (compName != "parent") {
                ent->addComponent(compName, parameters);
            }
            lua_pop(entity, 1);
        }
    }

    template<typename T>
    void LuaManager::pushToLua(T* var, std::string name) {
        luabridge::push(luaState, var);
        lua_setglobal(luaState, name.c_str());
    }

    LuaManager::~LuaManager()
    {
        lua_close(luaState);
    }

    void LuaManager::exposeFunctions()
    {
        luabridge::getGlobalNamespace(luaState)
            .beginClass<SceneManager>("SceneManager")
            .addStaticFunction("getSceneManager", &SceneManager::getInstance)
            .addFunction("changeScene", (&SceneManager::changeScene))
            .addFunction("nextScene", (&SceneManager::nextScene))
            .addFunction("getCurrentScene", (&SceneManager::getCurrentScene))
            .endClass();

        luabridge::getGlobalNamespace(luaState)
            .beginClass<AudioManager>("AudioManager")
            .addStaticFunction("getAudioManager", &AudioManager::getInstance)
            .addFunction("upMusicVolume", (&AudioManager::upMusicVolume))
            .addFunction("downMusicVolume", (&AudioManager::downMusicVolume))
            .addFunction("upFxVolume", (&AudioManager::upFxVolume))
            .addFunction("downFxVolume", (&AudioManager::downFxVolume))
            .endClass();

        luabridge::getGlobalNamespace(luaState)
            .beginClass<GraphicsManager>("GraphicsManager")
            .addStaticFunction("getGraphicsManager", &GraphicsManager::getInstance)
            .addFunction("upResolution", (&GraphicsManager::setResolutionUp))
            .addFunction("downResolution", (&GraphicsManager::setResolutionDown))
            .endClass();

        luabridge::getGlobalNamespace(luaState)
            .beginClass<ElHornoBase>("ElHornoBase")
            .addStaticFunction("getElHornoBase", &ElHornoBase::getInstance)
            .addFunction("pause", (&ElHornoBase::pause))
            .addFunction("exit", (&ElHornoBase::exit))
            .endClass();

        //vamos con el uiManager y todo lo que necesitamos exposear para manejo de interfaces y menu
        luabridge::getGlobalNamespace(luaState)
            .beginClass<UIManager>("UIManager")
            .addStaticFunction("getUIManager", &UIManager::getInstance)
            .addFunction("setLayoutVisibility", (&UIManager::setLayoutVisibility))
            .addFunction("addLayout", (&UIManager::addLayout))
            .addFunction("removeLayout", (&UIManager::removeLayout))
            .addFunction("removeLayouts", (&UIManager::removeLayouts))
            .addFunction("setLayoutScale", (&UIManager::setLayoutScale))
            .addFunction("subscribeLayoutChildEvent", (&UIManager::subscribeLayoutChildEvent))
            .addFunction("subscribeChildEvent", (&UIManager::subscribeChildEvent))
            .addFunction("addImageFile", (&UIManager::addImageFile))
            .addFunction("addWidgetToLayout", (&UIManager::addWidgetToLayout))
            .addFunction("removeWidgetFromLayout", (&UIManager::removeWidgetFromLayout))
            .addFunction("setChildProperty", (&UIManager::setChildProperty))
            .addFunction("getLayout", (&UIManager::getLayout))
            .endClass();


    }

    void LuaManager::callLuaFunction(std::string name)
    {
        luabridge::LuaRef s = getFromLua(name);
        s();
    }

    //void LuaManager::callLuaFunction(std::string name, int i)
    //{
    //    luabridge::LuaRef s = getFromLua(name);
    //}

    template <class... Args>
    void LuaManager::callLuaFunction(std::string name, Args&&... args)
    {
        luabridge::LuaRef s = getFromLua(name);
        s(args...);
    }

    template<typename T>
    void LuaManager::pushCFunct(std::string classTypename, std::string name, void(*function)())
    {
        luabridge::getGlobalNamespace(luaState)
            .beginClass<T>(classTypename)
            .addFunction(name, &(T::function))
            .endClass();
    }
}

// create a global variable (an instance_ of a Greeter class) in Lua scope
//auto globalGreeter = std::make_unique<Example>("noname");
//std::error_code e = std::error_code();
//luabridge::push(luaState, globalGreeter.get(), e);
//lua_setglobal(luaState, "example");