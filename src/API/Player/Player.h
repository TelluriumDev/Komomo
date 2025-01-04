#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/player/Player.h>

class PlayerClass : public ScriptClass {
private:
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
};

extern ClassDefine<PlayerClass> PlayerClassBuilder;