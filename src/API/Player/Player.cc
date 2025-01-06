#include "API/Player/Player.h"
#include "API/APIHelper.h"
#include "API/ItemStack/ItemStack.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"


#include <ll/api/service/PlayerInfo.h>

#include <mc/world/actor/player/AbilitiesIndex.h>


using namespace Komomo;

ClassDefine<PlayerClass> playerClassBuilder =
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
Local<Value> PlayerClass::addAndRefresh(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            return Boolean::newBoolean(mPlayer->addAndRefresh(*itemStackClass->mItemStack));
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}
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
            if (IsInstanceOf<ItemStackClass>(args[0])) {
                auto engine         = EngineScope::currentEngine();
                auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
                mPlayer->eat(*itemStackClass->mItemStack);
                return Boolean::newBoolean(true);
            } else PrintWrongArgType();
            return Boolean::newBoolean(false);
        } else {
            mPlayer->eat(args[0].asNumber().toInt32(), args[1].asNumber().toFloat());
            return Boolean::newBoolean(true);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::equippedArmorItemCanBeMoved(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            return Boolean::newBoolean(mPlayer->equippedArmorItemCanBeMoved(*itemStackClass->mItemStack));
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

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
// Local<Value> PlayerClass::getCurrentActiveShield(const Arguments& args) {
//     try {
//         if (!mPlayer) return Local<Value>();
//         return ItemStackClass::newItemStack(mPlayer->getCurrentActiveShield());
// --------Failed there because const ItemStack cannot be converted to ItemStack*--------
//     }
//     Catch;
// }

// MCAPI float getDestroyProgress(::Block const& block);

// MCAPI ::gsl::not_null<::StackRefResult<::IDynamicContainerSerialization>> getDynamicContainerSerialization() const;

// MCAPI ::DimensionType getExpectedSpawnDimensionId() const;

// MCAPI ::BlockPos const& getExpectedSpawnPosition() const;

// MCAPI ::GameMode& getGameMode() const;

// MCAPI ::Container& getInventory();

// Cannot use getItemCooldownLeft(HashedString) because HashedString not implemented
Local<Value> PlayerClass::getItemCooldownLeft(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        // if (IsInstanceOf<HashedString>(args[0])) {
        //     auto engine            = EngineScope::currentEngine();
        //     auto hashedStringClass = engine->getNativeInstance<HashedStringClass>(args[0]);
        //     return Number::newNumber(mPlayer->getItemCooldownLeft(*HashedStringClass->mHashString));
        // } else {
        CheckArgType(args[0], ValueKind::kNumber);
        return Number::newNumber(mPlayer->getItemCooldownLeft(args[0].asNumber().toInt64()));
        // }
    }
    Catch;
}

// MCAPI ::ItemStack const& getItemInUse() const;

// MCAPI ::std::string getItemInteractText(::Item const& item) const;

// MCAPI ::ItemStackNetManagerBase const* getItemStackNetManager() const;
// MCAPI ::ItemStackNetManagerBase* getItemStackNetManager();

// MCAPI ::BuildPlatform getPlatform() const;

Local<Value> PlayerClass::getPlatformOnlineId(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return String::newString(mPlayer->getPlatformOnlineId());
    }
    Catch;
}

// MCAPI ::GameType getPlayerGameType() const;

// MCAPI ::PlayerPermissionLevel getPlayerPermissionLevel() const;

Local<Value> PlayerClass::getPlayerSessionId(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return String::newString(mPlayer->getPlayerSessionId());
    }
    Catch;
}

// MCAPI ::ItemStack const& getPlayerUIItem(::PlayerUISlot slot);

// MCAPI ::BlockPos const& getRespawnAnchorPosition() const;

// MCAPI ::ItemStack const& getSelectedItem() const;
// Local<Value> PlayerClass::getSelectedItem(const Arguments& args) {
//     try {
//         if (!mPlayer) return Local<Value>();
//         return ItemStackClass::newItemStack(mPlayer->getSelectedItem());
// --------Failed there because const ItemStack cannot be converted to ItemStack*--------
//     }
//     Catch;
// }

// MCAPI ::SerializedSkin const& getSkin() const;

// MCAPI ::SerializedSkin& getSkin();

// MCAPI ::DimensionType getSpawnDimension() const;

// MCAPI ::BlockPos const& getSpawnPosition() const;

// MCAPI ::PlayerInventory const& getSupplies() const;
// MCAPI ::PlayerInventory& getSupplies();

// MCAPI ::std::vector<::ActorUniqueID> const& getTrackedBosses();

Local<Value> PlayerClass::getXpNeededForLevelRange(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        return Number::newNumber(
            mPlayer->getXpNeededForLevelRange(args[0].asNumber().toInt32(), args[1].asNumber().toInt32())
        );
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI bool hasOpenContainerOfContainerType(::ContainerType containerType) const;

// MCAPI bool hasResource(::ItemDescriptor const& resource);

// MCAPI bool interact(::Actor& actor, ::Vec3 const& location);

// MCAPI void
// inventoryChanged(::Container&, int slot, ::ItemStack const& oldItem, ::ItemStack const& newItem, bool forceBalanced);

// MCAPI bool is2DPositionRelevant(::DimensionType dimension, ::BlockPos const& position);

// MCAPI bool isHiddenFrom(::Mob& target) const;

// MCAPI bool isItemOnCooldown(::HashedString const& type) const;

Local<Value> PlayerClass::passengerCheckMovementStats(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->passengerCheckMovementStats();
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void playPredictiveSynchronizedSound(
//     ::SharedTypes::Legacy::LevelSoundEvent type,
//     ::Vec3 const&                          pos,
//     ::Block const&                         block,
//     ::ActorDefinitionIdentifier const&     entityType,
//     bool                                   isGlobal
// );
// MCAPI void playPredictiveSynchronizedSound(
//     ::SharedTypes::Legacy::LevelSoundEvent type,
//     ::Vec3 const&                          pos,
//     ::ActorDefinitionIdentifier const&     entityType,
//     int                                    data,
//     bool                                   isGlobal
// );

// MCAPI void recheckSpawnPosition();

// MCAPI void registerTrackedBoss(::ActorUniqueID mob);

// MCAPI void releaseUsingItem();

// MCAPI void resendAllChunks();

// MCAPI void resetPlayerLevel();

// MCAPI void resetPublisherInitialSpawn();

// MCAPI void resetToDefaultGameMode();

// MCAPI void saveLastDeathLocation(::CompoundTag& tag) const;

// MCAPI void sendEventPacket(::LegacyTelemetryEventPacket& packet) const;

// MCAPI void sendPlayerTeleported();

// MCAPI void sendSpawnExperienceOrbPacketToServer(::Vec3 const& pos, int count);

// MCAPI void setAgent(::Agent* agent);

// MCAPI void setBedRespawnPosition(::BlockPos const& bedPosition);

// MCAPI void setBlockRespawnUntilClientMessage(bool val);

// MCAPI void setChunkRadius(uint chunkRadius);

// MCAPI void setContainerManagerModel(::std::shared_ptr<::ContainerManagerModel> manager);

// MCAPI void setCursorSelectedItem(::ItemStack const& item);

// MCAPI void setCursorSelectedItemGroup(::ItemGroup const& itemGroup);

// MCAPI void setEmotingStatus(uint emoteTicks);

// MCAPI void setEnchantmentSeed(int newSeed);

// MCAPI void setHasDied(bool hasDied);

// MCAPI void setHasSeenCredits(bool value);

// MCAPI void setInventoryOptions(::InventoryOptions const& options);

// MCAPI void setLastDeathDimension(::DimensionType dimension);

// MCAPI void setLastDeathPos(::BlockPos pos);

// MCAPI void setMapIndex(int mapIndex);

// MCAPI void setName(::std::string const& newName);

// MCAPI void setPermissions(::CommandPermissionLevel permissions);

// MCAPI void setPlatformOnlineId(::std::string const& platformOnlineId);

// MCAPI void setPlayerIndex(int index);

// MCAPI void setPlayerUIItem(::PlayerUISlot slot, ::ItemStack const& item, bool forceBalance);

// MCAPI void setRespawnPosition(::BlockPos const& inRespawnPosition, ::DimensionType dimension);
// MCAPI void setRespawnPositionCandidate();

// MCAPI void setRespawnReady(::Vec3 const& respawnPosition);

// MCAPI void setSelectedItem(::ItemStack const& item);

// MCAPI ::ItemStack const& setSelectedSlot(int slot);

// MCAPI bool setSpawnBlockRespawnPosition(::BlockPos const& spawnBlockPosition, ::DimensionType dimension);

// MCAPI void setUsedPotion(bool used);

// MCAPI bool shouldShowCredits() const;

// MCAPI void startCooldown(::Item const* item, bool updateClient);
// MCAPI void startCooldown(::HashedString const& type, int tickDuration, bool updateClient);

// MCAPI void startDestroying();

// MCAPI void
// startItemUseOn(uchar face, ::BlockPos const& blockPos, ::BlockPos const& buildBlockPos, ::ItemStack const& item);

// MCAPI void startUsingItem(::ItemStack const& instance, int duration);

// MCAPI void stopDestroying();

// MCAPI void stopGliding();

// MCAPI void stopItemUseOn(::BlockPos const& blockPos, ::ItemStack const& item);

// MCAPI void stopUsingItem();

// MCAPI bool take(::Actor& actor, int, int favoredSlot);

// MCAPI void tickArmor();

// MCAPI void tryDisableShield();

// MCAPI bool tryStartGliding();

// MCAPI void unRegisterTrackedBoss(::ActorUniqueID mob);

// MCAPI void updateBlockSourceTick();

// MCAPI void updateInventoryTransactions();

// MCAPI void updateSkin(::SerializedSkin const& skin, int clientSubID);

// MCAPI void updateTouch();

// MCAPI void updateTrackedBosses();

// MCAPI void useSelectedItem(::ItemUseMethod itemUseMethod, bool consumeItem);

// static

// MCAPI static ::std::optional<::Player::FixedSpawnPositionData_DEPRECATED> checkAndFixSpawnPosition_DEPRECATED(
//     ::Vec3 const&                                  spawnPosition,
//     ::std::vector<::gsl::not_null<::BlockSource*>> regions,
//     ::AABB                                         aabb,
//     bool                                           adjustYToSolidGround,
//     bool,
//     bool  searchUp,
//     bool  positionFromSave,
//     bool  spawningAtForcedSpawn,
//     short dimensionHeight
// );

// MCAPI static bool checkNeedAutoJump(
//     ::IConstBlockSource const&                         region,
//     ::AABBShapeComponent const&                        aabbShape,
//     ::ActorRotationComponent const&                    actorRotation,
//     float                                              movementSpeed,
//     ::StateVectorComponent const&                      stateVector,
//     ::optional_ref<::GetCollisionShapeInterface const> collisionShapeInterface,
//     float                                              inputMoveX,
//     float                                              inputMoveZ
// );

// MCAPI static ::std::optional<::SDharedTypes::Legacy::LevelSoundEvent>
// getCustomHurtSound(::Mob& mob, ::ActorDamageCause cause);

// MCAPI static bool isDangerousVolumeForSpawn(::BlockSource& region, ::AABB const& centeredAABB);

// MCAPI static ::Player const* tryGetFromComponent(::PlayerComponent const&, ::ActorOwnerComponent const&, bool);
// MCAPI static ::Player* tryGetFromComponent(::PlayerComponent const&, ::ActorOwnerComponent& actor, bool
// includeRemoved);

// MCAPI static ::Player* tryGetFromEntity(::EntityContext& entity, bool includeRemoved);
// MCAPI static ::Player* tryGetFromEntity(::StackRefResult<::EntityContext> entity, bool includeRemoved);

// MCAPI static void
// updatePlayerGameTypeEntityData(::EntityContext& entity, ::GameType gameType, ::GameType defaultGameType);