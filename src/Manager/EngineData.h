#pragma once

#include "Utils/Using.h"

#include <ll/api/mod/Mod.h>

#include <cstdint>
#include <memory>

namespace Komomo {


struct EngineData {
    uint64_t               mID{uint64_t(-1)};
    string                 mFileName;
    script::Global<Object> mRegisterInfo;

    std::shared_ptr<ll::mod::Mod> mMod{nullptr};

public:
    explicit EngineData(uint64_t engineID) : mID(engineID) {}

    
};


#define ENGINE_DATA() EngineScope::currentEngine()->getData<EngineData>()

#define GET_ENGINE_DATA(engine) engine->getData<EngineData>()

#undef TRY_PARSE_MACRO

#undef CALL_PLUGIN_MACRO

} // namespace Komomo