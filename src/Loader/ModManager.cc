#include "Loader/ModManager.h"
#include "API/Event/Event.h"
#include "Entry.h"
#include "Loader/Mod.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "Utils/Using.h"


#include <ll/api/Expected.h>
#include <ll/api/mod/Mod.h>

#include <algorithm>
#include <filesystem>
#include <memory>


constexpr auto ModManagerName = "KomomoJS";

namespace Komomo {

KomomoModManager::KomomoModManager() : ll::mod::ModManager(ModManagerName) {}
KomomoModManager::~KomomoModManager() = default;

ll::Expected<> KomomoModManager::load(ll::mod::Manifest manifest) {
    auto& manager = NodeManager::getInstance();
    auto  wrapper = manager.newScriptEngine();

    EngineID id;
    {
        EngineScope enter(wrapper->mEngine);
        id = ENGINE_DATA()->mID;
    }

    auto file = fs::current_path() / ll::mod::getModsRoot() / manifest.name / manifest.entry;
    try {
        {
            EngineScope enter(wrapper->mEngine);
            ENGINE_DATA()->mFileName = file.filename().string();
        }

        fs::path package = file.parent_path() / "package.json";
        if (NodeManager::packageHasDependency(package) && !fs::exists(file.parent_path() / "node_modules")) {
            Entry::getInstance().getSelf().getLogger().info("Installing dependencies for mod: {}", file.filename());
            EngineScope enter(wrapper->mEngine);
            manager.NpmInstall(file.parent_path().string());
        }


        auto mod = std::make_shared<KomomoMod>(manifest);
        {
            EngineScope enter(wrapper->mEngine);
            auto        data = ENGINE_DATA();
            data->mMod       = mod;
            mod->id          = data->mID;
        }

        if (!NodeManager::loadFile(wrapper, file, NodeManager::packageIsEsm(package))) {
            Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
            manager.destroyEngine(wrapper->mID);
            return ll::makeStringError("Failed to load mod");
        }

        {
            auto        engine_ = wrapper->mEngine;
            EngineScope enter(engine_);
            engine_->set("onLoad", Function::newFunction([mod](const Arguments& args) {
                             CheckArgsCount(args, 1);
                             CheckArgType(args[0], ValueKind::kFunction);
                             try {
                                 auto func = args[0].asFunction();
                                 script::Global<Function> callbackFunc(func);
                                 mod->onLoadCallbacks.push_back([engine_{EngineScope::currentEngine()},
                                                                 callback{std::move(callbackFunc)}]() {
                                     EngineScope enter(engine_);
                                     try {
                                         callback.get().call();
                                     }
                                     CatchNotReturn;
                                 });
                             }
                             Catch;
                             return Local<Value>();
                         }));

            engine_->set("onEnable", Function::newFunction([mod](const Arguments& args) {
                             CheckArgsCount(args, 1);
                             CheckArgType(args[0], ValueKind::kFunction);
                             try {
                                 auto func = args[0].asFunction();
                                 script::Global<Function> callbackFunc(func);
                                 mod->onEnableCallbacks.push_back([engine_{EngineScope::currentEngine()},
                                                                 callback{std::move(callbackFunc)}]() {
                                     EngineScope enter(engine_);
                                     try {
                                         callback.get().call();
                                     }
                                     CatchNotReturn;
                                 });
                             }
                             Catch;
                             return Local<Value>();
                         }));

            engine_->set("onDisable", Function::newFunction([mod](const Arguments& args) {
                             CheckArgsCount(args, 1);
                             CheckArgType(args[0], ValueKind::kFunction);
                             try {
                                 auto func = args[0].asFunction();
                                 script::Global<Function> callbackFunc(func);
                                 mod->onDisableCallbacks.push_back([engine_{EngineScope::currentEngine()},
                                                                 callback{std::move(callbackFunc)}]() {
                                     EngineScope enter(engine_);
                                     try {
                                         callback.get().call();
                                     }
                                     CatchNotReturn;
                                 });
                             }
                             Catch;
                             return Local<Value>();
                         }));

            engine_->set("onUnload", Function::newFunction([mod](const Arguments& args) {
                             CheckArgsCount(args, 1);
                             CheckArgType(args[0], ValueKind::kFunction);
                             try {
                                 auto func = args[0].asFunction();
                                 script::Global<Function> callbackFunc(func);
                                 mod->onUnloadCallbacks.push_back([engine_{EngineScope::currentEngine()},
                                                                 callback{std::move(callbackFunc)}]() {
                                     EngineScope enter(engine_);
                                     try {
                                         callback.get().call();
                                     }
                                     CatchNotReturn;
                                 });
                             }
                             Catch;
                             return Local<Value>();
                         }));
        }


        mod->onLoad([mod_{std::weak_ptr{mod}}](ll::mod::Mod& mod) {
            auto callbacks = mod_.lock()->onLoadCallbacks;
            std::for_each(callbacks.begin(), callbacks.end(), [](std::function<void()> func) { std::invoke(func); });
            return true;
        });
        mod->onEnable([mod_{std::weak_ptr{mod}}](ll::mod::Mod& mod) {
            auto callbacks = mod_.lock()->onEnableCallbacks;
            std::for_each(callbacks.begin(), callbacks.end(), [](std::function<void()> func) { std::invoke(func); });
            return true;
        });
        mod->onDisable([mod_{std::weak_ptr{mod}}](ll::mod::Mod& mod) {
            auto callbacks = mod_.lock()->onDisableCallbacks;
            std::for_each(callbacks.begin(), callbacks.end(), [](std::function<void()> func) { std::invoke(func); });
            return true;
        });
        mod->onUnload([mod_{std::weak_ptr{mod}}](ll::mod::Mod& mod) {
            auto callbacks = mod_.lock()->onUnloadCallbacks;
            std::for_each(callbacks.begin(), callbacks.end(), [](std::function<void()> func) { std::invoke(func); });
            return true;
        });

        return mod->onLoad().transform([&, this] { addMod(manifest.name, mod); });
    } catch (script::Exception& e) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
        // Entry::getInstance().getSelf().getLogger().error("JavaScript error: {}", e.what());
        // Entry::getInstance().getSelf().getLogger().error("Stack trace: {}", e.stacktrace());
    } catch (std::exception& e) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
        Entry::getInstance().getSelf().getLogger().error("Unknown error: {}", e.what());
    } catch (...) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
        Entry::getInstance().getSelf().getLogger().error("Unknown error");
    }

    manager.destroyEngine(id);
    return {};
}

// TODO: 实现 unload 方法
ll::Expected<> KomomoModManager::unload(std::string_view name) {
    try {

        auto mod = std::static_pointer_cast<KomomoMod>(getMod(name));

        auto wrapper = NodeManager::getInstance().getEngine(mod->id);

        EventBusClass::removeModAllListeners(mod->getName());

        // wrapper->mEngine->getData().reset();

        NodeManager::getInstance().destroyEngine(mod->id);

        eraseMod(name);

        return {};
    } catch (const std::exception& e) {
        return ll::makeStringError("Failed to unload mod {0}: {1}");
    }
}
} // namespace Komomo
