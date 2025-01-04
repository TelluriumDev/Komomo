#include "API/Player/Player.h"
#include "API/APIHelper.h"
#include "Utils/Using.h"

#include <ll/api/service/PlayerInfo.h>

using namespace Komomo;

ClassDefine<PlayerClass> PlayerClassBuilder = defineClass<PlayerClass>("Player")
                                                  .constructor(nullptr)

                                                  .instanceProperty("getXuid", &PlayerClass::getXuid)


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
        try {
            xuid = mPlayer->getXuid();
        } catch (...) {
            xuid = ll::service::PlayerInfo::getInstance().fromName(mPlayer->getRealName())->xuid;
        }
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
