#include "Entry.h"

#include "Loader/JavaScriptPluginLoader.h"
#include "Loader/ModManager.h"
#include "Manager/NodeManager.h"
#include "Utils/Using.h"
#include "ll/api/mod/ModManager.h"
#include "ll/api/mod/ModManagerRegistry.h"
// #include "endstone/plugin/plugin_manager.h"


#include <filesystem>
#include <memory>
#include <thread>
#include <utility>

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

Entry& Entry::getInstance() {
    static Entry instance;
    return instance;
}

bool Entry::load() {
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
    registerPluginManager(komomoModManager = std::make_shared<KomomoModManager>());
    return true;
}

bool Entry::enable() { return true; }
bool Entry::disable() { return true; }
bool Entry::unload() { return true; }

// endstone::PluginDescription const& Entry::getDescription() const { return description_; }

} // namespace Komomo

#include <ll/api/mod/RegisterHelper.h>
LL_REGISTER_MOD(Komomo::Entry, Komomo::Entry::getInstance());