#pragma once

#include <array>

#include <ll/api/mod/NativeMod.h>

namespace Komomo {

class Entry {
public:
    static Entry& getInstance();

    Entry() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

    bool unload();

private:
    ll::mod::NativeMod& mSelf;
};

}; // namespace Komomo