#include "API/Player/Player.h"
#include "API/APIHelper.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"


#include <ll/api/service/PlayerInfo.h>

#include <mc/world/actor/player/AbilitiesIndex.h>


using namespace Komomo;

ClassDefine<PlayerClass> PlayerClassBuilder =
    defineClass<PlayerClass>("Player")
        .constructor(nullptr)

        .instanceProperty("xuid", &PlayerClass::getXuid)
        .instanceProperty("uuid", &PlayerClass::getUUID)
        .instanceProperty("realName", &PlayerClass::getRealName)
        .instanceProperty("name", &PlayerClass::getName)
        .instanceProperty("IPAndPort", &PlayerClass::getIPAndPort)
        .instanceProperty("localeCode", &PlayerClass::getLocaleCode)
        .instanceProperty("shadowRadius", &PlayerClass::getShadowRadius)
        .instanceProperty("speed", &PlayerClass::getSpeed)
        .instanceProperty("userId", &PlayerClass::getUserId)
        .instanceProperty("itemUseDuration", &PlayerClass::getItemUseDuration)
        .instanceProperty("itemUseStartupProgress", &PlayerClass::getItemUseStartupProgress)
        .instanceProperty("itemUseIntervalProgress", &PlayerClass::getItemUseIntervalProgress)
        .instanceProperty("maxChunkBuildRadius", &PlayerClass::getMaxChunkBuildRadius)
        .instanceProperty("blockedUsingDamagedShieldTimeStamp", &PlayerClass::getBlockedUsingDamagedShieldTimeStamp)
        .instanceProperty("blockedUsingShieldTimeStamp", &PlayerClass::getBlockedUsingShieldTimeStamp)
        .instanceProperty("blockingStartTimeStamp", &PlayerClass::getBlockingStartTimeStamp)
        .instanceProperty("chunkRadius", &PlayerClass::getChunkRadius)
        .instanceProperty("direction", &PlayerClass::getDirection)
        .instanceProperty("enchantmentSeed", &PlayerClass::getEnchantmentSeed)
        .instanceProperty("luck", &PlayerClass::getLuck)
        .instanceProperty("mapIndex", &PlayerClass::getMapIndex)
        .instanceProperty("maxItemCooldownLeft", &PlayerClass::getMaxItemCooldownLeft)
        // .instanceProperty("getNewEnchantmentSeed", &PlayerClass::getNewEnchantmentSeed)
        .instanceProperty("interactText", &PlayerClass::getInteractText)
        .instanceProperty("playerIndex", &PlayerClass::getPlayerIndex)
        .instanceProperty("playerLevel", &PlayerClass::getPlayerLevel)
        .instanceProperty("selectedItemSlot", &PlayerClass::getSelectedItemSlot)
        .instanceProperty("serverId", &PlayerClass::getServerId)
        .instanceProperty("sleepRotation", &PlayerClass::getSleepRotation)
        .instanceProperty("usedPotion", &PlayerClass::getUsedPotion)
        .instanceProperty("xpEarnedAtCurrentLevel", &PlayerClass::getXpEarnedAtCurrentLevel)
        .instanceProperty("xpNeededForNextLevel", &PlayerClass::getXpNeededForNextLevel)

        .instanceProperty("isLoading", &PlayerClass::isLoading)
        .instanceProperty("isPlayerInitialized", &PlayerClass::isPlayerInitialized)
        .instanceProperty("isImmobile", &PlayerClass::isImmobile)
        .instanceProperty("isSleeping", &PlayerClass::isSleeping)
        .instanceProperty("isTeacher", &PlayerClass::isTeacher)
        .instanceProperty("isSimulated", &PlayerClass::isSimulated)
        .instanceProperty("isFireImmune", &PlayerClass::isFireImmune)
        .instanceProperty("isInTrialMode", &PlayerClass::isInTrialMode)
        .instanceProperty("isBlocking", &PlayerClass::isBlocking)
        .instanceProperty("isSilentObserver", &PlayerClass::isSilentObserver)
        .instanceProperty("isEmoting", &PlayerClass::isEmoting)
        .instanceProperty("isFlying", &PlayerClass::isFlying)
        .instanceProperty("isForcedRespawn", &PlayerClass::isForcedRespawn)
        .instanceProperty("isHostingPlayer", &PlayerClass::isHostingPlayer)
        .instanceProperty("isHungry", &PlayerClass::isHungry)
        .instanceProperty("isHurt", &PlayerClass::isHurt)
        .instanceProperty("isInRaid", &PlayerClass::isInRaid)
        .instanceProperty("isRespawningFromTheEnd", &PlayerClass::isRespawningFromTheEnd)
        .instanceProperty("isSleepingLongEnough", &PlayerClass::isSleepingLongEnough)
        .instanceProperty("isSpawned", &PlayerClass::isSpawned)
        .instanceProperty("isUsingItem", &PlayerClass::isUsingItem)
        .instanceProperty("isValidSpawn", &PlayerClass::isValidSpawn)

        .instanceProperty("canStartSleepInBed", &PlayerClass::canStartSleepInBed)
        .instanceProperty("canExistWhenDisallowMob", &PlayerClass::canExistWhenDisallowMob)
        .instanceProperty("canFreeze", &PlayerClass::canFreeze)
        .instanceProperty("canChangeDimensionsUsingPortal", &PlayerClass::canChangeDimensionsUsingPortal)
        .instanceProperty("canInteractWithOtherEntitiesInGame", &PlayerClass::canInteractWithOtherEntitiesInGame)
        .instanceProperty("canObstructSpawningAndBlockPlacement", &PlayerClass::canObstructSpawningAndBlockPlacement)
        .instanceProperty("canBeSeenOnMap", &PlayerClass::canBeSeenOnMap)
        .instanceProperty("canJump", &PlayerClass::canJump)
        .instanceProperty("canOpenContainerScreen", &PlayerClass::canOpenContainerScreen)
        .instanceProperty("canSleep", &PlayerClass::canSleep)
        .instanceProperty("canUseOperatorBlocks", &PlayerClass::canUseOperatorBlocks)

        .instanceProperty("hasDiedBefore", &PlayerClass::hasDiedBefore)
        .instanceProperty("hasBedPosition", &PlayerClass::hasBedPosition)
        .instanceProperty("hasOpenContainer", &PlayerClass::hasOpenContainer)
        .instanceProperty("hasOwnedChunkSource", &PlayerClass::hasOwnedChunkSource)
        .instanceProperty("hasRespawnAnchorPosition", &PlayerClass::hasRespawnAnchorPosition)
        .instanceProperty("hasRespawnPosition", &PlayerClass::hasRespawnPosition)
        .build();


PlayerClass::PlayerClass(Player* player) : ScriptClass(ConstructFromCpp<PlayerClass>{}) { this->mPlayer = player; };

Local<Object> PlayerClass::newPlayer(Player* player) { return (new PlayerClass(player))->getScriptObject(); }

#define CallFunction(Type, Function)                                                                                   \
    try {                                                                                                              \
        if (!mPlayer) return Local<Value>();                                                                           \
        return Type::new##Type(mPlayer->Function);                                                                     \
    }                                                                                                                  \
    Catch;


Local<Value> PlayerClass::getXuid() {
    try {
        if (!mPlayer) return Local<Value>();
        std::string xuid;
        xuid = mPlayer->getXuid();
        if (xuid.empty()) xuid = ll::service::PlayerInfo::getInstance().fromName(mPlayer->getRealName())->xuid;
        return String::newString(xuid);
    }
    Catch;
}

Local<Value> PlayerClass::getRealName() { CallFunction(String, getRealName()); };
Local<Value> PlayerClass::getUUID() { CallFunction(String, getUuid().asString()) };
Local<Value> PlayerClass::getIPAndPort() { CallFunction(String, getIPAndPort()); };
Local<Value> PlayerClass::getLocaleCode() { CallFunction(String, getLocaleCode()); };
Local<Value> PlayerClass::getShadowRadius() { CallFunction(Number, getShadowRadius()); };
Local<Value> PlayerClass::getSpeed() { CallFunction(Number, getSpeed()); };
Local<Value> PlayerClass::getUserId() { CallFunction(Number, getUserId()); };
Local<Value> PlayerClass::getItemUseDuration() { CallFunction(Number, getItemUseDuration()); };
Local<Value> PlayerClass::getItemUseStartupProgress() { CallFunction(Number, getItemUseStartupProgress()); };
Local<Value> PlayerClass::getItemUseIntervalProgress() { CallFunction(Number, getItemUseIntervalProgress()); };
Local<Value> PlayerClass::getMaxChunkBuildRadius() { CallFunction(Number, getMaxChunkBuildRadius()); };
Local<Value> PlayerClass::getBlockedUsingDamagedShieldTimeStamp() {
    CallFunction(Number, getBlockedUsingDamagedShieldTimeStamp());
};
Local<Value> PlayerClass::getBlockedUsingShieldTimeStamp() { CallFunction(Number, getBlockedUsingShieldTimeStamp()); };
Local<Value> PlayerClass::getBlockingStartTimeStamp() { CallFunction(Number, getBlockingStartTimeStamp()); };
Local<Value> PlayerClass::getChunkRadius() { CallFunction(Number, getChunkRadius()); };
Local<Value> PlayerClass::getDirection() { CallFunction(Number, getDirection()); };
Local<Value> PlayerClass::getEnchantmentSeed() { CallFunction(Number, getEnchantmentSeed()); };
Local<Value> PlayerClass::getLuck() { CallFunction(Number, getLuck()); };
Local<Value> PlayerClass::getMapIndex() { CallFunction(Number, getMapIndex()); };
Local<Value> PlayerClass::getMaxItemCooldownLeft() { CallFunction(Number, getMaxItemCooldownLeft()); };
Local<Value> PlayerClass::getName() { CallFunction(String, getName()); };
// Local<Value> PlayerClass::getNewEnchantmentSeed() {
//     CallFunction(String, getNewEnchantmentSeed());
// };
Local<Value> PlayerClass::getInteractText() { CallFunction(String, getInteractText()); };
Local<Value> PlayerClass::getPlayerIndex() { CallFunction(Number, getPlayerIndex()); };
Local<Value> PlayerClass::getPlayerLevel() { CallFunction(Number, getPlayerLevel()); };
Local<Value> PlayerClass::getSelectedItemSlot() { CallFunction(Number, getSelectedItemSlot()); };
Local<Value> PlayerClass::getServerId() { CallFunction(String, getServerId()); }; // TODO: Reference
Local<Value> PlayerClass::getSleepRotation() { CallFunction(Number, getSleepRotation()); };
Local<Value> PlayerClass::getUsedPotion() { CallFunction(Number, getUsedPotion()); };
Local<Value> PlayerClass::getXpEarnedAtCurrentLevel() { CallFunction(Number, getXpEarnedAtCurrentLevel()); };
Local<Value> PlayerClass::getXpNeededForNextLevel() { CallFunction(Number, getXpNeededForNextLevel()); };

Local<Value> PlayerClass::isLoading() { CallFunction(Boolean, isLoading()); };
Local<Value> PlayerClass::isPlayerInitialized() { CallFunction(Boolean, isPlayerInitialized()); };
Local<Value> PlayerClass::isImmobile() { CallFunction(Boolean, isImmobile()); };
Local<Value> PlayerClass::isSleeping() { CallFunction(Boolean, isSleeping()); };
Local<Value> PlayerClass::isTeacher() { CallFunction(Boolean, isTeacher()); };
Local<Value> PlayerClass::isSimulated() { CallFunction(Boolean, isSimulated()); };
Local<Value> PlayerClass::isFireImmune() { CallFunction(Boolean, isFireImmune()); };
Local<Value> PlayerClass::isInTrialMode() { CallFunction(Boolean, isInTrialMode()); };
Local<Value> PlayerClass::isBlocking() { CallFunction(Boolean, isBlocking()); };
Local<Value> PlayerClass::isSilentObserver() { CallFunction(Boolean, isSilentObserver()); };
Local<Value> PlayerClass::isEmoting() { CallFunction(Boolean, isEmoting()); };
Local<Value> PlayerClass::isFlying() { CallFunction(Boolean, isFlying()); };
Local<Value> PlayerClass::isForcedRespawn() { CallFunction(Boolean, isForcedRespawn()); };
Local<Value> PlayerClass::isHostingPlayer() { CallFunction(Boolean, isHostingPlayer()); };
Local<Value> PlayerClass::isHungry() { CallFunction(Boolean, isHungry()); };
Local<Value> PlayerClass::isHurt() { CallFunction(Boolean, isHurt()); };
Local<Value> PlayerClass::isInRaid() { CallFunction(Boolean, isInRaid()); };
Local<Value> PlayerClass::isOperator() { CallFunction(Boolean, isOperator()); };
Local<Value> PlayerClass::isRespawningFromTheEnd() { CallFunction(Boolean, isRespawningFromTheEnd()); };
Local<Value> PlayerClass::isSleepingLongEnough() { CallFunction(Boolean, isSleepingLongEnough()); };
Local<Value> PlayerClass::isSpawned() { CallFunction(Boolean, isSpawned()); };
Local<Value> PlayerClass::isUsingItem() { CallFunction(Boolean, isUsingItem()); };
Local<Value> PlayerClass::isValidSpawn() { CallFunction(Boolean, isValidSpawn()); };

Local<Value> PlayerClass::canStartSleepInBed() { CallFunction(Boolean, canStartSleepInBed()); };
Local<Value> PlayerClass::canExistWhenDisallowMob() { CallFunction(Boolean, canExistWhenDisallowMob()); };
Local<Value> PlayerClass::canFreeze() { CallFunction(Boolean, canFreeze()); };
Local<Value> PlayerClass::canChangeDimensionsUsingPortal() { CallFunction(Boolean, canChangeDimensionsUsingPortal()); };
Local<Value> PlayerClass::canInteractWithOtherEntitiesInGame() {
    CallFunction(Boolean, canInteractWithOtherEntitiesInGame());
};
Local<Value> PlayerClass::canObstructSpawningAndBlockPlacement() {
    CallFunction(Boolean, canObstructSpawningAndBlockPlacement());
};
Local<Value> PlayerClass::canBeSeenOnMap() { CallFunction(Boolean, canBeSeenOnMap()); };
Local<Value> PlayerClass::canJump() { CallFunction(Boolean, canJump()); };
Local<Value> PlayerClass::canOpenContainerScreen() { CallFunction(Boolean, canOpenContainerScreen()); };
Local<Value> PlayerClass::canSleep() { CallFunction(Boolean, canSleep()); };
Local<Value> PlayerClass::canUseOperatorBlocks() { CallFunction(Boolean, canUseOperatorBlocks()); };

Local<Value> PlayerClass::hasDiedBefore() { CallFunction(Boolean, hasDiedBefore()); };
Local<Value> PlayerClass::hasBedPosition() { CallFunction(Boolean, hasBedPosition()); };
Local<Value> PlayerClass::hasOpenContainer() { CallFunction(Boolean, hasOpenContainer()); };
Local<Value> PlayerClass::hasOwnedChunkSource() { CallFunction(Boolean, hasOwnedChunkSource()); };
Local<Value> PlayerClass::hasRespawnAnchorPosition() { CallFunction(Boolean, hasRespawnAnchorPosition()); };
Local<Value> PlayerClass::hasRespawnPosition() { CallFunction(Boolean, hasRespawnPosition()); };

/* Method */

Local<Value> PlayerClass::disconnect(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->disconnect(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
};

Local<Value> PlayerClass::sendMessage(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->sendMessage(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::setAbility(const Arguments& args) {

    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kBoolean);

    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setAbility(ConvertFromScriptX<AbilitiesIndex>(args[0]), args[1].asBoolean().value());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// LLAPI bool addAndRefresh(class ItemStack& item);
// MCAPI void broadcastPlayerSpawnedMobEvent(::ActorType spawnedType, ::MobSpawnMethod spawnMethod);

Local<Value> PlayerClass::canUseAbility(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        return Boolean::newBoolean(mPlayer->canUseAbility(ConvertFromScriptX<AbilitiesIndex>(args[0])));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::causeFoodExhaustion(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->causeFoodExhaustion(args[0].asNumber().toFloat());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

//  MCAPI bool checkBed(::BlockSource* spawnBlockSource, ::Vec3 const* const positionToCheck);

Local<Value> PlayerClass::checkNeedAutoJump(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        return Boolean::newBoolean(
            mPlayer->checkNeedAutoJump(args[0].asNumber().toFloat(), args[1].asNumber().toFloat())
        );
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI bool checkSpawnBlock(::BlockSource const& region) const;

Local<Value> PlayerClass::clearRespawnPosition(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->clearRespawnPosition();
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::completeUsingItem(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->completeUsingItem();
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::eat(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (args.size() == 1) {
            // TODO: MCAPI void eat(::ItemStack const& instance);
            //     mPlayer->eat();
            return Boolean::newBoolean(false);
        } else {
            mPlayer->eat(args[0].asNumber().toInt32(), args[1].asNumber().toFloat());
            return Boolean::newBoolean(true);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI bool equippedArmorItemCanBeMoved(::ItemStack const& item) const;

// MCAPI void fireDimensionChangedEvent(::DimensionType fromDimension, ::DimensionType toDimension);

Local<Value> PlayerClass::forceAllowEating(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return Boolean::newBoolean(mPlayer->forceAllowEating());
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI ::LayeredAbilities const& getAbilities() const;
// MCAPI ::LayeredAbilities& getAbilities();

// MCAPI ::Agent* getAgent() const;

// MCAPI ::ActorUniqueID getAgentID() const;

// MCAPI ::Agent* getAgentIfAllowed(bool callerCanAccessOtherAgents, ::ActorUniqueID callerAgentID) const;

// MCAPI ::BlockPos const& getBedPosition() const;

// MCAPI ::Vec3 getCapePos(float a);

// MCAPI ::std::weak_ptr<::IContainerManager> getContainerManager() const;

// MCAPI ::gsl::not_null<::StackRefResult<::IContainerRegistryAccess>> getContainerRegistryAccess() const;

// MCAPI ::gsl::not_null<::StackRefResult<::IContainerRegistryTracker>> getContainerRegistryTracker() const;

// MCAPI ::ItemStack const& getCurrentActiveShield() const;

// MCAPI float getDestroyProgress(::Block const& block);

// MCAPI ::gsl::not_null<::StackRefResult<::IDynamicContainerSerialization>> getDynamicContainerSerialization() const;

// MCAPI ::DimensionType getExpectedSpawnDimensionId() const;

// MCAPI ::BlockPos const& getExpectedSpawnPosition() const;

// MCAPI ::GameMode& getGameMode() const;

// MCAPI ::Container& getInventory();

// TODO: getItemCooldownLeft
// MCAPI int getItemCooldownLeft(::HashedString const& type) const;
// MCAPI int getItemCooldownLeft(uint64 typeHash) const;

// MCAPI ::ItemStack const& getItemInUse() const;

// MCAPI ::std::string getItemInteractText(::Item const& item) const;

// MCAPI ::ItemStackNetManagerBase const* getItemStackNetManager() const;
// MCAPI ::ItemStackNetManagerBase* getItemStackNetManager();