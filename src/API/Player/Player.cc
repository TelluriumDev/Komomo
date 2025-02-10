#include "API/Player/Player.h"
#include "API/APIHelper.h"
#include "API/Actor/Actor.h"
#include "API/Actor/ActorUniqueID.h"
#include "API/Block/BlockSource.h"
#include "API/Container/Container.h"
#include "API/Item/Item.h"
#include "API/Item/ItemStack.h"
#include "API/Math/Vec3.h"
#include "API/Mob/Agent.h"
#include "API/Player/Gamemode.h"
#include "API/Player/LayeredAbilities.h"

#include "Utils/Convert.h"
#include "Utils/Using.h"

#include <ll/api/service/PlayerInfo.h>


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
        .instanceProperty("PlayerSessionId", &PlayerClass::getPlayerSessionId)
        .instanceProperty("platformOnlineId", &PlayerClass::getPlatformOnlineId)
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

        .InstanceFunction(disconnect, PlayerClass)
        .InstanceFunction(sendMessage, PlayerClass)
        .InstanceFunction(setAbility, PlayerClass)
        .InstanceFunction(addAndRefresh, PlayerClass)
        .InstanceFunction(broadcastPlayerSpawnedMobEvent, PlayerClass)
        .InstanceFunction(canUseAbility, PlayerClass)
        .InstanceFunction(causeFoodExhaustion, PlayerClass)
        .InstanceFunction(checkBed, PlayerClass)
        .InstanceFunction(checkNeedAutoJump, PlayerClass)
        .InstanceFunction(checkSpawnBlock, PlayerClass)
        .InstanceFunction(clearRespawnPosition, PlayerClass)
        .InstanceFunction(completeUsingItem, PlayerClass)
        .InstanceFunction(eat, PlayerClass)
        .InstanceFunction(equippedArmorItemCanBeMoved, PlayerClass)
        // .InstanceFunction(fireDimensionChangedEvent, PlayerClass)
        .InstanceFunction(forceAllowEating, PlayerClass)
        .InstanceFunction(getAbilities, PlayerClass)
        .InstanceFunction(getAgent, PlayerClass)
        // .InstanceFunction(getAgentID, PlayerClass)
        .InstanceFunction(getAgentIfAllowed, PlayerClass)
        // .InstanceFunction(getBedPosition, PlayerClass)
        .InstanceFunction(getCapePos, PlayerClass)
        // .InstanceFunction(getContainerManager, PlayerClass)
        // .InstanceFunction(getContainerRegistryAccess, PlayerClass)
        // .InstanceFunction(getContainerRegistryTracker, PlayerClass)
        .InstanceFunction(getCurrentActiveShield, PlayerClass)
        // .InstanceFunction(getDestroyProgress, PlayerClass)
        // .InstanceFunction(getDynamicContainerSerialization, PlayerClass)
        // .InstanceFunction(getExpectedSpawnDimensionId, PlayerClass)
        .InstanceFunction(getGameMode, PlayerClass)
        .InstanceFunction(getInventory, PlayerClass)
        .InstanceFunction(getItemCooldownLeft, PlayerClass)
        .InstanceFunction(getItemInUse, PlayerClass)
        // .InstanceFunction(getPlatform, PlayerClass)
        // .InstanceFunction(getItemStackNetManager, PlayerClass)
        // .InstanceFunction(getPlayerGameType, PlayerClass)
        // .InstanceFunction(getPlayerPermissionLevel, PlayerClass)
        // .InstanceFunction(getPlayerUIItem, PlayerClass)
        // .InstanceFunction(getRespawnAnchorPosition, PlayerClass)
        .InstanceFunction(getSelectedItem, PlayerClass)
        // .InstanceFunction(getSkin, PlayerClass)
        // .InstanceFunction(getSpawnDimension, PlayerClass)
        // .InstanceFunction(getSpawnPosition, PlayerClass)
        // .InstanceFunction(getSupplies, PlayerClass)
        .InstanceFunction(getTrackedBosses, PlayerClass)
        .InstanceFunction(getXpNeededForLevelRange, PlayerClass)
        // .InstanceFunction(hasOpenContainerOfContainerType, PlayerClass)
        // .InstanceFunction(hasResource, PlayerClass)
        .InstanceFunction(interact, PlayerClass)
        .InstanceFunction(inventoryChanged, PlayerClass)
        // .InstanceFunction(is2DPositionRelevant, PlayerClass)
        // .InstanceFunction(isHiddenFrom, PlayerClass)
        // .InstanceFunction(isItemOnCooldown, PlayerClass)
        .InstanceFunction(passengerCheckMovementStats, PlayerClass)
        // .InstanceFunction(playPredictiveSynchronizedSound, PlayerClass)
        .InstanceFunction(recheckSpawnPosition, PlayerClass)
        .InstanceFunction(registerTrackedBoss, PlayerClass)
        .InstanceFunction(releaseUsingItem, PlayerClass)
        .InstanceFunction(resendAllChunks, PlayerClass)
        .InstanceFunction(resetPlayerLevel, PlayerClass)
        .InstanceFunction(resetPublisherInitialSpawn, PlayerClass)
        .InstanceFunction(resetToDefaultGameMode, PlayerClass)
        // .InstanceFunction(saveLastDeathLocation, PlayerClass)
        // .InstanceFunction(sendEventPacket, PlayerClass)
        .InstanceFunction(sendPlayerTeleported, PlayerClass)
        // .InstanceFunction(sendSpawnExperienceOrbPacketToServer, PlayerClass)
        .InstanceFunction(setAgent, PlayerClass)
        // .InstanceFunction(setBedRespawnPosition, PlayerClass)
        .InstanceFunction(setBlockRespawnUntilClientMessage, PlayerClass)
        .InstanceFunction(setChunkRadius, PlayerClass)
        // .InstanceFunction(setContainerManagerModel, PlayerClass)
        .InstanceFunction(setCursorSelectedItem, PlayerClass)
        // .InstanceFunction(setCursorSelectedItemGroup, PlayerClass)
        .InstanceFunction(setEmotingStatus, PlayerClass)
        .InstanceFunction(setEnchantmentSeed, PlayerClass)
        .InstanceFunction(setHasDied, PlayerClass)
        .InstanceFunction(setHasSeenCredits, PlayerClass)
        // .InstanceFunction(setInventoryOptions, PlayerClass)
        // .InstanceFunction(setLastDeathDimension, PlayerClass)
        // .InstanceFunction(setLastDeathPos, PlayerClass)
        .InstanceFunction(setMapIndex, PlayerClass)
        .InstanceFunction(setName, PlayerClass)
        // .InstanceFunction(setPermissions, PlayerClass)
        .InstanceFunction(setPlatformOnlineId, PlayerClass)
        .InstanceFunction(setPlayerIndex, PlayerClass)
        // .InstanceFunction(setPlayerUIItem, PlayerClass)
        // .InstanceFunction(setRespawnPosition, PlayerClass)
        .InstanceFunction(setRespawnPositionCandidate, PlayerClass)
        .InstanceFunction(setRespawnReady, PlayerClass)
        .InstanceFunction(setSelectedItem, PlayerClass)
        // .InstanceFunction(setSelectedSlot, PlayerClass)
        // .InstanceFunction(setSpawnBlockRespawnPosition, PlayerClass)
        .InstanceFunction(setUsedPotion, PlayerClass)
        .InstanceFunction(shouldShowCredits, PlayerClass)
        // .InstanceFunction(startCooldownOverload1, PlayerClass)
        // .InstanceFunction(startCooldownOverload2, PlayerClass)
        .InstanceFunction(startDestroying, PlayerClass)
        // .InstanceFunction(startItemUseOn, PlayerClass)
        .InstanceFunction(startUsingItem, PlayerClass)
        .InstanceFunction(stopDestroying, PlayerClass)
        .InstanceFunction(stopGliding, PlayerClass)
        // .InstanceFunction(stopItemUseOn, PlayerClass)
        .InstanceFunction(stopUsingItem, PlayerClass)
        // .InstanceFunction(take, PlayerClass)
        .InstanceFunction(tickArmor, PlayerClass)
        .InstanceFunction(tryDisableShield, PlayerClass)
        .InstanceFunction(tryStartGliding, PlayerClass)
        // .InstanceFunction(unRegisterTrackedBoss, PlayerClass)
        .InstanceFunction(updateBlockSourceTick, PlayerClass)
        .InstanceFunction(updateInventoryTransactions, PlayerClass)
        // .InstanceFunction(updateSkin, PlayerClass)
        .InstanceFunction(updateTouch, PlayerClass)
        .InstanceFunction(updateTrackedBosses, PlayerClass)
        // .InstanceFunction(useSelectedItem, PlayerClass)

        // static
        // .function(checkAndFixSpawnPosition_DEPRECATED, PlayerClass)
        // .function(checkNeedAutoJump, PlayerClass)
        // .function(getCustomHurtSound, PlayerClass)
        // .function(isDangerousVolumeForSpawn, PlayerClass)
        // .function(tryGetFromComponentOverload1, PlayerClass)
        // .function(tryGetFromComponentOverload2, PlayerClass)
        // .function(tryGetFromEntity, PlayerClass)
        // .function(updatePlayerGameTypeEntityData, PlayerClass)

        .build();


Local<Object> PlayerClass::newPlayer(Player* player) { return (new PlayerClass(player))->getScriptObject(); }

#define CallFunction(Type, Function)                                                                                   \
    try {                                                                                                              \
        if (!mPlayer) return Local<Value>();                                                                           \
        return Type::new##Type(mPlayer->Function);                                                                     \
    }                                                                                                                  \
    Catch;
#define CallVoidMethod(Function)                                                                                       \
    try {                                                                                                              \
        if (!mPlayer) return Local<Value>();                                                                           \
        mPlayer->Function;                                                                                             \
        return Boolean::newBoolean(true);                                                                              \
    }                                                                                                                  \
    CatchReturn(Boolean::newBoolean(false));

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
Local<Value> PlayerClass::getPlayerSessionId(){CallFunction(String, getPlayerSessionId())
} Local<Value> PlayerClass::getPlatformOnlineId(){CallFunction(String, getPlatformOnlineId())
} Local<Value> PlayerClass::getXpNeededForNextLevel() {
    CallFunction(Number, getXpNeededForNextLevel());
};

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

Local<Value> PlayerClass::addAndRefresh(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            if (!itemStackClass->mItemStack) return Local<Value>();
            return Boolean::newBoolean(mPlayer->addAndRefresh(*itemStackClass->mItemStack));
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> PlayerClass::broadcastPlayerSpawnedMobEvent(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->broadcastPlayerSpawnedMobEvent(
            ConvertFromScriptX<ActorType>(args[0]),
            ConvertFromScriptX<MobSpawnMethod>(args[1])
        );
    }
    Catch;
    return Local<Value>();
}

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

Local<Value> PlayerClass::checkBed(const Arguments& args) {
    CheckArgsCount(args, 2);

    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        if (IsInstanceOf<BlockSourceClass>(args[0]) && IsInstanceOf<Vec3Class>(args[1])) {
            auto blockSourceClass = engine->getNativeInstance<BlockSourceClass>(args[0]);
            auto vec3Class        = engine->getNativeInstance<Vec3Class>(args[1]);
            if (blockSourceClass->mBlockSource)
                return Boolean::newBoolean(mPlayer->checkBed(blockSourceClass->mBlockSource, &vec3Class->mVec3));
            else return Boolean::newBoolean(false);
        }
    }
    Catch;
    return Boolean::newBoolean(false);
}

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

Local<Value> PlayerClass::checkSpawnBlock(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        if (IsInstanceOf<BlockSourceClass>(args[0])) {
            auto blockSourceClass = engine->getNativeInstance<BlockSourceClass>(args[0]);
            if (blockSourceClass->mBlockSource)
                return Boolean::newBoolean(mPlayer->checkSpawnBlock(*blockSourceClass->mBlockSource));
            else return Boolean::newBoolean(false);
        }
    }
    Catch;
    return Boolean::newBoolean(false);
}

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
            CheckArgType(args[1], ValueKind::kNumber);
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

// MCAPI void fireDimensionChangedEvent(::DimensionType fromDimension, ::DimensionType toDimension); // TODO

Local<Value> PlayerClass::forceAllowEating(const Arguments& args) { CallVoidMethod(forceAllowEating()); }

// MCAPI ::LayeredAbilities const& getAbilities() const;
Local<Value> PlayerClass::getAbilities() {
    try {
        if (!mPlayer) return Local<Value>();
        return LayeredAbilitiesClass::newLayeredAbilities(&mPlayer->getAbilities());
    }
    Catch;
}

// MCAPI ::LayeredAbilities& getAbilities(); // TODO : can throw

// MCAPI ::Agent* getAgent() const;
Local<Value> PlayerClass::getAgent(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return AgentClass::newAgent(mPlayer->getAgent());
    }
    Catch;
}


// MCAPI ::ActorUniqueID getAgentID() const;
// Local<Value> PlayerClass::getAgentID(const Arguments& args) {
//     try {
//         if (!mPlayer) return Local<Value>();
//         return ActorUniqueIDClass::newActorUniqueID(&mPlayer->getAgentID());
//     }
//     Catch;
// }
// TODO

// MCAPI ::Agent* getAgentIfAllowed(bool callerCanAccessOtherAgents, ::ActorUniqueID callerAgentID) const;
Local<Value> PlayerClass::getAgentIfAllowed(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ActorUniqueIDClass>(args[1])) {
            auto engine             = EngineScope::currentEngine();
            auto actorUniqueIDClass = engine->getNativeInstance<ActorUniqueIDClass>(args[1]);
            return AgentClass::newAgent(mPlayer->getAgentIfAllowed(true, *actorUniqueIDClass->mActorUniqueID));
        } else PrintWrongArgType();
        return Local<Value>();
    }
    Catch;
}

// MCAPI ::BlockPos const& getBedPosition() const;

// MCAPI ::Vec3 getCapePos(float a);
Local<Value> PlayerClass::getCapePos(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        return Vec3Class::newVec3Class(mPlayer->getCapePos(args[0].asNumber().toFloat()));
    }
    Catch;
}

// MCAPI ::std::weak_ptr<::IContainerManager> getContainerManager() const;

// MCAPI ::gsl::not_null<::StackRefResult<::IContainerRegistryAccess>> getContainerRegistryAccess() const;

// MCAPI ::gsl::not_null<::StackRefResult<::IContainerRegistryTracker>> getContainerRegistryTracker() const;

// MCAPI ::ItemStack const& getCurrentActiveShield() const;
Local<Value> PlayerClass::getCurrentActiveShield(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return ItemStackClass::newItemStack(const_cast<ItemStack*>(&mPlayer->getCurrentActiveShield()));
    }
    Catch;
}

// MCAPI float getDestroyProgress(::Block const& block);

// MCAPI ::gsl::not_null<::StackRefResult<::IDynamicContainerSerialization>> getDynamicContainerSerialization()
// const;

// MCAPI ::DimensionType getExpectedSpawnDimensionId() const;

// MCAPI ::BlockPos const& getExpectedSpawnPosition() const;

// MCAPI ::GameMode& getGameMode() const;
Local<Value> PlayerClass::getGameMode(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return GameModeClass::newGameMode(&mPlayer->getGameMode());
    }
    Catch;
}

// MCAPI ::Container& getInventory();
Local<Value> PlayerClass::getInventory(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return ContainerClass::newContainer(&mPlayer->getInventory());
    }
    Catch;
}

// Cannot use getItemCooldownLeft(HashedString) because HashedString not implemented
Local<Value> PlayerClass::getItemCooldownLeft(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
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
Local<Value> PlayerClass::getItemInUse(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return ItemStackClass::newItemStack(const_cast<ItemStack*>(&mPlayer->getItemInUse()));
    }
    Catch;
}

// MCAPI ::std::string getItemInteractText(::Item const& item) const;
Local<Value> PlayerClass::getItemInteractText(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemClass>(args[0])) {
            auto engine    = EngineScope::currentEngine();
            auto itemClass = engine->getNativeInstance<ItemClass>(args[0]);
            return String::newString(mPlayer->getItemInteractText(*itemClass->mItem));
        } else PrintWrongArgType();
        return Local<Value>();
    }
    Catch;
}

// MCAPI ::ItemStackNetManagerBase const* getItemStackNetManager() const;
// MCAPI ::ItemStackNetManagerBase* getItemStackNetManager();

// MCAPI ::BuildPlatform getPlatform() const;


// MCAPI ::GameType getPlayerGameType() const;

// MCAPI ::PlayerPermissionLevel getPlayerPermissionLevel() const;


// MCAPI ::ItemStack const& getPlayerUIItem(::PlayerUISlot slot);

// MCAPI ::BlockPos const& getRespawnAnchorPosition() const;

// MCAPI ::ItemStack const& getSelectedItem() const;
Local<Value> PlayerClass::getSelectedItem(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        return ItemStackClass::newItemStack(const_cast<ItemStack*>(&mPlayer->getSelectedItem()));
    }
    Catch;
}

// MCAPI ::SerializedSkin const& getSkin() const;

// MCAPI ::SerializedSkin& getSkin();

// MCAPI ::DimensionType getSpawnDimension() const;

// MCAPI ::BlockPos const& getSpawnPosition() const;

// MCAPI ::PlayerInventory const& getSupplies() const;
// MCAPI ::PlayerInventory& getSupplies();

// MCAPI ::std::vector<::ActorUniqueID> const& getTrackedBosses();
Local<Value> PlayerClass::getTrackedBosses(const Arguments& args) {
    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto array  = Array::newArray();
        for (auto& boss : mPlayer->getTrackedBosses()) {
            array.add(ActorUniqueIDClass::newActorUniqueID((ActorUniqueID*)&boss));
        }
        return array;
    }
    Catch;
}

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
    Catch;
}

// MCAPI bool hasOpenContainerOfContainerType(::ContainerType containerType) const;

// MCAPI bool hasResource(::ItemDescriptor const& resource);

// MCAPI bool interact(::Actor& actor, ::Vec3 const& location);
Local<Value> PlayerClass::interact(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kObject);
    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto actor  = engine->getNativeInstance<ActorClass>(args[0]);
        if (actor->mActor) return Boolean::newBoolean(mPlayer->interact(*actor->mActor, mPlayer->getPosition()));
        else return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void
// inventoryChanged(::Container&, int slot, ::ItemStack const& oldItem, ::ItemStack const& newItem, bool
// forceBalanced);
Local<Value> PlayerClass::inventoryChanged(const Arguments& args) {
    CheckArgsCount(args, 5);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckArgType(args[4], ValueKind::kBoolean);
    try {
        if (!mPlayer) return Local<Value>();
        auto engine    = EngineScope::currentEngine();
        auto container = engine->getNativeInstance<ContainerClass>(args[0]);
        if (container->mContainer) {
            mPlayer->inventoryChanged(
                *container->mContainer,
                args[1].asNumber().toInt32(),
                *engine->getNativeInstance<ItemStackClass>(args[2])->mItemStack,
                *engine->getNativeInstance<ItemStackClass>(args[3])->mItemStack,
                args[4].asBoolean().value()
            );
        }
    }
    Catch;
    return Local<Value>();
}

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
Local<Value> PlayerClass::recheckSpawnPosition() { CallVoidMethod(recheckSpawnPosition()); }

// MCAPI void   registerTrackedBoss(::ActorUniqueID mob);
Local<Value> PlayerClass::registerTrackedBoss(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto actor  = engine->getNativeInstance<ActorClass>(args[0]);
        if (actor->mActor) mPlayer->registerTrackedBoss(actor->mActor->getOrCreateUniqueID());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void releaseUsingItem();
Local<Value> PlayerClass::releaseUsingItem() { CallVoidMethod(releaseUsingItem()); }

// MCAPI void resendAllChunks();
Local<Value> PlayerClass::resendAllChunks() { CallVoidMethod(resendAllChunks()); }

// MCAPI void resetPlayerLevel();
Local<Value> PlayerClass::resetPlayerLevel() { CallVoidMethod(resetPlayerLevel()); }

// MCAPI void resetPublisherInitialSpawn();
Local<Value> PlayerClass::resetPublisherInitialSpawn() { CallVoidMethod(resetPublisherInitialSpawn()); }

// MCAPI void resetToDefaultGameMode();
Local<Value> PlayerClass::resetToDefaultGameMode() { CallVoidMethod(resetToDefaultGameMode()); }

// MCAPI void saveLastDeathLocation(::CompoundTag& tag) const;

// MCAPI void sendEventPacket(::LegacyTelemetryEventPacket& packet) const;

// MCAPI void sendPlayerTeleported();
Local<Value> PlayerClass::sendPlayerTeleported() { CallVoidMethod(sendPlayerTeleported()); }

// MCAPI void sendSpawnExperienceOrbPacketToServer(::Vec3 const& pos, int count);

// MCAPI void   setAgent(::Agent* agent);
Local<Value> PlayerClass::setAgent(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto agent  = engine->getNativeInstance<AgentClass>(args[0]);
        if (agent->mAgent) mPlayer->setAgent(agent->mAgent);

        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setBedRespawnPosition(::BlockPos const& bedPosition);

// MCAPI void setBlockRespawnUntilClientMessage(bool val);
Local<Value> PlayerClass::setBlockRespawnUntilClientMessage(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setBlockRespawnUntilClientMessage(args[0].asBoolean().value());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setChunkRadius(uint chunkRadius);
Local<Value> PlayerClass::setChunkRadius(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setChunkRadius(args[0].asNumber().toInt32());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setContainerManagerModel(::std::shared_ptr<::ContainerManagerModel> manager);

// MCAPI void setCursorSelectedItem(::ItemStack const& item);
Local<Value> PlayerClass::setCursorSelectedItem(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            mPlayer->setCursorSelectedItem(*itemStackClass->mItemStack);
            return Boolean::newBoolean(true);
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setCursorSelectedItemGroup(::ItemGroup const& itemGroup);

// MCAPI void setEmotingStatus(uint emoteTicks);
Local<Value> PlayerClass::setEmotingStatus(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber) try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setEmotingStatus(args[0].asNumber().toInt32());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setEnchantmentSeed(int newSeed);
Local<Value> PlayerClass::setEnchantmentSeed(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber) try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setEnchantmentSeed(args[0].asNumber().toInt32());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setHasDied(bool hasDied);
Local<Value> PlayerClass::setHasDied(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean) try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setHasDied(args[0].asBoolean().value());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}
// MCAPI void setHasSeenCredits(bool value);
Local<Value> PlayerClass::setHasSeenCredits(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setHasSeenCredits(args[0].asBoolean().value());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setInventoryOptions(::InventoryOptions const& options);

// MCAPI void setLastDeathDimension(::DimensionType dimension);

// MCAPI void setLastDeathPos(::BlockPos pos);

// MCAPI void setMapIndex(int mapIndex);
Local<Value> PlayerClass::setMapIndex(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setMapIndex(args[0].asNumber().toInt32());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setName(::std::string const& newName);
Local<Value> PlayerClass::setName(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setName(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setPermissions(::CommandPermissionLevel permissions);

// MCAPI void setPlatformOnlineId(::std::string const& platformOnlineId);
Local<Value> PlayerClass::setPlatformOnlineId(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setPlatformOnlineId(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}
// MCAPI void setPlayerIndex(int index);
Local<Value> PlayerClass::setPlayerIndex(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setPlayerIndex(args[0].asNumber().toInt32());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setPlayerUIItem(::PlayerUISlot slot, ::ItemStack const& item, bool forceBalance);

// MCAPI void setRespawnPosition(::BlockPos const& inRespawnPosition, ::DimensionType dimension);

// MCAPI void setRespawnPositionCandidate();
Local<Value> PlayerClass::setRespawnPositionCandidate(){CallVoidMethod(setRespawnPositionCandidate())}


// MCAPI void setRespawnReady(::Vec3 const& respawnPosition);
Local<Value> PlayerClass::setRespawnReady(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<Vec3Class>(args[0])) {
            auto engine = EngineScope::currentEngine();
            auto vec3   = engine->getNativeInstance<Vec3Class>(args[0]);

            mPlayer->setRespawnReady(vec3->mVec3);
            return Boolean::newBoolean(true);
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void setSelectedItem(::ItemStack const& item);
Local<Value> PlayerClass::setSelectedItem(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            mPlayer->setSelectedItem(*itemStackClass->mItemStack);
            return Boolean::newBoolean(true);
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI ::ItemStack const& setSelectedSlot(int slot);
// Local<Value>             PlayerClass::setSelectedSlot(const Arguments& args) {
//     CheckArgsCount(args, 1);
//     CheckArgType(args[0], ValueKind::kNumber);
//     try {
//         if (!mPlayer) return Local<Value>();
//         return
//         ItemStackClass::newItemStack(const_cast<ItemStack*>(mPlayer->getSelectedItemSlot(args[0].asNumber().toInt32()
//         )));
//     }
//     Catch;
// }

// MCAPI bool setSpawnBlockRespawnPosition(::BlockPos const& spawnBlockPosition, ::DimensionType dimension);

// MCAPI void setUsedPotion(bool used);
Local<Value> PlayerClass::setUsedPotion(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mPlayer) return Local<Value>();
        mPlayer->setUsedPotion(args[0].asBoolean().value());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI bool shouldShowCredits() const;
Local<Value> PlayerClass::shouldShowCredits() { CallVoidMethod(shouldShowCredits()); }

// MCAPI void startCooldown(::Item const* item, bool updateClient);
// MCAPI void startCooldown(::HashedString const& type, int tickDuration, bool updateClient);

// MCAPI void startDestroying();
Local<Value> PlayerClass::startDestroying() { CallVoidMethod(startDestroying()); }

// MCAPI void
// startItemUseOn(uchar face, ::BlockPos const& blockPos, ::BlockPos const& buildBlockPos, ::ItemStack const& item);

// MCAPI void startUsingItem(::ItemStack const& instance, int duration);
Local<Value> PlayerClass::startUsingItem(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mPlayer) return Local<Value>();
        if (IsInstanceOf<ItemStackClass>(args[0])) {
            auto engine         = EngineScope::currentEngine();
            auto itemStackClass = engine->getNativeInstance<ItemStackClass>(args[0]);
            mPlayer->startUsingItem(*itemStackClass->mItemStack, args[1].asNumber().toInt32());
            return Boolean::newBoolean(true);
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}


// MCAPI void stopDestroying();
Local<Value> PlayerClass::stopDestroying() { CallVoidMethod(stopDestroying()); }

// MCAPI void stopGliding();
Local<Value> PlayerClass::stopGliding() { CallVoidMethod(stopGliding()); }

// MCAPI void stopItemUseOn(::BlockPos const& blockPos, ::ItemStack const& item);

// MCAPI void stopUsingItem();
Local<Value> PlayerClass::stopUsingItem() { CallVoidMethod(stopUsingItem()); }

// MCAPI bool take(::Actor& actor, int, int favoredSlot);

// MCAPI void tickArmor();
Local<Value> PlayerClass::tickArmor() { CallVoidMethod(tickArmor()); }

// MCAPI void tryDisableShield();
Local<Value> PlayerClass::tryDisableShield() { CallVoidMethod(tryDisableShield()); }

// MCAPI bool tryStartGliding();
Local<Value> PlayerClass::tryStartGliding() { CallVoidMethod(tryStartGliding()); }

// MCAPI bool tryStartSleeping(::BlockPos const& blockPos);

// MCAPI void unRegisterTrackedBoss(::ActorUniqueID mob);

// MCAPI void updateBlockSourceTick();
Local<Value> PlayerClass::updateBlockSourceTick() { CallVoidMethod(updateBlockSourceTick()); }

// MCAPI void updateInventoryTransactions();
Local<Value> PlayerClass::updateInventoryTransactions() { CallVoidMethod(updateInventoryTransactions()); }

// MCAPI void updateSkin(::SerializedSkin const& skin, int clientSubID);

// MCAPI void updateTouch();
Local<Value> PlayerClass::updateTouch() { CallVoidMethod(updateTouch()); }

// MCAPI void updateTrackedBosses();
Local<Value> PlayerClass::updateTrackedBosses() { CallVoidMethod(updateTrackedBosses()); }

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