#include "Loader/ModManager.h"
#include "API/APIHelper.h"
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
std::vector<std::string> KomomoModManager::getPluginFileFilters() const { return {".js"}; }


ll::Expected<> KomomoModManager::load(ll::mod::Manifest manifest) {

    auto& manager = NodeManager::getInstance();
    auto  wrapper = manager.newScriptEngine();

    EngineScope scope(wrapper->mEngine);
    auto        data = ENGINE_DATA();
    auto        file = fs::current_path() / ll::mod::getModsRoot() / manifest.name / manifest.entry;
    try {
        auto path = fs::path(file);

        data->mFileName = path.filename().string();

        fs::path package = path.parent_path() / "package.json";

        // 安装依赖
        if (NodeManager::packageHasDependency(package) && !fs::exists(path.parent_path() / "node_modules")) {
            Entry::getInstance().getSelf().getLogger().info("Installing dependencies for mod: {}", path.filename());
            manager.NpmInstall(path.parent_path().string());
        }


        // 创建插件实例
        auto mod   = std::make_shared<KomomoMod>(manifest);
        data->mMod = mod;

        mod->id = data->mID;

        if (!NodeManager::loadFile(wrapper, file, NodeManager::packageIsEsm(package))) {
            Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
            return ll::makeStringError("Failed to load mod");
        }

        mod->onLoad([data](ll::mod::Mod&) { return true; });
        mod->onEnable([data](ll::mod::Mod&) { return true; });
        mod->onDisable([data](ll::mod::Mod& mod) { return true; });
        mod->onUnload([data](ll::mod::Mod& mod) { return true; });

        return mod->onLoad().transform([&, this] { addMod(manifest.name, mod); });

    } catch (script::Exception& e) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance().getSelf().getLogger().error("JavaScript error: {}", e.what());
        Entry::getInstance().getSelf().getLogger().error("Stack trace: {}", e.stacktrace());
    } catch (std::exception& e) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance().getSelf().getLogger().error("Unknown error: {}", e.what());
    } catch (...) {
        Entry::getInstance().getSelf().getLogger().error("Failed to load plugin: {}", file);
        Entry::getInstance().getSelf().getLogger().error("Unknown error");
    }

    manager.destroyEngine(data->mID);
    return {};
}

// TODO: 实现 unload 方法
ll::Expected<> KomomoModManager::unload(std::string_view name) {
    try {

        auto mod = std::static_pointer_cast<KomomoMod>(getMod(name));

        auto& scriptEngine = *NodeManager::getInstance().getEngine(mod->id);

        EventBusClass::removeModAllListeners(mod->getName());

        scriptEngine.mEngine->getData().reset();

        if (NodeManager::getInstance().destroyEngine(scriptEngine.mID)) {
            eraseMod(name);
        }

        return {};
    } catch (const std::exception& e) {
        return ll::makeStringError("Failed to unload plugin {0}: {1}");
    }
}

std::vector<std::string> KomomoModManager::filterMods(const fs::path& directory) {
    std::vector<std::string> mods;
    if (!fs::exists(directory)) {
        return mods;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (!entry.is_directory()) {
            continue;
        }

        fs::path package = entry.path() / "package.json";
        if (!fs::exists(package)) {
            continue;
        }

        auto main = NodeManager::findMainScript(package);
        if (!main) {
            continue;
        }

        mods.push_back((entry.path() / *main).string());
    }

    return mods;
}
} // namespace Komomo