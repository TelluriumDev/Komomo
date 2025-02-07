#pragma once

#include "Utils/Using.h"

#include <ll/api/mod/Mod.h>

#include <memory>

namespace Komomo {


struct EngineData {
    uint64_t               mID{uint64_t(-1)};
    string                 mFileName;

    std::shared_ptr<ll::mod::Mod> mMod{nullptr};

public:
    explicit EngineData(uint64_t engineID) : mID(engineID) {}

    Global <Function> onLoad = Global<Function>(Function::newFunction([] {}));
    Global <Function> onEnable = Global<Function>(Function::newFunction([] {}));
    Global <Function> onDisable = Global<Function>(Function::newFunction([] {}));
    Global <Function> onUnload = Global<Function>(Function::newFunction([] {}));

};


#define ENGINE_DATA() EngineScope::currentEngine()->getData<EngineData>()

#define GET_ENGINE_DATA(engine) engine->getData<EngineData>()

#undef TRY_PARSE_MACRO

#undef CALL_MOD_MACRO

} // namespace Komomo