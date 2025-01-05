#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/player/Player.h>

class PlayerClass : public ScriptClass {
public:
    Player* mPlayer;

public:
    PlayerClass(Player* player);

public:
    static Local<Object> newPlayer(Player* player);

public: /* Member */
    Local<Value> getRealName();
    Local<Value> getXuid();
    Local<Value> getUUID();
    Local<Value> getIPAndPort();
    Local<Value> getLocaleCode();
    Local<Value> getShadowRadius();
    Local<Value> getSpeed();
    Local<Value> getUserId();
    Local<Value> getItemUseDuration();
    Local<Value> getItemUseStartupProgress();
    Local<Value> getItemUseIntervalProgress();
    Local<Value> getMaxChunkBuildRadius();
    Local<Value> getBlockedUsingDamagedShieldTimeStamp();
    Local<Value> getBlockedUsingShieldTimeStamp();
    Local<Value> getBlockingStartTimeStamp();
    Local<Value> getChunkRadius();
    Local<Value> getDirection();
    Local<Value> getEnchantmentSeed();
    Local<Value> getLuck();
    Local<Value> getMapIndex();
    Local<Value> getMaxItemCooldownLeft();
    Local<Value> getName();
    // Local<Value> getNewEnchantmentSeed(); //? Return Void
    Local<Value> getInteractText();
    Local<Value> getPlayerIndex();
    Local<Value> getPlayerLevel();
    Local<Value> getSelectedItemSlot();
    Local<Value> getServerId();
    Local<Value> getSleepRotation();
    Local<Value> getUsedPotion();
    Local<Value> getXpEarnedAtCurrentLevel();
    Local<Value> getXpNeededForNextLevel();

    Local<Value> isLoading();
    Local<Value> isPlayerInitialized();
    Local<Value> isImmobile();
    Local<Value> isSleeping();
    Local<Value> isTeacher();
    Local<Value> isSimulated();
    Local<Value> isFireImmune();
    Local<Value> isInTrialMode();
    Local<Value> isBlocking();
    Local<Value> isSilentObserver();
    Local<Value> isEmoting();
    Local<Value> isFlying();
    Local<Value> isForcedRespawn();
    Local<Value> isHostingPlayer();
    Local<Value> isHungry();
    Local<Value> isHurt();
    Local<Value> isInRaid();
    Local<Value> isOperator();
    Local<Value> isRespawningFromTheEnd();
    Local<Value> isSleepingLongEnough();
    Local<Value> isSpawned();
    Local<Value> isUsingItem();
    Local<Value> isValidSpawn();

    Local<Value> canStartSleepInBed();
    Local<Value> canExistWhenDisallowMob();
    Local<Value> canFreeze();
    Local<Value> canChangeDimensionsUsingPortal();
    Local<Value> canInteractWithOtherEntitiesInGame();
    Local<Value> canObstructSpawningAndBlockPlacement();
    Local<Value> canBeSeenOnMap();
    Local<Value> canJump();
    Local<Value> canOpenContainerScreen();
    Local<Value> canSleep();
    Local<Value> canUseOperatorBlocks();

    Local<Value> hasDiedBefore();
    Local<Value> hasBedPosition();
    Local<Value> hasOpenContainer();
    Local<Value> hasOwnedChunkSource();
    Local<Value> hasRespawnAnchorPosition();
    Local<Value> hasRespawnPosition();

public: /* Method */
    Local<Value> disconnect(const Arguments& args);
    Local<Value> sendMessage(const Arguments& args);
    Local<Value> setAbility(const Arguments& args);
    // Local<Value> addAndRefresh(const Arguments& args);
    // Local<Value> broadcastPlayerSpawnedMobEvent(const Arguments& args);
    Local<Value> canUseAbility(const Arguments& args);
    Local<Value> causeFoodExhaustion(const Arguments& args);
    // Local<Value> checkBed(const Arguments& args);
    Local<Value> checkNeedAutoJump(const Arguments& args);
    // Local<Value> checkSpawnBlock(const Arguments& args);
    Local<Value> clearRespawnPosition(const Arguments& args);
    Local<Value> completeUsingItem(const Arguments& args);
    Local<Value> eat(const Arguments& args); // two overloads
    // Local<Value> equippedArmorItemCanBeMoved(const Arguments& args);
    // Local<Value> fireDimensionChangedEvent(const Arguments& args);
    Local<Value> forceAllowEating(const Arguments& args);
    // Local<Value> getAbilities(const Arguments& args); // two overloads
    // Local<Value> getAgent(const Arguments& args);
    // Local<Value> getAgentID(const Arguments& args);
    // Local<Value> getAgentIfAllowed(const Arguments& args);
    // Local<Value> getBedPosition(const Arguments& args);
    // Local<Value> getCapePos(const Arguments& args);
    // Local<Value> getContainerManager(const Arguments& args);
    // Local<Value> getContainerRegistryAccess(const Arguments& args);
    // Local<Value> getContainerRegistryTracker(const Arguments& args);
    // Local<Value> getCurrentActiveShield(const Arguments& args);
    // Local<Value> getDestroyProgress(const Arguments& args);
    // Local<Value> getDynamicContainerSerialization(const Arguments& args);
    // Local<Value> getExpectedSpawnDimensionId(const Arguments& args);
    // Local<Value> getGameMode(const Arguments& args);
    // Local<Value> getInventory(const Arguments& args);
    // Local<Value> getItemCooldownLeft(const Arguments& args); // two overloads
    // Local<Value> getItemInteractText(const Arguments& args);
    // Local<Value> getItemStackNetManager(const Arguments& args); // two overloads
};

extern ClassDefine<PlayerClass> playerClassBuilder;