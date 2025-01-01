#include "Loader/ModManager.h"
#include "Entry.h"
#include "Manager/EngineData.h"
#include "Manager/NodeManager.h"

#include "Utils/Util.h"
#include "ll/api/Expected.h"
#include "ll/api/mod/Mod.h"

#include <filesystem>
#include <memory>


#define CatchNotReturn                                                                                                 \
    catch (...) {                                                                                                      \
    }


constexpr auto ModManagerName = "KomomoJS";

namespace Komomo {

KomomoModManager::KomomoModManager() : ll::mod::ModManager(ModManagerName) {}
KomomoModManager::~KomomoModManager() = default;

ll::Expected<> KomomoModManager::load(ll::mod::Manifest manifest) {
    auto& manager = NodeManager::getInstance();
    auto  wrapper = manager.newScriptEngine();

    EngineScope scope(wrapper->mEngine);
    auto        data = ENGINE_DATA();
    auto        file = fs::current_path().string() + "\\plugins\\" + manifest.name + "\\" + manifest.entry; //!!!!!
    try {
        auto path = fs::path(file);

        data->mFileName = path.filename().string();

        fs::path package = path.parent_path() / "package.json";

        // 安装依赖
        if (NodeManager::packageHasDependency(package)
            && !NodeManager::packageHasDependency(path.parent_path() / "node_modules")) {
            Entry::getInstance().getSelf().getLogger().info("Installing dependencies for mod: {}", path.filename());
            manager.NpmInstall(path.parent_path().string());
        }

        if (!NodeManager::loadFile(wrapper, file, NodeManager::packageIsEsm(package))) {
            Entry::getInstance().getSelf().getLogger().error("Failed to load mod: {}", file);
            return ll::makeStringError("Failed to load mod");
        }

        // 解析注册数据
        // JsPluginDescriptionBuilder builder{};
        // builder.description        = data->tryParseDescription();
        // builder.load               = data->tryParseLoad();
        // builder.authors            = data->tryParseAuthors();
        // builder.contributors       = data->tryParseContributors();
        // builder.website            = data->tryParseWebsite();
        // builder.prefix             = data->tryParsePrefix();
        // builder.provides           = data->tryParseProvides();
        // builder.depend             = data->tryParseDepend();
        // builder.soft_depend        = data->tryParseSoftDepend();
        // builder.load_before        = data->tryParseLoadBefore();
        // builder.default_permission = data->tryParseDefaultPermission();
        // data->tryParseCommands(builder);
        // data->tryParsePermissions(builder);

        // 创建插件实例
        auto mod = std::make_shared<ll::mod::Mod>(manifest);
        // auto mod   = new JavaScriptPlugin(data->mID, builder.build(data->tryParseName(), data->tryParseVersion()));
        data->mMod = mod;


        mod->onLoad([&data](ll::mod::Mod&) {
            data   = ENGINE_DATA();
            auto        engine = NodeManager::getInstance().getEngine(data->mID);
            EngineScope scope(engine->mEngine);
            try {
                ENGINE_DATA()->callOnLoad();
            }
            CatchNotReturn;
            return true;
        });
        auto id = data->mID;
        mod->onEnable([&id](ll::mod::Mod& mod) {
            auto        engine = NodeManager::getInstance().getEngine(id);
            EngineScope scope(engine->mEngine);
            try {
                ENGINE_DATA()->callOnEnable();
            }
            CatchNotReturn;
            return true;
        });
        mod->onDisable([](ll::mod::Mod&) {
            auto        data   = ENGINE_DATA();
            auto        engine = NodeManager::getInstance().getEngine(data->mID);
            EngineScope scope(engine->mEngine);
            try {
                ENGINE_DATA()->callOnDisable();
            }
            CatchNotReturn;
            return true;
        });
        mod->onUnload([](ll::mod::Mod&) {
            auto data = ENGINE_DATA();
            NodeManager::getInstance().destroyEngine(data->mID);
            return true;
        });

        addMod(manifest.name, mod);

        // return mod->onLoad().transform([&, this] {  });


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
ll::Expected<> KomomoModManager::unload(std::string_view name) { return {}; }
} // namespace Komomo