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
    Member(isSimulated);
    Member(getXuid);
    Member(_getSpawnChunkLimit);

public: /* Method */
    static Local<Object> newSimulatedPlayer(const Arguments& args);

    Method(simulateSneaking);
    Method(simulateStopSneaking);
    Method(simulateUseItem); // two overloads
    Method(simulateDestroyLookAt);

    // Method(initializeComponents);
    Method(aiStep);
    // Method(getMovementSettings);
    Method(teleportTo);
    // Method(_createChunkSource);
    Method(_updateChunkPublisherView);
    Method(_addMoveComponent);
    // Method(_createNavigationResult);
    Method(_trySwing);
    Method(_updateMovement);
    Method(_updateRidingComponents);
    // Method(getGameTestHelper);
    Method(postAiStep);
    Method(preAiStep);
    // Method(setGameTestHelper);
    Method(setXuid);
    Method(simulateAttack);
    Method(simulateChat);
    Method(simulateDestroyBlock);
    Method(simulateDisconnect);
    Method(simulateDropSelectedItem);
    Method(simulateFly);
    Method(simulateGiveItem);
    Method(simulateInteract); // three overloads
    Method(simulateJump);
    Method(simulateLocalMove);
    Method(simulateLookAt); // three overloads
    Method(simulateMoveToLocation);
    Method(simulateNavigateToEntity);
    Method(simulateNavigateToLocation);
    Method(simulateNavigateToLocations);
    Method(simulateRespawn);
    Method(simulateSetBodyRotation);
    Method(simulateSetItem);
    Method(simulateStartBuildInSlot);
    Method(simulateStopBuild);
    Method(simulateStopDestroyingBlock);
    Method(simulateStopFlying);
    Method(simulateStopInteracting);
    Method(simulateStopMoving);
    Method(simulateStopUsingItem);
    Method(simulateUseItemInSlot);
    Method(simulateUseItemInSlotOnBlock);
    Method(simulateUseItemOnBlock);
    Method(simulateWorldMove);
};

extern ClassDefine<SimulatedPlayerClass> simulatedPlayerClassBuilder;
