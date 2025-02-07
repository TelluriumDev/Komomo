#include "Entry.h"
#include "Loader/ModManager.h"
#include "Manager/NodeManager.h"

#include "ll/api/io/LogLevel.h"
#include <ll/api/mod/ModManager.h>
#include <ll/api/mod/ModManagerRegistry.h>

#include <memory>

void registerModManager(const std::shared_ptr<Komomo::KomomoModManager>& pm) {
    auto& modManagerRegistry = ll::mod::ModManagerRegistry::getInstance();

    if (!modManagerRegistry.addManager(pm)) {
        throw std::runtime_error("Failed to register mod manager");
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

#ifdef DEBUG
    getSelf().getLogger().setLevel(ll::io::LogLevel::Debug);
#endif

    NodeManager::getInstance().initNodeJs();
    getInstance().getSelf().getLogger().info("Load javascript mod...");

    komomoModManager = std::make_shared<KomomoModManager>();
    selfModInstance  = std::make_unique<std::reference_wrapper<ll::mod::NativeMod>>(getSelf());
    registerModManager(komomoModManager);
    return true;
}

bool Entry::enable() { return true; }
bool Entry::disable() { return true; }
// bool Entry::unload() {
//     // NodeManager::getInstance().shutdownNodeJs();
//     return true;
// }


auto getKomomoModManager() -> KomomoModManager& {
    if (!komomoModManager) {
        throw std::runtime_error("modManager is null");
    }

    return *komomoModManager;
}

auto getSelfModInstance() -> ll::mod::NativeMod& {
    if (!selfModInstance) {
        throw std::runtime_error("selfModInstance is null");
    }

    return *selfModInstance;
}
} // namespace Komomo

#include <ll/api/mod/RegisterHelper.h>
LL_REGISTER_MOD(Komomo::Entry, Komomo::Entry::getInstance());