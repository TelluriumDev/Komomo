#pragma once

#include "Loader/ModManager.h"

#include "Utils/Using.h"
#include "ll/api/mod/Manifest.h"
#include "ll/api/mod/Mod.h"
#include "ll/api/mod/ModManager.h"

namespace Komomo {

class KomomoMod : public ll::mod::Mod {
    friend KomomoModManager;

private:
    EngineID id;
public:
    KomomoMod(const ll::mod::Manifest& manifest);
    ~KomomoMod();

    static std::shared_ptr<ll::mod::Mod> current();
};
} // namespace Komomo