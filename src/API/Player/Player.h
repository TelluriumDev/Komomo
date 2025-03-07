#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Mob/Mob.h"

#include <mc/world/actor/player/Player.h>

class PlayerClass : public MobClass {
private:
    Player *mPlayer;

public:
    template<class T>
    explicit PlayerClass(Player *player, ConstructFromCpp<T> tag) : MobClass(player, tag) {
        this->mPlayer = player;
    };
    ;

    explicit PlayerClass(Player *player) : MobClass(player, ConstructFromCpp<PlayerClass>{}) {
        this->mPlayer = player;
    };
    ;

public:
    static Local<Object> newPlayer(Player *player);

    Player *get() { return mPlayer; }

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

    // Local<Value> getBlockedUsingDamagedShieldTimeStamp();
    // Local<Value> getBlockedUsingShieldTimeStamp();
    // Local<Value> getBlockingStartTimeStamp();
    // Local<Value> getChunkRadius();
    // Local<Value> getDirection();
    // Local<Value> getEnchantmentSeed();
    // Local<Value> getLuck();
    // Local<Value> getMapIndex();
    // Local<Value> getMaxItemCooldownLeft();
    // Local<Value> getName();
    // Local<Value> getNewEnchantmentSeed(); //? Return Void
    Local<Value> getInteractText();

    // Local<Value> getPlayerIndex();

    // Local<Value> getPlayerLevel();

    Local<Value> getSelectedItemSlot();

    // Local<Value> getServerId();

    Local<Value> getSleepRotation();

    // Local<Value> getUsedPotion();

    // Local<Value> getXpEarnedAtCurrentLevel();

    Local<Value> getXpNeededForNextLevel();

    // Local<Value> getPlayerSessionId();

    // Local<Value> getPlatformOnlineId();

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

    // Local<Value> isEmoting();

    Local<Value> isFlying();

    Local<Value> isForcedRespawn();

    // Local<Value> isHostingPlayer();

    // Local<Value> isHungry();

    // Local<Value> isHurt();

    Local<Value> isInRaid();

    Local<Value> isOperator();

    // Local<Value> isRespawningFromTheEnd();

    // Local<Value> isSleepingLongEnough();

    // Local<Value> isSpawned();

    // Local<Value> isUsingItem();

    // Local<Value> isValidSpawn();

    Local<Value> canStartSleepInBed();

    Local<Value> canExistWhenDisallowMob();

    Local<Value> canFreeze();

    Local<Value> canChangeDimensionsUsingPortal();

    Local<Value> canInteractWithOtherEntitiesInGame();

    Local<Value> canObstructSpawningAndBlockPlacement();

    // Local<Value> canBeSeenOnMap();

    Local<Value> canJump();

    Local<Value> canOpenContainerScreen();

    Local<Value> canSleep();

    Local<Value> canUseOperatorBlocks();

    Local<Value> hasDiedBefore();

    // Local<Value> hasBedPosition();

    // Local<Value> hasOpenContainer();

    Local<Value> hasOwnedChunkSource();

    // Local<Value> hasRespawnAnchorPosition();

    Local<Value> hasRespawnPosition();

public: /* Method */
    Local<Value> disconnect(const Arguments &args);

    Local<Value> sendMessage(const Arguments &args);

    Local<Value> setAbility(const Arguments &args);

    Local<Value> addAndRefresh(const Arguments &args);

    Local<Value> broadcastPlayerSpawnedMobEvent(const Arguments &args);

    Local<Value> canUseAbility(const Arguments &args);

    Local<Value> causeFoodExhaustion(const Arguments &args);

    Local<Value> checkBed(const Arguments &args);

    Local<Value> checkNeedAutoJump(const Arguments &args);

    Local<Value> checkSpawnBlock(const Arguments &args);

    Local<Value> clearRespawnPosition(const Arguments &args);

    Local<Value> completeUsingItem(const Arguments &args);

    Local<Value> eat(const Arguments &args); // two overloads
    Local<Value> equippedArmorItemCanBeMoved(const Arguments &args);

    // Local<Value> fireDimensionChangedEvent(const Arguments& args);
    // Local<Value> forceAllowEating(const Arguments &args);

    Local<Value> getAbilities();

    Local<Value> getAgent(const Arguments &args);

    // Local<Value> getAgentID(const Arguments& args);
    Local<Value> getAgentIfAllowed(const Arguments &args);

    // Local<Value> getBedPosition(const Arguments& args);
    Local<Value> getCapePos(const Arguments &args);

    // Local<Value> getContainerManager(const Arguments& args);
    // Local<Value> getContainerRegistryAccess(const Arguments& args);
    // Local<Value> getContainerRegistryTracker(const Arguments& args);
    Local<Value> getCurrentActiveShield(const Arguments &args);

    // Local<Value> getDestroyProgress(const Arguments& args);
    // Local<Value> getDynamicContainerSerialization(const Arguments& args);
    // Local<Value> getExpectedSpawnDimensionId(const Arguments& args);
    Local<Value> getGameMode(const Arguments &args);

    Local<Value> getInventory(const Arguments &args);

    Local<Value> getItemCooldownLeft(const Arguments &args); // two overloads
    Local<Value> getItemInUse(const Arguments &args);

    Local<Value> getItemInteractText(const Arguments &args);

    // Local<Value> getPlatform(const Arguments& args); // two overloads
    // Local<Value> getItemStackNetManager(const Arguments& args); // two overloads
    // Local<Value> getPlayerGameType(const Arguments& args);
    // Local<Value> getPlayerPermissionLevel(const Arguments& args);
    // Local<Value> getPlayerUIItem(const Arguments& args);
    // Local<Value> getRespawnAnchorPosition(const Arguments& args);
    Local<Value> getSelectedItem(const Arguments &args);

    // Local<Value> getSkin(const Arguments& args);
    // Local<Value> getSpawnDimension(const Arguments& args);
    // Local<Value> getSpawnPosition(const Arguments& args);
    // Local<Value> getSupplies(const Arguments& args); // two overloads
    Local<Value> getTrackedBosses(const Arguments &args);

    Local<Value> getXpNeededForLevelRange(const Arguments &args);

    // Local<Value> hasOpenContainerOfContainerType(const Arguments& args);
    // Local<Value> hasResource(const Arguments& args);
    Local<Value> interact(const Arguments &args);

    Local<Value> inventoryChanged(const Arguments &args);

    // Local<Value> is2DPositionRelevant(const Arguments& args);
    // Local<Value> isHiddenFrom(const Arguments& args);
    // Local<Value> isItemOnCooldown(const Arguments& args);
    Local<Value> passengerCheckMovementStats(const Arguments &args);

    // Local<Value> playPredictiveSynchronizedSound(const Arguments& args); // two overloads
    Local<Value> recheckSpawnPosition();

    Local<Value> registerTrackedBoss(const Arguments &args);

    Local<Value> releaseUsingItem();

    // Local<Value> resendAllChunks();

    Local<Value> resetPlayerLevel();

    // Local<Value> resetPublisherInitialSpawn();

    // Local<Value> resetToDefaultGameMode();

    // Local<Value> saveLastDeathLocation(const Arguments& args);
    // Local<Value> sendEventPacket(const Arguments& args);
    // Local<Value> sendPlayerTeleported();

    // Local<Value> sendSpawnExperienceOrbPacketToServer(const Arguments& args);
    Local<Value> setAgent(const Arguments &args);

    // Local<Value> setBedRespawnPosition(const Arguments& args);
    Local<Value> setBlockRespawnUntilClientMessage(const Arguments &args);

    Local<Value> setChunkRadius(const Arguments &args);

    // Local<Value> setContainerManagerModel(const Arguments& args);
    Local<Value> setCursorSelectedItem(const Arguments &args);

    // Local<Value> setCursorSelectedItemGroup(const Arguments& args);
    Local<Value> setEmotingStatus(const Arguments &args);

    Local<Value> setEnchantmentSeed(const Arguments &args);

    Local<Value> setHasDied(const Arguments &args);

    Local<Value> setHasSeenCredits(const Arguments &args);

    // Local<Value> setInventoryOptions(const Arguments& args);
    // Local<Value> setLastDeathDimension(const Arguments& args);
    // Local<Value> setLastDeathPos(const Arguments& args);
    Local<Value> setMapIndex(const Arguments &args);

    Local<Value> setName(const Arguments &args);

    // Local<Value> setPermissions(const Arguments& args);
    Local<Value> setPlatformOnlineId(const Arguments &args);

    Local<Value> setPlayerIndex(const Arguments &args);

    // Local<Value> setPlayerUIItem(const Arguments& args);
    // Local<Value> setRespawnPosition(const Arguments& args);
    Local<Value> setRespawnPositionCandidate();

    Local<Value> setRespawnReady(const Arguments &args);

    Local<Value> setSelectedItem(const Arguments &args);

    // Local<Value> setSelectedSlot(const Arguments& args);
    // Local<Value> setSpawnBlockRespawnPosition(const Arguments& args);
    Local<Value> setUsedPotion(const Arguments &args);

    // Local<Value> shouldShowCredits();

    // Local<Value> startCooldown(const Arguments& args); // two overloads
    // Local<Value> startDestroying();

    // Local<Value> startItemUseOn(const Arguments& args);
    Local<Value> startUsingItem(const Arguments &args);

    // Local<Value> stopDestroying();

    Local<Value> stopGliding();

    // Local<Value> stopItemUseOn(const Arguments& args);
    Local<Value> stopUsingItem();

    // Local<Value> take(const Arguments& args);
    Local<Value> tickArmor();

    // Local<Value> tryDisableShield();

    Local<Value> tryStartGliding();

    // Local<Value> unRegisterTrackedBoss(const Arguments& args);
    // Local<Value> updateBlockSourceTick();

    Local<Value> updateInventoryTransactions();

    // Local<Value> updateSkin(const Arguments& args);
    // Local<Value> updateTouch();

    Local<Value> updateTrackedBosses();

    // Local<Value> useSelectedItem(const Arguments& args);

    // static
    // Local<Value> checkAndFixSpawnPosition_DEPRECATED(const Arguments& args);
    // Local<Value> checkNeedAutoJump(const Arguments& args);
    // Local<Value> getCustomHurtSound(const Arguments& args);
    // Local<Value> isDangerousVolumeForSpawn(const Arguments& args);
    // Local<Value> tryGetFromComponent(const Arguments& args); // two overloads
    // Local<Value> tryGetFromEntity(const Arguments& args);
    // Local<Value> updatePlayerGameTypeEntityData(const Arguments& args);
};

extern ClassDefine<PlayerClass> playerClassBuilder;
