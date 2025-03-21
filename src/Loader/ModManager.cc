#include "Loader/ModManager.h"
#include "API/Event/Event.h"
#include "Entry.h"
#include "Loader/Mod.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"
#include "Utils/Using.h"


#include <ll/api/Expected.h>
#include <ll/api/mod/Mod.h>

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
            // manager.NpmInstall(file.parent_path().string());
        }


        auto mod = std::make_shared<KomomoMod>(manifest);
        {
            EngineScope enter(wrapper->mEngine);
            auto        data = ENGINE_DATA();
            data->mMod       = mod;
            mod->id          = data->mID;
        }

        if (!NodeManager::loadFile(wrapper, file)) {
            Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
            manager.destroyEngine(wrapper->mID);
            return ll::makeStringError("Failed to load mod");
        }

        mod->onLoad([id](ll::mod::Mod &) {
            auto engineWrapper = NodeManager::getInstance().getEngine(id);
            auto engine = engineWrapper->mEngine;
            try {
                EngineScope enter(engine);
                ENGINE_DATA()->onLoad.get().call();
            } CatchNotReturn;
            return true;
        });


        mod->onEnable([id](ll::mod::Mod &mod) {
            auto engineWrapper = NodeManager::getInstance().getEngine(id);
            auto engine = engineWrapper->mEngine;
            try {
                EngineScope enter(engine);
                ENGINE_DATA()->onEnable.get().call();
            } CatchNotReturn;
            return true;
            return true;
        });
        mod->onDisable([id](ll::mod::Mod &mod) {
            auto engineWrapper = NodeManager::getInstance().getEngine(id);
            auto engine = engineWrapper->mEngine;
            try {
                EngineScope enter(engine);
                ENGINE_DATA()->onDisable.get().call();
            } CatchNotReturn;
            return true;
        });
        mod->onUnload([id](ll::mod::Mod &mod) {
            auto engineWrapper = NodeManager::getInstance().getEngine(id);
            auto engine = engineWrapper->mEngine;
            try {
                EngineScope enter(engine);
                ENGINE_DATA()->onUnload.get().call();
            } CatchNotReturn;
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