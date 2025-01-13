#include "Entry.h"
#include "Loader/ModManager.h"
#include "Manager/NodeManager.h"
#include "ll/api/io/LogLevel.h"

#include <ll/api/mod/ModManager.h>
#include <ll/api/mod/ModManagerRegistry.h>


#include <memory>


#if (defined(WIN32) || defined(_WIN32)) && defined(DEBUG)
#include <debugapi.h>
#endif


void registerPluginManager(const std::shared_ptr<Komomo::KomomoModManager>& pm) {
    auto& pluginManagerRegistry = ll::mod::ModManagerRegistry::getInstance();

    if (!pluginManagerRegistry.addManager(pm)) {
        throw std::runtime_error("Failed to register plugin manager");
    }
}

namespace Komomo {

std::shared_ptr<KomomoModManager> komomoModManager;

std::unique_ptr<std::reference_wrapper<ll::mod::NativeMod>>
    selfModInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)


Entry& Entry::getInstance() {
    static Entry instance;
    return instance;
}

bool Entry::load() {
    getSelf().getLogger().setLevel(ll::io::LogLevel::Debug);
#if (defined(WIN32) || defined(_WIN32)) && defined(DEBUG)
    getSelf().getLogger().info("Waiting for VC debugger attach...");
    // while (!IsDebuggerPresent()) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }
#endif
    NodeManager::getInstance().initNodeJs();
    Entry::getInstance().getSelf().getLogger().info("Load javascript plugin...");
    // auto& server        = getServer();
    // auto& pluginManager = server.getPluginManager();
    // pluginManager.registerLoader(std::make_unique<jse::JavaScriptPluginLoader>(server));
    // pluginManager.loadPlugins(std::move(jse::JavaScriptPluginLoader::filterPlugins(fs::current_path() /

    komomoModManager = std::make_shared<KomomoModManager>();
    selfModInstance  = std::make_unique<std::reference_wrapper<ll::mod::NativeMod>>(getSelf());
    registerPluginManager(komomoModManager);
    return true;
}

bool Entry::enable() { return true; }
bool Entry::disable() { return true; }
bool Entry::unload() { return true; }


auto getKomomoModManager() -> KomomoModManager& {
    if (!komomoModManager) {
        throw std::runtime_error("modManager is null");
    }

    return *komomoModManager;
}

auto getSelfModInstance() -> ll::mod::NativeMod& {
    if (!selfModInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }

    return *selfModInstance;
}
} // namespace Komomo

#include <ll/api/mod/RegisterHelper.h>
LL_REGISTER_MOD(Komomo::Entry, Komomo::Entry::getInstance());