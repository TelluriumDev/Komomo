#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Player/ServerPlayer.h"

#include <mc/server/SimulatedPlayer.h>

class SimulatedPlayerClass : public ServerPlayerClass {
public:
    optional_ref<SimulatedPlayer> mSimulatedPlayer;

public:
    template <typename T>
    explicit SimulatedPlayerClass(SimulatedPlayer* simulatedPlayer, ConstructFromCpp<T> tag)
    : ServerPlayerClass(simulatedPlayer, tag),
      mSimulatedPlayer(simulatedPlayer){};

    explicit SimulatedPlayerClass(SimulatedPlayer* simulatedPlayer)
    : ServerPlayerClass(simulatedPlayer, ConstructFromCpp<SimulatedPlayerClass>()) {
        mSimulatedPlayer = simulatedPlayer;
    };

public: /* Member */
    virtual Member(isSimulated);
    virtual Member(getXuid);
    virtual Member(_getSpawnChunkLimit);

public: /* Method */
    static Local<Object> newSimulatedPlayer(const Arguments& args);

    Method(simulateSneaking);
    Method(simulateStopSneaking);
    Method(simulateUseItem); // two overloads
    Method(simulateDestroyLookAt);

    // virtual Method(initializeComponents);
    virtual Method(aiStep);
    // virtual Method(getMovementSettings);
    virtual Method(teleportTo);
    // virtual Method(_createChunkSource);
    virtual Method(_updateChunkPublisherView);
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
    // Method(simulateNavigateToEntity);
    // Method(simulateNavigateToLocation);
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
