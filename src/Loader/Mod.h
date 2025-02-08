#pragma once

#include "Loader/ModManager.h"
#include "Utils/Using.h"

#include <ll/api/mod/Manifest.h>
#include <ll/api/mod/Mod.h>
#include <ll/api/mod/ModManager.h>

#include <functional>
#include <vector>

namespace Komomo {

class KomomoMod : public ll::mod::Mod {
    friend KomomoModManager;

private:
    EngineID                           id;
    std::vector<std::function<void()>> onLoadCallbacks;
    std::vector<std::function<void()>> onEnableCallbacks;
    std::vector<std::function<void()>> onDisableCallbacks;
    std::vector<std::function<void()>> onUnloadCallbacks;

public:
    KomomoMod(const ll::mod::Manifest& manifest);
    ~KomomoMod();

    static std::shared_ptr<ll::mod::Mod> current();
};
} // namespace Komomo