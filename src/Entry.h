#pragma once

#include "Loader/ModManager.h"

#include <ll/api/mod/NativeMod.h>
#include <memory>

namespace Komomo {

// extern std::shared_ptr<KomomoModManager> komomoModManager;
class Entry {
public:
    static Entry& getInstance();


    Entry() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

    // bool unload();


private:
    ll::mod::NativeMod& mSelf;
};

[[nodiscard]] auto getKomomoModManager() -> KomomoModManager&;
[[nodiscard]] auto getSelfModInstance() -> ll::mod::NativeMod&;
}; // namespace Komomo