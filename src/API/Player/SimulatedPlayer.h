#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/world/simulatedplayer/SimulatedPlayer.h>

#include <mc/server/SimulatedPlayer.h>

class SimulatedPlayerClass : public ScriptClass {
public:
    optional_ref<SimulatedPlayer> mSimulatedPlayer;

public:
    SimulatedPlayerClass(
        std::string const&         name,
        std::optional<Vec3> const& pos      = std::nullopt,
        DimensionType              dimId    = 0,
        Vec2 const&                rotation = {0, 0}
    );

public: /* Member */
public: /* Method */
    static Local<Object> newSimulatedPlayer(const Arguments& args);

    
};

extern ClassDefine<SimulatedPlayerClass> simulatedPlayerClassBuilder;
