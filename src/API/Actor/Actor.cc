#include "API/Actor/Actor.h"
#include "API/Actor/ActorDamageSource.h"
#include "API/Actor/ActorInteraction.h"
#include "API/Actor/ActorUniqueID.h"
#include "API/Actor/EquipmentTable.h"
#include "API/Actor/ItemActor.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Block/IConstBlockSource.h"
#include "API/Dimension/DimensionType.h"
#include "API/Entity/EntityContext.h"
#include "API/Entity/RideableComponent.h"
#include "API/Item/ItemStack.h"
#include "API/Math/HitResult.h"
#include "API/Math/Vec2.h"
#include "API/Math/Vec3.h"
#include "API/Mob/MobEffectInstance.h"
#include "API/Network/Packet/ChangeDimensionPacket.h"
#include "API/Network/Packet/UpdateEquipPacket.h"
#include "API/Network/Packet/UpdateTradePacket.h"
#include "API/Player/Player.h"
#include "API/Player/PlayerMovementSettings.h"

#include "API/Math/AABB.h"


ClassDefine<ActorClass> actorClassBuilder =
        defineClass<ActorClass>("Actor")
        .constructor(nullptr)

        .instanceProperty("typeName", &ActorClass::typeName)
        .instanceProperty("isOnGround", &ActorClass::isOnGround)
        .instanceProperty("posDeltaPerSecLength", &ActorClass::posDeltaPerSecLength)
        .instanceProperty("isFireImmune", &ActorClass::isFireImmune)
        .instanceProperty("canDisableShield", &ActorClass::canDisableShield)
        .instanceProperty("entityLocNameString", &ActorClass::entityLocNameString)
        // .instanceProperty("isInWall", &ActorClass::isInWall)
        .instanceProperty("isInvisible", &ActorClass::isInvisible)
        .instanceProperty("canShowNameTag", &ActorClass::canShowNameTag)
        .instanceProperty("formattedNameTag", &ActorClass::formattedNameTag)
        .instanceProperty("shadowRadius", &ActorClass::shadowRadius)
        .instanceProperty("canInteractWithOtherEntitiesInGame", &ActorClass::canInteractWithOtherEntitiesInGame)
        .instanceProperty("isSilentObserver", &ActorClass::isSilentObserver)
        .instanceProperty("isSleeping", &ActorClass::isSleeping)
        .instanceProperty("isBlocking", &ActorClass::isBlocking)
        .instanceProperty("isAlive", &ActorClass::isAlive)
        .instanceProperty("isOnFire", &ActorClass::isOnFire)
        .instanceProperty("isSurfaceMob", &ActorClass::isSurfaceMob)
        .instanceProperty("isTargetable", &ActorClass::isTargetable)
        .instanceProperty("canPowerJump", &ActorClass::canPowerJump)
        .instanceProperty("isEnchanted", &ActorClass::isEnchanted)
        // .instanceProperty("shouldRender", &ActorClass::shouldRender)
        // .instanceProperty("consumeTotem", &ActorClass::consumeTotem)
        .instanceProperty("canFreeze", &ActorClass::canFreeze)
        .instanceProperty("canChangeDimensionsUsingPortal", &ActorClass::canChangeDimensionsUsingPortal)
        .instanceProperty("canBePulledIntoVehicle", &ActorClass::canBePulledIntoVehicle)
        .instanceProperty("inCaravan", &ActorClass::inCaravan)
        .instanceProperty("canSynchronizeNewEntity", &ActorClass::canSynchronizeNewEntity)
        .instanceProperty("deathTime", &ActorClass::deathTime)
        .instanceProperty("canObstructSpawningAndBlockPlacement", &ActorClass::canObstructSpawningAndBlockPlacement)
        .instanceProperty("mapDecorationRotation", &ActorClass::mapDecorationRotation)
        .instanceProperty("shouldDropDeathLoot", &ActorClass::shouldDropDeathLoot)
        .instanceProperty("hasDiedBefore", &ActorClass::hasDiedBefore)
        // .instanceProperty("shouldTryMakeStepSound", &ActorClass::shouldTryMakeStepSound)
        .instanceProperty("canBeginOrContinueClimbingLadder", &ActorClass::canBeginOrContinueClimbingLadder)
        .instanceProperty("canCurrentlySwim", &ActorClass::canCurrentlySwim)
        .instanceProperty("canFly", &ActorClass::canFly)
        .instanceProperty("canReceiveMobEffectsFromGameplay", &ActorClass::canReceiveMobEffectsFromGameplay)
        .instanceProperty("canSeeDaylight", &ActorClass::canSeeDaylight)
        // .instanceProperty("canPickupItems", &ActorClass::canPickupItems)
        // .instanceProperty("chainedDamageEffects", &ActorClass::chainedDamageEffects)
        .instanceProperty("chestSlots", &ActorClass::chestSlots)
        // .instanceProperty("collidableMob", &ActorClass::collidableMob)
        .instanceProperty("currentSwimAmount", &ActorClass::currentSwimAmount)
        // .instanceProperty("damageNearbyMobs", &ActorClass::damageNearbyMobs)
        .instanceProperty("equipSlots", &ActorClass::equipSlots)
        // .instanceProperty("equipmentCount", &ActorClass::equipmentCount)
        .instanceProperty("fallDistance", &ActorClass::fallDistance)
        // .instanceProperty("health", &ActorClass::health)
        // .instanceProperty("hurtDir", &ActorClass::hurtDir)
        // .instanceProperty("hurtTime", &ActorClass::hurtTime)
        // .instanceProperty("inventorySize", &ActorClass::inventorySize)
        // .instanceProperty("isExperienceDropEnabled", &ActorClass::isExperienceDropEnabled)
        // .instanceProperty("lastHurtByMobTime", &ActorClass::lastHurtByMobTime)
        // .instanceProperty("lastHurtByMobTimestamp", &ActorClass::lastHurtByMobTimestamp)
        // .instanceProperty("lastHurtDamage", &ActorClass::lastHurtDamage)
        // .instanceProperty("lastHurtMobTimestamp", &ActorClass::lastHurtMobTimestamp)
        // .instanceProperty("lastHurtTimestamp", &ActorClass::lastHurtTimestamp)
        // .instanceProperty("levelTimeStamp", &ActorClass::levelTimeStamp)
        // .instanceProperty("limitedLifetimeTicks", &ActorClass::limitedLifetimeTicks)
        .instanceProperty("markVariant", &ActorClass::markVariant)
        // .instanceProperty("maxAutoStep", &ActorClass::maxAutoStep)
        .instanceProperty("maxHealth", &ActorClass::maxHealth)
        .instanceProperty("nameTag", &ActorClass::nameTag)
        // .instanceProperty("nameTagAsHash", &ActorClass::nameTagAsHash)
        // .instanceProperty("onDeathExperience", &ActorClass::onDeathExperience)
        // .instanceProperty("persistingTradeRiches", &ActorClass::persistingTradeRiches)
        // .instanceProperty("radius", &ActorClass::radius)
        .instanceProperty("ridingHeight", &ActorClass::ridingHeight)
        // .instanceProperty("shakeTime", &ActorClass::shakeTime)
        // .instanceProperty("skinID", &ActorClass::skinID)
        // .instanceProperty("speedInMetersPerSecond", &ActorClass::speedInMetersPerSecond)
        // .instanceProperty("strength", &ActorClass::strength)
        // .instanceProperty("strengthMax", &ActorClass::strengthMax)
        // .instanceProperty("tradeInterest", &ActorClass::tradeInterest)
        .instanceProperty("variant", &ActorClass::variant)
        // .instanceProperty("verticalSpeedInMetersPerSecond", &ActorClass::verticalSpeedInMetersPerSecond)
        // .instanceProperty("yHeadRot", &ActorClass::yHeadRot)
        // .instanceProperty("hasAnyEffects", &ActorClass::hasAnyEffects)
        // .instanceProperty("hasDimension", &ActorClass::hasDimension)
        // .instanceProperty("hasFishingHook", &ActorClass::hasFishingHook)
        // .instanceProperty("hasLevel", &ActorClass::hasLevel)
        // .instanceProperty("hasPassenger", &ActorClass::hasPassenger)
        // .instanceProperty("hasPersistingTrade", &ActorClass::hasPersistingTrade)
        // .instanceProperty("hasPlayerPassenger", &ActorClass::hasPlayerPassenger)
        // .instanceProperty("hasPriorityAmmunition", &ActorClass::hasPriorityAmmunition)
        .instanceProperty("hasRuntimeID", &ActorClass::hasRuntimeID)
        .instanceProperty("hasSaddle", &ActorClass::hasSaddle)
        // .instanceProperty("hasTags", &ActorClass::hasTags)
        // .instanceProperty("hasTeleported", &ActorClass::hasTeleported)
        // .instanceProperty("hasTotemEquipped", &ActorClass::hasTotemEquipped)
        .instanceProperty("hasUniqueID", &ActorClass::hasUniqueID)
        .instanceProperty("inDownwardFlowingLiquid", &ActorClass::inDownwardFlowingLiquid)
        .instanceProperty("isAdventure", &ActorClass::isAdventure)
        // .instanceProperty("isAffectedByWaterBottle", &ActorClass::isAffectedByWaterBottle)
        // .instanceProperty("isAngry", &ActorClass::isAngry)
        .instanceProperty("isAttackableGamemode", &ActorClass::isAttackableGamemode)
        .instanceProperty("isAutonomous", &ActorClass::isAutonomous)
        .instanceProperty("isBaby", &ActorClass::isBaby)
        // .instanceProperty("isBodyRotationBlocked", &ActorClass::isBodyRotationBlocked)
        // .instanceProperty("isBreakingObstruction", &ActorClass::isBreakingObstruction)
        // .instanceProperty("isBribed", &ActorClass::isBribed)
        // .instanceProperty("isCharged", &ActorClass::isCharged)
        .instanceProperty("isChested", &ActorClass::isChested)
        .instanceProperty("isClientSide", &ActorClass::isClientSide)
        // .instanceProperty("isClimbing", &ActorClass::isClimbing)
        .instanceProperty("isControlledByLocalInstance", &ActorClass::isControlledByLocalInstance)
        .instanceProperty("isCreative", &ActorClass::isCreative)
        .instanceProperty("isDancing", &ActorClass::isDancing)
        .instanceProperty("isDead", &ActorClass::isDead)
        // .instanceProperty("isDoorBreaker", &ActorClass::isDoorBreaker)
        .instanceProperty("isDoorOpener", &ActorClass::isDoorOpener)
        .instanceProperty("isGlobal", &ActorClass::isGlobal)
        // .instanceProperty("isIgnited", &ActorClass::isIgnited)
        // .instanceProperty("isImmersedInWater", &ActorClass::isImmersedInWater)
        .instanceProperty("isInClouds", &ActorClass::isInClouds)
        // .instanceProperty("isInContactWithWater", &ActorClass::isInContactWithWater)
        .instanceProperty("isInLava", &ActorClass::isInLava)
        .instanceProperty("isInLove", &ActorClass::isInLove)
        .instanceProperty("isInPrecipitation", &ActorClass::isInPrecipitation)
        .instanceProperty("isInRain", &ActorClass::isInRain)
        // .instanceProperty("isInScaffolding", &ActorClass::isInScaffolding)
        .instanceProperty("isInSnow", &ActorClass::isInSnow)
        .instanceProperty("isInThunderstorm", &ActorClass::isInThunderstorm)
        .instanceProperty("isInWater", &ActorClass::isInWater)
        .instanceProperty("isInWaterOrRain", &ActorClass::isInWaterOrRain)
        .instanceProperty("isInWorld", &ActorClass::isInWorld)
        // .instanceProperty("isInsidePortal", &ActorClass::isInsidePortal)
        // .instanceProperty("isInvertedHealAndHarm", &ActorClass::isInvertedHealAndHarm)
        .instanceProperty("isJumping", &ActorClass::isJumping)
        // .instanceProperty("isLayingDown", &ActorClass::isLayingDown)
        .instanceProperty("isLeashed", &ActorClass::isLeashed)
        .instanceProperty("isLocalPlayer", &ActorClass::isLocalPlayer)
        // .instanceProperty("isMovedToLimbo", &ActorClass::isMovedToLimbo)
        // .instanceProperty("isMovedToUnloadedChunk", &ActorClass::isMovedToUnloadedChunk)
        // .instanceProperty("isMoving", &ActorClass::isMoving)
        // .instanceProperty("isOrphan", &ActorClass::isOrphan)
        // .instanceProperty("isOutOfControl", &ActorClass::isOutOfControl)
        // .instanceProperty("isOverScaffolding", &ActorClass::isOverScaffolding)
        .instanceProperty("isOverWater", &ActorClass::isOverWater)
        // .instanceProperty("isPacified", &ActorClass::isPacified)
        .instanceProperty("isPersistent", &ActorClass::isPersistent)
        .instanceProperty("isPlayer", &ActorClass::isPlayer)
        // .instanceProperty("isPlayingDead", &ActorClass::isPlayingDead)
        // .instanceProperty("isPowered", &ActorClass::isPowered)
        .instanceProperty("isRemotePlayer", &ActorClass::isRemotePlayer)
        // .instanceProperty("isRemoved", &ActorClass::isRemoved)
        // .instanceProperty("isResting", &ActorClass::isResting)
        // .instanceProperty("isSheared", &ActorClass::isSheared)
        // .instanceProperty("isSilent", &ActorClass::isSilent)
        .instanceProperty("isSitting", &ActorClass::isSitting)
        // .instanceProperty("isSneaking", &ActorClass::isSneaking)
        .instanceProperty("isSpectator", &ActorClass::isSpectator)
        // .instanceProperty("isStanding", &ActorClass::isStanding)
        .instanceProperty("isSurvival", &ActorClass::isSurvival)
        // .instanceProperty("isSwimmer", &ActorClass::isSwimmer)
        .instanceProperty("isSwimming", &ActorClass::isSwimming)
        .instanceProperty("isTame", &ActorClass::isTame)
        // .instanceProperty("isTickingEntity", &ActorClass::isTickingEntity)
        .instanceProperty("isTouchingDamageBlock", &ActorClass::isTouchingDamageBlock)
        .instanceProperty("isTrading", &ActorClass::isTrading)
        // .instanceProperty("isTrusting", &ActorClass::isTrusting)
        // .instanceProperty("isUseNewTradeScreen", &ActorClass::isUseNewTradeScreen)
        // .instanceProperty("isWalker", &ActorClass::isWalker)
        .instanceProperty("isWearingLeatherArmor", &ActorClass::isWearingLeatherArmor)
        .instanceProperty("isWorldBuilder", &ActorClass::isWorldBuilder)

        .InstanceFunction(getEntityContext, ActorClass)
        .InstanceFunction(refresh, ActorClass)
        .InstanceFunction(clone, ActorClass)
        .InstanceFunction(getFeetPos, ActorClass)
        .InstanceFunction(getHeadPos, ActorClass)
        .InstanceFunction(getFeetBlockPos, ActorClass)
        .InstanceFunction(setOnFire, ActorClass)
        .InstanceFunction(stopFire, ActorClass)
        .InstanceFunction(getPosDeltaPerSecLength, ActorClass)
        .InstanceFunction(hurtByCause, ActorClass)
        .InstanceFunction(traceRay, ActorClass)
        .InstanceFunction(teleport, ActorClass)
        .InstanceFunction(setName, ActorClass)
        .InstanceFunction(evalMolang, ActorClass)
        // .InstanceFunction(hasComponent, ActorClass)
        .InstanceFunction(outOfWorld, ActorClass)
        // .InstanceFunction(reloadHardcoded, ActorClass)
        // .InstanceFunction(reloadHardcodedClient, ActorClass)
        // .InstanceFunction(initializeComponents, ActorClass)
        // .InstanceFunction(reloadComponents, ActorClass)
        .InstanceFunction(resetUserPos, ActorClass)
        .InstanceFunction(getOwnerEntityType, ActorClass)
        .InstanceFunction(remove, ActorClass)
        .InstanceFunction(getFiringPos, ActorClass)
        .InstanceFunction(getInterpolatedBodyRot, ActorClass)
        .InstanceFunction(getInterpolatedHeadRot, ActorClass)
        .InstanceFunction(getInterpolatedBodyYaw, ActorClass)
        .InstanceFunction(getYawSpeedInDegreesPerSecond, ActorClass)
        .InstanceFunction(getInterpolatedRidingOffset, ActorClass)
        .InstanceFunction(blockedByShield, ActorClass)
        .InstanceFunction(teleportTo, ActorClass)
        .InstanceFunction(lerpMotion, ActorClass)
        // .InstanceFunction(tryCreateAddActorPacket, ActorClass)
        .InstanceFunction(normalTick, ActorClass)
        .InstanceFunction(baseTick, ActorClass)
        .InstanceFunction(passengerTick, ActorClass)
        .InstanceFunction(startRiding, ActorClass)
        .InstanceFunction(addPassenger, ActorClass)
        .InstanceFunction(getExitTip, ActorClass)
        //        .InstanceFunction(getNameTagTextColor, ActorClass)
        .InstanceFunction(getHeadLookVector, ActorClass)
        .InstanceFunction(getBrightness, ActorClass)
        .InstanceFunction(playerTouch, ActorClass)
        .InstanceFunction(setSleeping, ActorClass)
        .InstanceFunction(setSneaking, ActorClass)
        .InstanceFunction(isDamageBlocked, ActorClass)
        .InstanceFunction(setTarget, ActorClass)
        .InstanceFunction(isValidTarget, ActorClass)
        .InstanceFunction(attack, ActorClass)
        .InstanceFunction(performRangedAttack, ActorClass)
        .InstanceFunction(setOwner, ActorClass)
        .InstanceFunction(setSitting, ActorClass)
        .InstanceFunction(onTame, ActorClass)
        .InstanceFunction(onFailedTame, ActorClass)
        .InstanceFunction(setStanding, ActorClass)
        //        .InstanceFunction(playAmbientSound, ActorClass)
        .InstanceFunction(getAmbientSound, ActorClass)
        .InstanceFunction(isInvulnerableTo, ActorClass)
        .InstanceFunction(getBlockDamageCause, ActorClass)
        .InstanceFunction(doFireHurt, ActorClass)
        .InstanceFunction(onLightningHit, ActorClass)
        .InstanceFunction(feed, ActorClass)
        .InstanceFunction(handleEntityEvent, ActorClass)
        //        .InstanceFunction(getActorRendererId, ActorClass)
        //        .InstanceFunction(despawn, ActorClass)
        //        .InstanceFunction(setArmor, ActorClass)
        //        .InstanceFunction(getArmorMaterialTypeInSlot, ActorClass)
        //        .InstanceFunction(getArmorTextureIndexInSlot, ActorClass)
        //        .InstanceFunction(getArmorColorInSlot, ActorClass)
        //        .InstanceFunction(setEquippedSlot, ActorClass)
        //        .InstanceFunction(setCarriedItem, ActorClass)
        //        .InstanceFunction(getCarriedItem, ActorClass)
        //        .InstanceFunction(setOffhandSlot, ActorClass)
        //        .InstanceFunction(getEquippedTotem, ActorClass)
        //        .InstanceFunction(load, ActorClass)
        //        .InstanceFunction(queryEntityRenderer, ActorClass)
        //        .InstanceFunction(getSourceUniqueID, ActorClass)
        //        .InstanceFunction(getLiquidAABB, ActorClass)
        //        .InstanceFunction(handleInsidePortal, ActorClass)
        //        .InstanceFunction(changeDimension, ActorClass)
        //        .InstanceFunction(getControllingPlayer, ActorClass)
        //        .InstanceFunction(causeFallDamageToActor, ActorClass)
        //        .InstanceFunction(onSynchedDataUpdate, ActorClass)
        //        .InstanceFunction(canAddPassenger, ActorClass)
        //        .InstanceFunction(canPickupItem, ActorClass)
        //        .InstanceFunction(sendMotionPacketIfNeeded, ActorClass)
        //        .InstanceFunction(buildDebugInfo, ActorClass)
        //        .InstanceFunction(getCommandPermissionLevel, ActorClass)
        //        .InstanceFunction(canBeAffected, ActorClass)
        //        .InstanceFunction(canBeAffectedByArrow, ActorClass)
        //        .InstanceFunction(onEffectRemoved, ActorClass)
        //        .InstanceFunction(getAnimationComponent, ActorClass)
        //        .InstanceFunction(openContainerComponent, ActorClass)
        //        .InstanceFunction(swing, ActorClass)
        //        .InstanceFunction(useItem, ActorClass)
        //        .InstanceFunction(getDebugText, ActorClass)
        //        .InstanceFunction(getPassengerYRotation, ActorClass)
        //        .InstanceFunction(add, ActorClass)
        //        .InstanceFunction(drop, ActorClass)
        //        .InstanceFunction(getInteraction, ActorClass)
        //        .InstanceFunction(canDestroyBlock, ActorClass)
        //        .InstanceFunction(setAuxValue, ActorClass)
        //        .InstanceFunction(renderDebugServerState, ActorClass)
        //        .InstanceFunction(die, ActorClass)
        //        .InstanceFunction(applySnapshot, ActorClass)
        //        .InstanceFunction(getNextStep, ActorClass)
        //        .InstanceFunction(onPush, ActorClass)
        //        .InstanceFunction(getLastDeathPos, ActorClass)
        //        .InstanceFunction(getLastDeathDimension, ActorClass)
        //        .InstanceFunction(doEnterWaterSplashEffect, ActorClass)
        //        .InstanceFunction(doExitWaterSplashEffect, ActorClass)
        //        .InstanceFunction(doWaterSplashEffect, ActorClass)
        //        .InstanceFunction(readAdditionalSaveData, ActorClass)
        //        .InstanceFunction(addAdditionalSaveData, ActorClass)
        //        .InstanceFunction(addCategory, ActorClass)
        //        .InstanceFunction(addDefinitionGroup, ActorClass)
        //        .InstanceFunction(addEffect, ActorClass)
        //        .InstanceFunction(addTag, ActorClass)
        //        .InstanceFunction(applyImpulse, ActorClass)
        //        .InstanceFunction(buildDebugGroupInfo, ActorClass)
        //        .InstanceFunction(buildForward, ActorClass)
        //        .InstanceFunction(burn, ActorClass)
        //        .InstanceFunction(calcCenterPos, ActorClass)
        //        .InstanceFunction(calculateAttackDamage, ActorClass)
        //        .InstanceFunction(canAttack, ActorClass)
        //        .InstanceFunction(canSee, ActorClass)
        //        .InstanceFunction(celebrateHunt, ActorClass)
        //        .InstanceFunction(checkFallDamage, ActorClass)
        //        .InstanceFunction(chorusFruitTeleport, ActorClass)
        //        .InstanceFunction(clearFishingHookID, ActorClass)
        //        .InstanceFunction(closerThan, ActorClass)
        //        .InstanceFunction(consumeItem, ActorClass)
        //        .InstanceFunction(createUpdateEquipPacket, ActorClass)
        //        .InstanceFunction(createUpdateTradePacket, ActorClass)
        //        .InstanceFunction(deregisterTagsFromLevelCache, ActorClass)
        //        .InstanceFunction(distanceSqrToBlockPosCenter, ActorClass)
        //        .InstanceFunction(distanceTo, ActorClass)
        //        .InstanceFunction(distanceToSqr, ActorClass)
        //        .InstanceFunction(dropLeash, ActorClass)
        //        .InstanceFunction(dropTowards, ActorClass)
        //        .InstanceFunction(enableAutoSendPosRot, ActorClass)
        //        .InstanceFunction(equip, ActorClass)
        //        .InstanceFunction(equipFromEquipmentDefinition, ActorClass)
        //        .InstanceFunction(evaluateSeatRotation, ActorClass)
        //        .InstanceFunction(executeEvent, ActorClass)
        //        .InstanceFunction(exitVehicle, ActorClass)
        //        .InstanceFunction(fetchFishingHook, ActorClass)
        //        .InstanceFunction(fetchNearbyActorsSorted, ActorClass)
        //        .InstanceFunction(forEachLeashedActor, ActorClass)
        //        .InstanceFunction(getAABB, ActorClass)
        //        .InstanceFunction(getAABBDim, ActorClass)
        //        .InstanceFunction(getActorIdentifier, ActorClass)
        //        .InstanceFunction(getAllEffects, ActorClass)
        //        .InstanceFunction(getArmor, ActorClass)
        //        .InstanceFunction(getAttachPos, ActorClass)
        //        .InstanceFunction(getAttribute, ActorClass)
        //        .InstanceFunction(getAttributes, ActorClass)
        //        .InstanceFunction(getBlockPosCurrentlyStandingOn, ActorClass)
        //        .InstanceFunction(getBlockTarget, ActorClass)
        //        .InstanceFunction(getBlockWhenClimbing, ActorClass)
        //        .InstanceFunction(getCarriedItemInSlotPreferredBy, ActorClass)
        //        .InstanceFunction(getCategories, ActorClass)
        //        .InstanceFunction(getColor, ActorClass)
        //        .InstanceFunction(getColor2, ActorClass)
        //        .InstanceFunction(getDiffListNonConst, ActorClass)
        //        .InstanceFunction(getDimension, ActorClass)
        //        .InstanceFunction(getDimensionBlockSource, ActorClass)
        //        .InstanceFunction(getDimensionBlockSourceConst, ActorClass)
        //        .InstanceFunction(getDimensionConst, ActorClass)
        //        .InstanceFunction(getDimensionId, ActorClass)
        //        .InstanceFunction(getEffect, ActorClass)
        //        .InstanceFunction(getEntityData, ActorClass)
        //        .InstanceFunction(getEntityRegistry, ActorClass)
        //        .InstanceFunction(getEntityTerrainInterlockData, ActorClass)
        //        .InstanceFunction(getEntityTypeId, ActorClass)
        //        .InstanceFunction(getEquipmentSlotForItem, ActorClass)
        //        .InstanceFunction(getEyePos, ActorClass)
        //        .InstanceFunction(getFirstAvailableSeatPos, ActorClass)
        //        .InstanceFunction(getFirstPassenger, ActorClass)
        //        .InstanceFunction(getILevel, ActorClass)
        //        .InstanceFunction(getInitializationMethod, ActorClass)
        //        .InstanceFunction(getInterpolatedPosition, ActorClass)
        //        .InstanceFunction(getInterpolatedRidingPosition, ActorClass)
        //        .InstanceFunction(getInterpolatedRotation, ActorClass)
        //        .InstanceFunction(getLastHurtByMob, ActorClass)
        //        .InstanceFunction(getLastHurtByMobID, ActorClass)
        //        .InstanceFunction(getLastHurtByPlayer, ActorClass)
        //        .InstanceFunction(getLastHurtByPlayerID, ActorClass)
        //        .InstanceFunction(getLastHurtCause, ActorClass)
        //        .InstanceFunction(getLastHurtMob, ActorClass)
        //        .InstanceFunction(getLeashHolder, ActorClass)
        //        .InstanceFunction(getLevel, ActorClass)
        //        .InstanceFunction(getLinks, ActorClass)
        //        .InstanceFunction(getLootTable, ActorClass)
        //        .InstanceFunction(getMolangVariables, ActorClass)
        //        .InstanceFunction(getMutableAttribute, ActorClass)
        //        .InstanceFunction(getOffhandSlot, ActorClass)
        //        .InstanceFunction(getOrAddDynamicProperties, ActorClass)
        //        .InstanceFunction(getOrCreateUniqueID, ActorClass)
        //        .InstanceFunction(getOwner, ActorClass)
        //        .InstanceFunction(getOwnerId, ActorClass)
        //        .InstanceFunction(getPassengerIndex, ActorClass)
        //        .InstanceFunction(getPersistingTradeOffers, ActorClass)
        //        .InstanceFunction(getPlayerOwner, ActorClass)
        //        .InstanceFunction(getPosDelta, ActorClass)
        //        .InstanceFunction(getPosDeltaNonConst, ActorClass)
        //        .InstanceFunction(getPosPrev, ActorClass)
        //        .InstanceFunction(getPosition, ActorClass)
        //        .InstanceFunction(getRandom, ActorClass)
        //        .InstanceFunction(getRenderParams, ActorClass)
        //        .InstanceFunction(getRotation, ActorClass)
        //        .InstanceFunction(getRotationPrev, ActorClass)
        //        .InstanceFunction(getRuntimeID, ActorClass)
        //        .InstanceFunction(getSpatialNetworkData, ActorClass)
        //        .InstanceFunction(getStatusFlag, ActorClass)
        //        .InstanceFunction(getSwimAmount, ActorClass)
        //        .InstanceFunction(getTags, ActorClass)
        //        .InstanceFunction(getTarget, ActorClass)
        //        .InstanceFunction(getTargetId, ActorClass)
        //        .InstanceFunction(getTradeOffers, ActorClass)
        //        .InstanceFunction(getTradingPlayer, ActorClass)
        //        .InstanceFunction(getVehicle, ActorClass)
        //        .InstanceFunction(getVehicleRoot, ActorClass)
        //        .InstanceFunction(getVehicleRuntimeID, ActorClass)
        //        .InstanceFunction(getViewVector, ActorClass)
        //        .InstanceFunction(getWeakEntity, ActorClass)
        //        .InstanceFunction(getYHeadRotationsNewOld, ActorClass)
        //        .InstanceFunction(handleFallDamage, ActorClass)
        //        .InstanceFunction(handleLeftoverFallDamage, ActorClass)
        //        .InstanceFunction(hasBeenHurtByMobInLastTicks, ActorClass)
        //        .InstanceFunction(hasCategory, ActorClass)
        //        .InstanceFunction(hasDefinitionGroup, ActorClass)
        //        .InstanceFunction(hasEffect, ActorClass)
        //        .InstanceFunction(hasFamily, ActorClass)
        //        .InstanceFunction(hasTag, ActorClass)
        //        .InstanceFunction(hasType, ActorClass)
        //        .InstanceFunction(heal, ActorClass)
        //        .InstanceFunction(healEffects, ActorClass)
        //        .InstanceFunction(hurt, ActorClass)
        //        .InstanceFunction(initParams, ActorClass)
        //        .InstanceFunction(intersects, ActorClass)
        //        .InstanceFunction(isActorLocationInMaterial, ActorClass)
        //        .InstanceFunction(isRiding, ActorClass)
        //        .InstanceFunction(isType, ActorClass)
        //        .InstanceFunction(isUnderLiquid, ActorClass)
        //        .InstanceFunction(killed, ActorClass)
        //        .InstanceFunction(lerpTo, ActorClass)
        //        .InstanceFunction(loadEntityFlags, ActorClass)
        //        .InstanceFunction(loadLinks, ActorClass)
        //        .InstanceFunction(lovePartnerId, ActorClass)
        //        .InstanceFunction(markHurt, ActorClass)
        //        .InstanceFunction(migrateUniqueID, ActorClass)
        //        .InstanceFunction(move, ActorClass)
        //        .InstanceFunction(moveRelative, ActorClass)
        //        .InstanceFunction(moveTo, ActorClass)
        //        .InstanceFunction(onAffectedByWaterBottle, ActorClass)
        //        .InstanceFunction(onClimbableBlock, ActorClass)
        //        .InstanceFunction(onOrphan, ActorClass)
        //        .InstanceFunction(pickUpItem, ActorClass)
        //        .InstanceFunction(playSound, ActorClass)
        //        .InstanceFunction(playSynchronizedSound, ActorClass)
        //        .InstanceFunction(positionAllPassengers, ActorClass)
        //        .InstanceFunction(postGameEvent, ActorClass)
        //        .InstanceFunction(postSplashGameEvent, ActorClass)
        //        .InstanceFunction(pullInEntity, ActorClass)
        //        .InstanceFunction(pushBackActionEventToActionQueue, ActorClass)
        //        .InstanceFunction(pushOutOfBlocks, ActorClass)
        //        .InstanceFunction(queueBBUpdateFromDefinition, ActorClass)
        //        .InstanceFunction(queueBBUpdateFromValue, ActorClass)
        //        .InstanceFunction(refreshComponents, ActorClass)
        //        .InstanceFunction(reload, ActorClass)
        //        .InstanceFunction(removeAllEffects, ActorClass)
        //        .InstanceFunction(removeAllPassengers, ActorClass)
        //        .InstanceFunction(removeDefinitionGroup, ActorClass)
        //        .InstanceFunction(removeEffect, ActorClass)
        //        .InstanceFunction(removePersistingTrade, ActorClass)
        //        .InstanceFunction(save, ActorClass)
        //        .InstanceFunction(saveEntityFlags, ActorClass)
        //        .InstanceFunction(saveLinks, ActorClass)
        //        .InstanceFunction(savePersistingTrade, ActorClass)
        //        .InstanceFunction(saveWithoutId, ActorClass)
        //        .InstanceFunction(sendActorDefinitionEventTriggered, ActorClass)
        //        .InstanceFunction(serializationSetHealth, ActorClass)
        //        .InstanceFunction(setAABB, ActorClass)
        //        .InstanceFunction(setAABBDim, ActorClass)
        //        .InstanceFunction(setActorRendererId, ActorClass)
        //        .InstanceFunction(setAutonomous, ActorClass)
        //        .InstanceFunction(setBaseDefinition, ActorClass)
        //        .InstanceFunction(setBlockTarget, ActorClass)
        //        .InstanceFunction(setBodyRotationBlocked, ActorClass)
        //        .InstanceFunction(setBreakingObstruction, ActorClass)
        //        .InstanceFunction(setCanClimb, ActorClass)
        //        .InstanceFunction(setCanFly, ActorClass)
        //        .InstanceFunction(setCanPowerJump, ActorClass)
        //        .InstanceFunction(setChainedDamageEffects, ActorClass)
        //        .InstanceFunction(setCharged, ActorClass)
        //        .InstanceFunction(setClimbing, ActorClass)
        //        .InstanceFunction(setColor, ActorClass)
        //        .InstanceFunction(setColor2, ActorClass)
        //        .InstanceFunction(setDancing, ActorClass)
        //        .InstanceFunction(setDead, ActorClass)
        //        .InstanceFunction(setDimension, ActorClass)
        //        .InstanceFunction(setDoorBreaker, ActorClass)
        //        .InstanceFunction(setDoorOpener, ActorClass)
        //        .InstanceFunction(setEnchanted, ActorClass)
        //        .InstanceFunction(setFallDistance, ActorClass)
        //        .InstanceFunction(setFishingHookID, ActorClass)
        //        .InstanceFunction(setGlobal, ActorClass)
        //        .InstanceFunction(setHurtDir, ActorClass)
        //        .InstanceFunction(setHurtTime, ActorClass)
        //        .InstanceFunction(setInLove, ActorClass)
        //        .InstanceFunction(setInterpolation, ActorClass)
        //        .InstanceFunction(setIsExperienceDropEnabled, ActorClass)
        //        .InstanceFunction(setJumping, ActorClass)
        //        .InstanceFunction(setLastHitBB, ActorClass)
        //        .InstanceFunction(setLastHurtByMob, ActorClass)
        //        .InstanceFunction(setLastHurtByPlayer, ActorClass)
        //        .InstanceFunction(setLastHurtMob, ActorClass)
        //        .InstanceFunction(setLayingDown, ActorClass)
        //        .InstanceFunction(setLeashHolder, ActorClass)
        //        .InstanceFunction(setLimitedLifetimeTicks, ActorClass)
        //        .InstanceFunction(setMarkVariant, ActorClass)
        //        .InstanceFunction(setMovedToLimbo, ActorClass)
        //        .InstanceFunction(setMovedToUnloadedChunk, ActorClass)
        //        .InstanceFunction(setMovementSoundDistanceOffset, ActorClass)
        //        .InstanceFunction(setMoving, ActorClass)
        //        .InstanceFunction(setNameTag, ActorClass)
        //        .InstanceFunction(setNameTagVisible, ActorClass)
        //        .InstanceFunction(setObstructsBlockPlacement, ActorClass)
        //        .InstanceFunction(setPersistent, ActorClass)
        //        .InstanceFunction(setPos, ActorClass)
        //        .InstanceFunction(setPosDelta, ActorClass)
        //        .InstanceFunction(setPosDirectLegacy, ActorClass)
        //        .InstanceFunction(setPosPrev, ActorClass)
        //        .InstanceFunction(setPrevPosRotSetThisTick, ActorClass)
        //        .InstanceFunction(setPreviousPosRot, ActorClass)
        //        .InstanceFunction(setResting, ActorClass)
        //        .InstanceFunction(setRotationDirectly, ActorClass)
        //        .InstanceFunction(setRotationPrev, ActorClass)
        //        .InstanceFunction(setRotationPrevY, ActorClass)
        //        .InstanceFunction(setRotationWrapped, ActorClass)
        //        .InstanceFunction(setRotationX, ActorClass)
        //        .InstanceFunction(setRotationY, ActorClass)
        //        .InstanceFunction(setRuntimeID, ActorClass)
        //        .InstanceFunction(setSaddle, ActorClass)
        //        .InstanceFunction(setScared, ActorClass)
        //        .InstanceFunction(setScoreTag, ActorClass)
        //        .InstanceFunction(setShakeTime, ActorClass)
        //        .InstanceFunction(setSkinID, ActorClass)
        //        .InstanceFunction(setStatusFlag, ActorClass)
        //        .InstanceFunction(setStrength, ActorClass)
        //        .InstanceFunction(setStrengthMax, ActorClass)
        //        .InstanceFunction(setStructuralIntegrity, ActorClass)
        //        .InstanceFunction(setStunned, ActorClass)
        //        .InstanceFunction(setSwimmer, ActorClass)
        //        .InstanceFunction(setTempted, ActorClass)
        //        .InstanceFunction(setTradeInterest, ActorClass)
        //        .InstanceFunction(setTradingPlayer, ActorClass)
        //        .InstanceFunction(setUniqueID, ActorClass)
        //        .InstanceFunction(setVariant, ActorClass)
        //        .InstanceFunction(setVelocity, ActorClass)
        //        .InstanceFunction(setWASDControlled, ActorClass)
        //        .InstanceFunction(setWalker, ActorClass)
        //        .InstanceFunction(setYHeadRot, ActorClass)
        //        .InstanceFunction(setYHeadRotations, ActorClass)
        //        .InstanceFunction(shouldOrphan, ActorClass)
        //        .InstanceFunction(shouldTick, ActorClass)
        //        .InstanceFunction(shouldUpdateEffects, ActorClass)
        //        .InstanceFunction(spawnAtLocation, ActorClass)
        //        .InstanceFunction(spawnEatParticles, ActorClass)
        //        .InstanceFunction(spawnTrailBubbles, ActorClass)
        //        .InstanceFunction(stopRiding, ActorClass)
        //        .InstanceFunction(synchronousSetSize, ActorClass)
        //        .InstanceFunction(teleportPassengersTo, ActorClass)
        //        .InstanceFunction(thawFreezeEffect, ActorClass)
        //        .InstanceFunction(tick, ActorClass)
        //        .InstanceFunction(tickBlockDamage, ActorClass)
        //        .InstanceFunction(transferTickingArea, ActorClass)
        //        .InstanceFunction(triggerActorRemovedEvent, ActorClass)
        //        .InstanceFunction(tryGetEquippableSlotAllowedItems, ActorClass)
        //        .InstanceFunction(tryGetEquippableSlotForItem, ActorClass)
        //        .InstanceFunction(tryTeleportTo, ActorClass)
        //        .InstanceFunction(updateAnimationComponentOnServer, ActorClass)
        //        .InstanceFunction(updateDescription, ActorClass)
        //        .InstanceFunction(updateDimensionChunkMove, ActorClass)
        //        .InstanceFunction(updateInsideBlock, ActorClass)
        //        .InstanceFunction(updateInvisibilityStatus, ActorClass)
        //        .InstanceFunction(updateMolangVariables, ActorClass)
        //        .InstanceFunction(updateTickingData, ActorClass)
        //        .InstanceFunction(updateWaterState, ActorClass)
        //        .InstanceFunction(useSaddle, ActorClass)
        //        .InstanceFunction(wasHurt, ActorClass)
        //        .InstanceFunction(wasLastHitByPlayer, ActorClass)
        //        .InstanceFunction(wobble, ActorClass)

        .build();


Local<Object> ActorClass::newActor(Actor *actor) { return (new ActorClass(actor))->getScriptObject(); }

#define CallFunction(Type, Function)                                                                                   \
    try {                                                                                                              \
        if (!mActor) return Local<Value>();                                                                            \
        return Type::new##Type(mActor->Function);                                                                      \
    }                                                                                                                  \
    Catch;


/* Members */
Local<Value> ActorClass::typeName() { CallFunction(String, getTypeName()) };
Local<Value> ActorClass::isOnGround() { CallFunction(Boolean, isOnGround()) };
Local<Value> ActorClass::posDeltaPerSecLength() { CallFunction(Number, getPosDeltaPerSecLength()) };
Local<Value> ActorClass::isFireImmune() { CallFunction(Boolean, isFireImmune()) };
Local<Value> ActorClass::canDisableShield() { CallFunction(Boolean, canDisableShield()) };
Local<Value> ActorClass::entityLocNameString() { CallFunction(String, getEntityLocNameString()) };
// Local<Value> ActorClass::isInWall() { CallFunction(Boolean, isInWall()) };
Local<Value> ActorClass::isInvisible() { CallFunction(Boolean, isInvisible()) };
Local<Value> ActorClass::canShowNameTag() { CallFunction(Boolean, canShowNameTag()) };
Local<Value> ActorClass::formattedNameTag() { CallFunction(String, getFormattedNameTag()) };
Local<Value> ActorClass::shadowRadius() { CallFunction(Number, getShadowRadius()) };

Local<Value> ActorClass::canInteractWithOtherEntitiesInGame() {
    CallFunction(Boolean, canInteractWithOtherEntitiesInGame())
};
Local<Value> ActorClass::isSilentObserver() { CallFunction(Boolean, isSilentObserver()) };
Local<Value> ActorClass::isSleeping() { CallFunction(Boolean, isSleeping()) };
Local<Value> ActorClass::isBlocking() { CallFunction(Boolean, isBlocking()) };
Local<Value> ActorClass::isAlive() { CallFunction(Boolean, isAlive()) }

Local<Value> ActorClass::isOnFire() {
    CallFunction(Boolean, isOnFire())
};
Local<Value> ActorClass::isSurfaceMob() { CallFunction(Boolean, isSurfaceMob()) };
Local<Value> ActorClass::isTargetable() { CallFunction(Boolean, isTargetable()) };
Local<Value> ActorClass::canPowerJump() { CallFunction(Boolean, canPowerJump()) };
Local<Value> ActorClass::isEnchanted() { CallFunction(Boolean, isEnchanted()) };
// Local<Value> ActorClass::shouldRender(){CallFunction(Boolean, shouldRender())} Local<Value> ActorClass::consumeTotem() {
//     CallFunction(Boolean, consumeTotem())
// };
Local<Value> ActorClass::canFreeze() { CallFunction(Boolean, canFreeze()) };
Local<Value> ActorClass::canChangeDimensionsUsingPortal() { CallFunction(Boolean, canChangeDimensionsUsingPortal()) };
Local<Value> ActorClass::canBePulledIntoVehicle() { CallFunction(Boolean, canBePulledIntoVehicle()) };
Local<Value> ActorClass::inCaravan() { CallFunction(Boolean, inCaravan()) };
Local<Value> ActorClass::canSynchronizeNewEntity() { CallFunction(Boolean, canSynchronizeNewEntity()) };
Local<Value> ActorClass::deathTime() { CallFunction(Number, getDeathTime()) };

Local<Value> ActorClass::canObstructSpawningAndBlockPlacement() {
    CallFunction(Boolean, canObstructSpawningAndBlockPlacement())
};
Local<Value> ActorClass::mapDecorationRotation() { CallFunction(Number, getMapDecorationRotation()) };
Local<Value> ActorClass::shouldDropDeathLoot() { CallFunction(Boolean, shouldDropDeathLoot()) };
Local<Value> ActorClass::hasDiedBefore() { CallFunction(Boolean, hasDiedBefore()) };
// Local<Value> ActorClass::shouldTryMakeStepSound() { CallFunction(Boolean, shouldTryMakeStepSound()) };

Local<Value> ActorClass::canBeginOrContinueClimbingLadder() {
    CallFunction(Boolean, canBeginOrContinueClimbingLadder())
};
Local<Value> ActorClass::canCurrentlySwim() { CallFunction(Boolean, canCurrentlySwim()) };
Local<Value> ActorClass::canFly() { CallFunction(Boolean, canFly()) };

Local<Value> ActorClass::canReceiveMobEffectsFromGameplay() {
    CallFunction(Boolean, canReceiveMobEffectsFromGameplay())
};
Local<Value> ActorClass::canSeeDaylight() { CallFunction(Boolean, canSeeDaylight()) };
// Local<Value> ActorClass::canPickupItems() { CallFunction(Boolean, getCanPickupItems()) };
// Local<Value> ActorClass::chainedDamageEffects() { CallFunction(Boolean, getChainedDamageEffects()) };
Local<Value> ActorClass::chestSlots() { CallFunction(Number, getChestSlots()) };
// Local<Value> ActorClass::collidableMob() { CallFunction(Number, getCollidableMob()) };
Local<Value> ActorClass::currentSwimAmount() { CallFunction(Number, getCurrentSwimAmount()) };
// Local<Value> ActorClass::damageNearbyMobs() { CallFunction(Number, getDamageNearbyMobs()) };
Local<Value> ActorClass::equipSlots() { CallFunction(Number, getEquipSlots()) };
// Local<Value> ActorClass::equipmentCount() { CallFunction(Number, getEquipmentCount()) };
Local<Value> ActorClass::fallDistance() { CallFunction(Number, getFallDistance()) };
// Local<Value> ActorClass::health() { CallFunction(Number, getHealth()) };
// Local<Value> ActorClass::hurtDir() { CallFunction(Number, getHurtDir()) };
// Local<Value> ActorClass::hurtTime() { CallFunction(Number, getHurtTime()) };
// Local<Value> ActorClass::inventorySize() { CallFunction(Number, getInventorySize()) };
// Local<Value> ActorClass::isExperienceDropEnabled() { CallFunction(Number, getIsExperienceDropEnabled()) };
// Local<Value> ActorClass::lastHurtByMobTime() { CallFunction(Number, getLastHurtByMobTime()) };
// Local<Value> ActorClass::lastHurtByMobTimestamp() { CallFunction(Number, getLastHurtByMobTimestamp()) };
// Local<Value> ActorClass::lastHurtDamage() { CallFunction(Number, getLastHurtDamage()) };
// Local<Value> ActorClass::lastHurtMobTimestamp() { CallFunction(Number, getLastHurtMobTimestamp()) };
// Local<Value> ActorClass::lastHurtTimestamp() { CallFunction(Number, getLastHurtTimestamp()) };
// Local<Value> ActorClass::levelTimeStamp() { CallFunction(Number, getLevelTimeStamp()) };
// Local<Value> ActorClass::limitedLifetimeTicks() { CallFunction(Number, getLimitedLifetimeTicks()) };
Local<Value> ActorClass::markVariant() { CallFunction(Number, getMarkVariant()) };
// Local<Value> ActorClass::maxAutoStep() { CallFunction(Number, getMaxAutoStep()) };
Local<Value> ActorClass::maxHealth() { CallFunction(Number, getMaxHealth()) };
Local<Value> ActorClass::nameTag() { CallFunction(String, getNameTag()) };
// Local<Value> ActorClass::nameTagAsHash() { CallFunction(Number, getNameTagAsHash()) };
// Local<Value> ActorClass::onDeathExperience() { CallFunction(Number, getOnDeathExperience()) };
// Local<Value> ActorClass::persistingTradeRiches() { CallFunction(Number, getPersistingTradeRiches()) };
// Local<Value> ActorClass::radius() { CallFunction(Number, getRadius()) };
Local<Value> ActorClass::ridingHeight() { CallFunction(Number, getRidingHeight()) };
// Local<Value> ActorClass::shakeTime() { CallFunction(Number, getShakeTime()) };
// Local<Value> ActorClass::skinID() { CallFunction(Number, getSkinID()) };
// Local<Value> ActorClass::speedInMetersPerSecond() { CallFunction(Number, getSpeedInMetersPerSecond()) };
Local<Value> ActorClass::strength() { CallFunction(Number, getStrength()) };
// Local<Value> ActorClass::strengthMax() { CallFunction(Number, getStrengthMax()) };
// Local<Value> ActorClass::tradeInterest() { CallFunction(Number, getTradeInterest()) };
Local<Value> ActorClass::variant() { CallFunction(Number, getVariant()) };
// Local<Value> ActorClass::verticalSpeedInMetersPerSecond() { CallFunction(Number, getVerticalSpeedInMetersPerSecond()) };
// Local<Value> ActorClass::yHeadRot() { CallFunction(Number, getYHeadRot()) };
// Local<Value> ActorClass::hasAnyEffects() { CallFunction(Number, hasAnyEffects()) };
// Local<Value> ActorClass::hasDimension() { CallFunction(Number, hasDimension()) };
// Local<Value> ActorClass::hasFishingHook() { CallFunction(Number, hasFishingHook()) };
// Local<Value> ActorClass::hasLevel() { CallFunction(Number, hasLevel()) };
// Local<Value> ActorClass::hasPassenger() { CallFunction(Number, hasPassenger()) };
// Local<Value> ActorClass::hasPersistingTrade() { CallFunction(Number, hasPersistingTrade()) };
// Local<Value> ActorClass::hasPlayerPassenger() { CallFunction(Number, hasPlayerPassenger()) };
// Local<Value> ActorClass::hasPriorityAmmunition() { CallFunction(Number, hasPriorityAmmunition()) };
Local<Value> ActorClass::hasRuntimeID() { CallFunction(Number, hasRuntimeID()) };
Local<Value> ActorClass::hasSaddle() { CallFunction(Number, hasSaddle()) };
// Local<Value> ActorClass::hasTags() { CallFunction(Number, hasTags()) };
// Local<Value> ActorClass::hasTeleported() { CallFunction(Number, hasTeleported()) };
// Local<Value> ActorClass::hasTotemEquipped() { CallFunction(Number, hasTotemEquipped()) };
Local<Value> ActorClass::hasUniqueID() { CallFunction(Number, hasUniqueID()) };
Local<Value> ActorClass::inDownwardFlowingLiquid() { CallFunction(Number, inDownwardFlowingLiquid()) };
Local<Value> ActorClass::isAdventure() { CallFunction(Boolean, isAdventure()); }
// Local<Value> ActorClass::isAffectedByWaterBottle() { CallFunction(Number, isAffectedByWaterBottle()) };
// Local<Value> ActorClass::isAngry() { CallFunction(Number, isAngry()) };
Local<Value> ActorClass::isAttackableGamemode() { CallFunction(Number, isAttackableGamemode()) };
Local<Value> ActorClass::isAutonomous() { CallFunction(Number, isAutonomous()) };
Local<Value> ActorClass::isBaby() { CallFunction(Number, isBaby()) };
// Local<Value> ActorClass::isBodyRotationBlocked() { CallFunction(Number, isBodyRotationBlocked()) };
// Local<Value> ActorClass::isBreakingObstruction() { CallFunction(Number, isBreakingObstruction()) };
// Local<Value> ActorClass::isBribed() { CallFunction(Number, isBribed()) };
// Local<Value> ActorClass::isCharged() { CallFunction(Number, isCharged()) };
Local<Value> ActorClass::isChested() { CallFunction(Number, isChested()) };
Local<Value> ActorClass::isClientSide() { CallFunction(Number, isClientSide()) };
// Local<Value> ActorClass::isClimbing() { CallFunction(Number, isClimbing()) };
Local<Value> ActorClass::isControlledByLocalInstance() { CallFunction(Number, isControlledByLocalInstance()) };
Local<Value> ActorClass::isCreative() { CallFunction(Number, isCreative()) };
Local<Value> ActorClass::isDancing() { CallFunction(Number, isDancing()) };
Local<Value> ActorClass::isDead() { CallFunction(Number, isDead()) };
// Local<Value> ActorClass::isDoorBreaker() { CallFunction(Number, isDoorBreaker()) };
Local<Value> ActorClass::isDoorOpener() { CallFunction(Number, isDoorOpener()) };
Local<Value> ActorClass::isGlobal() { CallFunction(Number, isGlobal()) };
// Local<Value> ActorClass::isIgnited() { CallFunction(Number, isIgnited()) };
// Local<Value> ActorClass::isImmersedInWater() { CallFunction(Number, isImmersedInWater()) };
Local<Value> ActorClass::isInClouds() { CallFunction(Number, isInClouds()) };
// Local<Value> ActorClass::isInContactWithWater() { CallFunction(Number, isInContactWithWater()) };
Local<Value> ActorClass::isInLava() { CallFunction(Number, isInLava()) };
Local<Value> ActorClass::isInLove() { CallFunction(Number, isInLove()) };
Local<Value> ActorClass::isInPrecipitation() { CallFunction(Number, isInPrecipitation()) };
Local<Value> ActorClass::isInRain() { CallFunction(Number, isInRain()) };
// Local<Value> ActorClass::isInScaffolding() { CallFunction(Number, isInScaffolding()) };
Local<Value> ActorClass::isInSnow() { CallFunction(Number, isInSnow()) };
Local<Value> ActorClass::isInThunderstorm() { CallFunction(Number, isInThunderstorm()) };
Local<Value> ActorClass::isInWater() { CallFunction(Number, isInWater()) };
Local<Value> ActorClass::isInWaterOrRain() { CallFunction(Number, isInWaterOrRain()) };
Local<Value> ActorClass::isInWorld() { CallFunction(Number, isInWorld()) };
// Local<Value> ActorClass::isInsidePortal() { CallFunction(Number, isInsidePortal()) };
// Local<Value> ActorClass::isInvertedHealAndHarm() { CallFunction(Number, isInvertedHealAndHarm()) };
Local<Value> ActorClass::isJumping() { CallFunction(Number, isJumping()) };
// Local<Value> ActorClass::isLayingDown() { CallFunction(Number, isLayingDown()) };
Local<Value> ActorClass::isLeashed() { CallFunction(Number, isLeashed()) };
Local<Value> ActorClass::isLocalPlayer() { CallFunction(Number, isLocalPlayer()) };
// Local<Value> ActorClass::isMovedToLimbo() { CallFunction(Number, isMovedToLimbo()) };
// Local<Value> ActorClass::isMovedToUnloadedChunk() { CallFunction(Number, isMovedToUnloadedChunk()) };
// Local<Value> ActorClass::isMoving() { CallFunction(Number, isMoving()) };
// Local<Value> ActorClass::isOrphan() { CallFunction(Number, isOrphan()) };
// Local<Value> ActorClass::isOutOfControl() { CallFunction(Number, isOutOfControl()) };
// Local<Value> ActorClass::isOverScaffolding() { CallFunction(Number, isOverScaffolding()) };
Local<Value> ActorClass::isOverWater() { CallFunction(Number, isOverWater()) };
// Local<Value> ActorClass::isPacified() { CallFunction(Number, isPacified()) };
Local<Value> ActorClass::isPersistent() { CallFunction(Number, isPersistent()) };
Local<Value> ActorClass::isPlayer() { CallFunction(Number, isPlayer()) };
// Local<Value> ActorClass::isPlayingDead() { CallFunction(Number, isPlayingDead()) };
// Local<Value> ActorClass::isPowered() { CallFunction(Number, isPowered()) };
Local<Value> ActorClass::isRemotePlayer() { CallFunction(Number, isRemotePlayer()) };
// Local<Value> ActorClass::isRemoved() { CallFunction(Number, isRemoved()) };
// Local<Value> ActorClass::isResting() { CallFunction(Number, isResting()) };
// Local<Value> ActorClass::isSheared() { CallFunction(Number, isSheared()) };
// Local<Value> ActorClass::isSilent() { CallFunction(Number, isSilent()) };
Local<Value> ActorClass::isSitting() { CallFunction(Number, isSitting()) };
// Local<Value> ActorClass::isSneaking() { CallFunction(Number, isSneaking()) };
Local<Value> ActorClass::isSpectator() { CallFunction(Number, isSpectator()) };
// Local<Value> ActorClass::isStanding() { CallFunction(Number, isStanding()) };
Local<Value> ActorClass::isSurvival() { CallFunction(Number, isSurvival()) };
// Local<Value> ActorClass::isSwimmer() { CallFunction(Number, isSwimmer()) };
Local<Value> ActorClass::isSwimming() { CallFunction(Number, isSwimming()) };
Local<Value> ActorClass::isTame() { CallFunction(Number, isTame()) };
// Local<Value> ActorClass::isTickingEntity() { CallFunction(Number, isTickingEntity()) };
Local<Value> ActorClass::isTouchingDamageBlock() { CallFunction(Number, isTouchingDamageBlock()) };
Local<Value> ActorClass::isTrading() { CallFunction(Number, isTrading()) };
// Local<Value> ActorClass::isTrusting() { CallFunction(Number, isTrusting()) };
// Local<Value> ActorClass::isUseNewTradeScreen() { CallFunction(Number, isUseNewTradeScreen()) };
// Local<Value> ActorClass::isWalker() { CallFunction(Number, isWalker()) };
Local<Value> ActorClass::isWearingLeatherArmor() { CallFunction(Number, isWearingLeatherArmor()) };
Local<Value> ActorClass::isWorldBuilder() { CallFunction(Number, isWorldBuilder()) };


/* Methods */

// LLNDAPI class EntityContext&       getEntityContext();
// LLNDAPI class EntityContext const& getEntityContext() const;
Local<Value> ActorClass::getEntityContext(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return EntityContextClass::newEntityContext(&mActor->getEntityContext());
    }
    CatchReturn(Local<Value>())
}

// LLAPI void refresh();
Local<Value> ActorClass::refresh(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->refresh();
    }
    Catch;
    return Local<Value>();
}

// LLAPI optional_ref<Actor> clone(Vec3 const& pos,
//                           std::optional<DimensionType> dimId = std::nullopt) const;
Local<Value> ActorClass::clone(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Local<Value>());
    CheckInstanceTypeReturn(args[0], Vec3Class, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto engine = EngineScope::currentEngine();
        if (args.size() == 1) {
            return ActorClass::newActor(&mActor->clone(engine->getNativeInstance<Vec3Class>(args[0])->mVec3).value());
        }
        CheckInstanceTypeReturn(args[1], DimensionTypeClass, Local<Value>());
        if (args.size() == 2) {
            return ActorClass::newActor(&mActor
                ->clone(
                    engine->getNativeInstance<Vec3Class>(args[0])->mVec3,
                    *engine->getNativeInstance<DimensionTypeClass>(args[1])->mDimensionType
                )
                .value());
        }
    }
    Catch;
    return Local<Value>();
}


// LLNDAPI class Vec3 getFeetPos() const;
Local<Value> ActorClass::getFeetPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Vec3Class::newVec3Class(mActor->getFeetPos());
    }
    Catch;
    return Local<Value>();
}

// LLNDAPI class Vec3 getHeadPos() const;
Local<Value> ActorClass::getHeadPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Vec3Class::newVec3Class(mActor->getHeadPos());
    }
    Catch;
    return Local<Value>();
}

// LLNDAPI class BlockPos getFeetBlockPos() const;
Local<Value> ActorClass::getFeetBlockPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return BlockPosClass::newBlockPosClass(mActor->getFeetBlockPos());
    }
    Catch;
    return Local<Value>();
}

// LLAPI void setOnFire(int time, bool isEffect = true);
Local<Value> ActorClass::setOnFire(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (args.size() == 1) {
            mActor->setOnFire(args[0].asNumber().toInt64());
        }
        CheckArgTypeReturn(args[1], ValueKind::kBoolean, Local<Value>());
        if (args.size() == 2) {
            mActor->setOnFire(args[0].asNumber().toInt64(), args[0].asBoolean().value());
        }
    }
    Catch;
    return Local<Value>();
}

// LLAPI void stopFire();
Local<Value> ActorClass::stopFire(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->stopFire();
    }
    Catch;
    return Local<Value>();
}

// LLNDAPI float getPosDeltaPerSecLength() const;
Local<Value> ActorClass::getPosDeltaPerSecLength(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(mActor->getPosDeltaPerSecLength());
    }
    Catch;
    return Local<Value>();
}


// LLAPI bool hurtByCause(
//     float               damage,
//     ActorDamageCause    cause    = ActorDamageCause::Override,
//     optional_ref<Actor> attacker = std::nullopt
// );
Local<Value> ActorClass::hurtByCause(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Local<Value>());
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto damage = args[0].asNumber().toFloat();
        if (args.size() == 1) {
            return Boolean::newBoolean(mActor->hurtByCause(damage));
        }
#include "mc/deps/shared_types/legacy/actor/ActorDamageCause.h"
        auto cause = ConvertFromScriptX<SharedTypes::Legacy::ActorDamageCause>(args[1]);
        if (args.size() == 2) {
            return Boolean::newBoolean(mActor->hurtByCause(damage, cause));
        }
        CheckInstanceType(args[2], ActorClass);
        if (args.size() == 3) {
            return Boolean::newBoolean(mActor->hurtByCause(
                damage,
                cause,
                EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[2])->mActor
            ));
        }
        return Boolean::newBoolean(false);
    }
    Catch;
    return Boolean::newBoolean(false);
}

// LLNDAPI class HitResult traceRay(
//     float                                                                          tMax         = 5.5f,
//     bool                                                                           includeActor = true,
//     bool                                                                           includeBlock = true,
//     std::function<bool(class BlockSource const&, class Block const&, bool)> const& blockCheckFunction =
//         [](auto&&...) -> bool { return true; }
// ) const;
Local<Value> ActorClass::traceRay(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (args.size() == 0) {
            // return HitResultClass::newHitResult(&mActor->traceRay()); // !
        }
        CheckArgType(args[0], ValueKind::kNumber);
        auto tMax = args[0].asNumber().toFloat();
        if (args.size() == 1) {
            // return HitResultClass::newHitResult(&mActor->traceRay(tMax));
        }
        CheckArgType(args[1], ValueKind::kBoolean);
        auto includeActor = args[1].asBoolean().value();
        if (args.size() == 2) {
            // return HitResultClass::newHitResult(&mActor->traceRay(tMax, includeActor));
        }
        CheckArgType(args[2], ValueKind::kBoolean);
        auto includeBlock = args[2].asBoolean().value();
        if (args.size() == 3) {
            // return HitResultClass::newHitResult(&mActor->traceRay(tMax, includeActor, includeBlock));
        }
        // Failed to parse arguments:
        // if (args.size() == 4) {
        //     return HitResultClass::newHitResult(&mActor->traceRay(
        //         tMax,
        //         includeActor,
        //         includeBlock,
        // FAILED THERE: -----------------------------------------------------
        // ConvertFromScriptX<std::function<bool(BlockSource const&, Block const&, bool)>>(args[3])));
        // -------------------------------------------------------------------
        // }
    }
    Catch;
    return Local<Value>();
}

// LLAPI void teleport(class Vec3 const& pos, DimensionType dimId);
// LLAPI void teleport(class Vec3 const& pos, DimensionType dimId, class Vec2 const& rotation);
Local<Value> ActorClass::teleport(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], Vec3Class);
    CheckInstanceType(args[1], DimensionTypeClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto engine = EngineScope::currentEngine();
        auto pos = engine->getNativeInstance<Vec3Class>(args[0])->mVec3;
        auto dimId = engine->getNativeInstance<DimensionTypeClass>(args[1])->mDimensionType;
        if (args.size() == 1) {
            mActor->teleport(pos, *dimId);
            return Local<Value>();
        }
        CheckInstanceType(args[2], Vec2Class);
        auto rotation = engine->getNativeInstance<Vec2Class>(args[2])->mVec2;
        if (args.size() == 2) {
            mActor->teleport(pos, *dimId, rotation);
            return Local<Value>();
        }
    }
    Catch;
    return Local<Value>();
}

// LLAPI void setName(std::string const& name);
Local<Value> ActorClass::setName(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setName(args[0].asString().toString());
    }
    Catch;
    return Local<Value>();
}

// LLNDAPI float evalMolang(std::string const& expression);
Local<Value> ActorClass::evalMolang(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(mActor->evalMolang(args[0].asString().toString()));
    }
    Catch;
    return Local<Value>();
}

/* Virtual Functions */

// TODO: HashedString not implemented
// virtual bool hasComponent(::HashedString const& name) const;

// virtual void outOfWorld();
Local<Value> ActorClass::outOfWorld(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->outOfWorld();
    }
    Catch;
    return Local<Value>();
}

// TODO: not implemented: ActorInitializationMethod, VariantParameterList
// virtual void reloadHardcoded(::ActorInitializationMethod, ::VariantParameterList const&);
// virtual void reloadHardcodedClient(::ActorInitializationMethod);
// virtual void initializeComponents(::ActorInitializationMethod method, ::VariantParameterList const&);
// virtual void reloadComponents(::ActorInitializationMethod, ::VariantParameterList const&);

// virtual void resetUserPos(bool);
Local<Value> ActorClass::resetUserPos(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->resetUserPos(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// virtual ::ActorType getOwnerEntityType();
Local<Value> ActorClass::getOwnerEntityType(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->getOwnerEntityType());
    }
    Catch;
    return Local<Value>();
}

// virtual void remove();
Local<Value> ActorClass::remove(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->remove();
    }
    Catch;
    return Local<Value>();
}

// virtual ::Vec3 getFiringPos() const;
Local<Value> ActorClass::getFiringPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Vec3Class::newVec3Class(mActor->getFiringPos());
    }
    Catch;
    return Local<Value>();
}

// virtual float getInterpolatedBodyRot(float a = 0.0f) const;
Local<Value> ActorClass::getInterpolatedBodyRot(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        CheckArgTypeReturn(args[0], ValueKind::kNumber, Number::newNumber(0.0f));
        if (args.size() == 0) {
            return Number::newNumber(mActor->getInterpolatedBodyRot());
        } else if (args.size() == 1) {
            CheckArgType(args[0], ValueKind::kNumber);
            return Number::newNumber(mActor->getInterpolatedBodyRot(args[0].asNumber().toFloat()));
        }
    }
    Catch;
    return Local<Value>();
}

// virtual float getInterpolatedHeadRot(float = 0.0f) const;
Local<Value> ActorClass::getInterpolatedHeadRot(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        CheckArgTypeReturn(args[0], ValueKind::kNumber, Number::newNumber(0.0f));
        if (args.size() == 0) {
            return Number::newNumber(mActor->getInterpolatedHeadRot());
        } else if (args.size() == 1) {
            CheckArgType(args[0], ValueKind::kNumber);
            return Number::newNumber(mActor->getInterpolatedHeadRot(args[0].asNumber().toFloat()));
        }
    }
    Catch;
    return Local<Value>();
}

// virtual float getInterpolatedBodyYaw(float = 0.0f) const;
Local<Value> ActorClass::getInterpolatedBodyYaw(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        CheckArgTypeReturn(args[0], ValueKind::kNumber, Number::newNumber(0.0f));
        if (args.size() == 0) {
            return Number::newNumber(mActor->getInterpolatedBodyYaw());
        } else if (args.size() == 1) {
            CheckArgType(args[0], ValueKind::kNumber);
            return Number::newNumber(mActor->getInterpolatedBodyYaw(args[0].asNumber().toFloat()));
        }
    }
    Catch;
    return Number::newNumber(0.0f);
}

// virtual float getYawSpeedInDegreesPerSecond() const;
Local<Value> ActorClass::getYawSpeedInDegreesPerSecond(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(mActor->getYawSpeedInDegreesPerSecond());
    }
    Catch;
    return Number::newNumber(0.0f);
}

// virtual ::Vec3 getInterpolatedRidingOffset(float, int const) const;
Local<Value> ActorClass::getInterpolatedRidingOffset(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Vec3Class::newVec3Class(
            mActor->getInterpolatedRidingOffset(args[0].asNumber().toFloat(), args[1].asNumber().toInt32())
        );
    }
    Catch;
    return Local<Value>();
}

// virtual void blockedByShield(::ActorDamageSource const& source, ::Actor& blocker);
Local<Value> ActorClass::blockedByShield(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ActorDamageSourceClass);
    CheckInstanceType(args[1], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto engine = EngineScope::currentEngine();
        mActor->blockedByShield(
            *engine->getNativeInstance<ActorDamageSourceClass>(args[0])->mActorDamageSource,
            *engine->getNativeInstance<ActorClass>(args[1])->mActor
        );
    }
    Catch;
    return Local<Value>();
}

// virtual void teleportTo(::Vec3 const& pos, bool shouldStopRiding, int, int, bool keepVelocity);
Local<Value> ActorClass::teleportTo(const Arguments &args) {
    CheckArgsCount(args, 5);
    CheckInstanceType(args[0], Vec3Class)
    CheckArgType(args[1], ValueKind::kBoolean);
    CheckArgType(args[2], ValueKind::kNumber);
    CheckArgType(args[3], ValueKind::kNumber);
    CheckArgType(args[4], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->teleportTo(
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
            args[1].asBoolean().value(),
            args[2].asNumber().toInt32(),
            args[3].asNumber().toInt32(),
            args[4].asBoolean().value()
        );
    }
    Catch;
    return Local<Value>();
}

// virtual void lerpMotion(::Vec3 const& delta);
Local<Value> ActorClass::lerpMotion(const Arguments &args) {
    CheckInstanceType(args[0], Vec3Class);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->lerpMotion(EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3);
    }
    Catch;
    return Local<Value>();
}

// virtual ::std::unique_ptr<::AddActorBasePacket> tryCreateAddActorPacket();
//
// Cannot use this.
// Local<Value> ActorClass::tryCreateAddActorPacket(const Arguments& args) {
//     try {
//         if (!mActor) {
//             return Local<Value>();
//         }
//         return ConvertToScriptX(mActor->tryCreateAddActorPacket());
//     }
//     Catch;
//     return Local<Value>();
// }

// virtual void normalTick();
Local<Value> ActorClass::normalTick(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->normalTick();
    }
    Catch;
    return Local<Value>();
}

// virtual void baseTick();
Local<Value> ActorClass::baseTick(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->baseTick();
    }
    Catch;
    return Local<Value>();
}

// virtual void passengerTick();
Local<Value> ActorClass::passengerTick(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->passengerTick();
    }
    Catch;
    return Local<Value>();
}

// virtual bool startRiding(::Actor& vehicle, bool forceRiding);
Local<Value> ActorClass::startRiding(const Arguments &args) {
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kBoolean, Boolean::newBoolean(false));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->startRiding(
            *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
            args[1].asBoolean().value()
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void addPassenger(::Actor& passenger);
Local<Value> ActorClass::addPassenger(const Arguments &args) {
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->addPassenger(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor);
    }
    Catch;
    return Local<Value>();
}

// virtual ::std::string getExitTip(::std::string const& kind, ::InputMode mode, ::NewInteractionModel scheme) const;
Local<Value> ActorClass::getExitTip(const Arguments &args) {
    CheckArgsCount(args, 3);
    CheckArgTypeReturn(args[0], ValueKind::kString, String::newString(""));
    CheckArgTypeReturn(args[1], ValueKind::kNumber, String::newString(""));
    CheckArgTypeReturn(args[2], ValueKind::kNumber, String::newString(""));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return String::newString(mActor->getExitTip(
            args[0].asString().toString(),
            ConvertFromScriptX<InputMode>(args[1]),
            ConvertFromScriptX<NewInteractionModel>(args[2])
        ));
    }
    Catch;
    return String::newString("");
}

// Not found: mce::Color
// virtual ::mce::Color getNameTagTextColor() const;

// virtual ::Vec3 getHeadLookVector(float a = 0.0f) const;
Local<Value> ActorClass::getHeadLookVector(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (args.size() == 0) {
            return Vec3Class::newVec3Class(mActor->getHeadLookVector());
        }
        CheckArgTypeReturn(args[0], ValueKind::kNumber, Local<Value>());
        if (args.size() == 1) {
            return Vec3Class::newVec3Class(mActor->getHeadLookVector(args[0].asNumber().toFloat()));
        }
    }
    Catch;
    return Local<Value>();
}

// MCAPI float getBrightness(float a = 0.0f) const;
// virtual float getBrightness(float a, ::IConstBlockSource const& region) const;
Local<Value> ActorClass::getBrightness(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgTypeReturn(args[0], ValueKind::kNumber, Number::newNumber(0.0));
    CheckInstanceTypeReturn(args[1], IConstBlockSourceClass, Number::newNumber(0.0));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (args.size() == 1) {
            return Number::newNumber(mActor->getBrightness());
        }
        if (args.size() == 2) {
            return Number::newNumber(mActor->getBrightness(
                args[0].asNumber().toFloat(),
                *EngineScope::currentEngine()->getNativeInstance<IConstBlockSourceClass>(args[1])->mIConstBlockSource
            ));
        }
    }
    Catch;
    return Number::newNumber(0.0);
}

// virtual void playerTouch(::Player&);
Local<Value> ActorClass::playerTouch(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], PlayerClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->playerTouch(*EngineScope::currentEngine()->getNativeInstance<PlayerClass>(args[0])->get());
    }
    Catch;
    return Local<Value>();
}

// virtual void setSleeping(bool);
Local<Value> ActorClass::setSleeping(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setSleeping(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// virtual void setSneaking(bool value);
Local<Value> ActorClass::setSneaking(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setSneaking(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// virtual bool isDamageBlocked(::ActorDamageSource const&) const;
Local<Value> ActorClass::isDamageBlocked(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ActorDamageSourceClass, Boolean::newBoolean(false));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->isDamageBlocked(
            *EngineScope::currentEngine()->getNativeInstance<ActorDamageSourceClass>(args[0])->mActorDamageSource
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void setTarget(::Actor* entity);
Local<Value> ActorClass::setTarget(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ActorClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setTarget(EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor);
    }
    Catch;
    return Local<Value>();
}

// virtual bool isValidTarget(::Actor*) const;
Local<Value> ActorClass::isValidTarget(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(
            mActor->isValidTarget(EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        );
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual bool attack(::Actor& target, ::ActorDamageCause const&);
Local<Value> ActorClass::attack(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->attack(
            *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
            ConvertFromScriptX<SharedTypes::Legacy::ActorDamageCause>(args[1])
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void performRangedAttack(::Actor& target, float);
Local<Value> ActorClass::performRangedAttack(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceTypeReturn(args[0], ActorClass, Local<Value>());
    CheckArgTypeReturn(args[1], ValueKind::kNumber, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->performRangedAttack(
            *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
            args[1].asNumber().toFloat()
        );
    }
    Catch;
    return Local<Value>();
}

// virtual void setOwner(::ActorUniqueID const ownerId);
Local<Value> ActorClass::setOwner(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setOwner(*EngineScope::currentEngine()->getNativeInstance<ActorUniqueIDClass>(args[0])->mActorUniqueID);
    }
    Catch;
    return Local<Value>();
}

// virtual void setSitting(bool value);
Local<Value> ActorClass::setSitting(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgTypeReturn(args[0], ValueKind::kBoolean, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setSitting(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// virtual void onTame()
Local<Value> ActorClass::onTame(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onTame();
    }
    Catch;
    return Local<Value>();
}

// virtual void onFailedTame();
Local<Value> ActorClass::onFailedTame(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onFailedTame();
    }
    Catch;
    return Local<Value>();
}

// virtual void setStanding(bool value);
Local<Value> ActorClass::setStanding(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setStanding(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// virtual ::SharedTypes::Legacy::LevelSoundEvent getAmbientSound() const;
Local<Value> ActorClass::getAmbientSound(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX<SharedTypes::Legacy::LevelSoundEvent>(mActor->getAmbientSound());
    }
    Catch;
    return Local<Value>();
}

// virtual bool isInvulnerableTo(::ActorDamageSource const& source) const;
Local<Value> ActorClass::isInvulnerableTo(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ActorDamageSourceClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->isInvulnerableTo(
            *EngineScope::currentEngine()->getNativeInstance<ActorDamageSourceClass>(args[0])->mActorDamageSource
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual ::ActorDamageCause getBlockDamageCause(::Block const& block) const;
Local<Value> ActorClass::getBlockDamageCause(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], BlockClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX<SharedTypes::Legacy::ActorDamageCause>(
            mActor->getBlockDamageCause(*EngineScope::currentEngine()->getNativeInstance<BlockClass>(args[0])->mBlock)
        );
    }
    Catch;
    return Local<Value>();
}

// virtual bool doFireHurt(int amount);
Local<Value> ActorClass::doFireHurt(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Boolean::newBoolean(false);
        }
        return Boolean::newBoolean(mActor->doFireHurt(args[0].asNumber().toInt32()));
    }
    Catch;
}

// virtual void onLightningHit();
Local<Value> ActorClass::onLightningHit(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onLightningHit();
    }
    Catch;
    return Local<Value>();
}

// virtual void feed(int itemId);
Local<Value> ActorClass::feed(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->feed(args[0].asNumber().toInt32());
    }
    Catch;
    return Local<Value>();
}

// virtual void handleEntityEvent(::ActorEvent eventId, int data);
Local<Value> ActorClass::handleEntityEvent(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->handleEntityEvent(ConvertFromScriptX<ActorEvent>(args[0]), args[1].asNumber().toInt32());
    }
    Catch;
    return Local<Value>();
}

// HashedString Not Implemented
// virtual ::HashedString const& getActorRendererId() const;

// virtual void despawn();
Local<Value> ActorClass::despawn(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->despawn();
    }
    Catch;
    return Local<Value>();
}

// virtual void setArmor(::ArmorSlot slot, ::ItemStack const& item);
Local<Value> ActorClass::setArmor(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckInstanceTypeReturn(args[1], ItemStackClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setArmor(
            ConvertFromScriptX<SharedTypes::Legacy::ArmorSlot>(args[0]),
            *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[1])->mItemStack
        );
    }
    Catch;
    return Local<Value>();
}

// virtual ::ArmorMaterialType getArmorMaterialTypeInSlot(::ArmorSlot) const;
Local<Value> ActorClass::getArmorMaterialTypeInSlot(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Number::newNumber(0));
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Number::newNumber(0);
        }
        return ConvertToScriptX<ArmorMaterialType>(
            mActor->getArmorMaterialTypeInSlot(ConvertFromScriptX<SharedTypes::Legacy::ArmorSlot>(args[0]))
        );
    }
    Catch;
    return Number::newNumber(0);
}

// virtual int getArmorTextureIndexInSlot(::ArmorSlot) const;
Local<Value> ActorClass::getArmorTextureIndexInSlot(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Number::newNumber(0));
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Number::newNumber(0);
        }
        return Number::newNumber(
            mActor->getArmorTextureIndexInSlot(ConvertFromScriptX<SharedTypes::Legacy::ArmorSlot>(args[0])));
    }
    Catch;
    return Number::newNumber(0);
}

// virtual float getArmorColorInSlot(::ArmorSlot, int) const;
Local<Value> ActorClass::getArmorColorInSlot(const Arguments &args) {
    CheckArgsCountReturn(args, 2, Number::newNumber(0.0f));
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Number::newNumber(0.0f);
        }
        return Number::newNumber(
            mActor->getArmorColorInSlot(ConvertFromScriptX<SharedTypes::Legacy::ArmorSlot>(args[0]),
                                        args[1].asNumber().toInt32())
        );
    }
    Catch;
    return Number::newNumber(0.0f);
}

// virtual void setEquippedSlot(::SharedTypes::Legacy::EquipmentSlot, ::ItemStack const&);
Local<Value> ActorClass::setEquippedSlot(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckInstanceTypeReturn(args[1], ItemStackClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setEquippedSlot(
            ConvertFromScriptX<SharedTypes::Legacy::EquipmentSlot>(args[0]),
            *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[1])->mItemStack
        );
    }
    Catch;
    return Local<Value>();
}

// virtual void setCarriedItem(::ItemStack const& item);
Local<Value> ActorClass::setCarriedItem(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ItemStackClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setCarriedItem(*EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack);
    }
    Catch;
    return Local<Value>();
}

// virtual ::ItemStack const& getCarriedItem() const;
Local<Value> ActorClass::getCarriedItem(const Arguments &args) {
    CheckArgsCountReturn(args, 0, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ItemStackClass::newItemStack(const_cast<ItemStack *>(&mActor->getCarriedItem()));
    }
    Catch;
    return Local<Value>();
}

// virtual void setOffhandSlot(::ItemStack const& item);
Local<Value> ActorClass::setOffhandSlot(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceTypeReturn(args[0], ItemStackClass, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setOffhandSlot(*EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack);
    }
    Catch;
    return Local<Value>();
}

// virtual ::ItemStack const& getEquippedTotem() const;
Local<Value> ActorClass::getEquippedTotem(const Arguments &args) {
    CheckArgsCountReturn(args, 0, Local<Value>());
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ItemStackClass::newItemStack(const_cast<ItemStack *>(&mActor->getEquippedTotem()));
    }
    Catch;
    return Local<Value>();
}

// virtual bool load(::CompoundTag const& tag, ::DataLoadHelper& dataLoadHelper);
// virtual ::HashedString const& queryEntityRenderer() const;

// virtual ::ActorUniqueID getSourceUniqueID() const;
Local<Value> ActorClass::getSourceUniqueID(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->getSourceUniqueID());
    }
    Catch;
    return Local<Value>();
}

// virtual ::AABB getLiquidAABB(::MaterialType const liquidType) const;
Local<Value> ActorClass::getLiquidAABB(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        AABB liquidAABB = mActor->getLiquidAABB(ConvertFromScriptX<MaterialType>(args[0]));
        return AABBClass::newAABB(&liquidAABB);
    }
    Catch;
    return Local<Value>();
}

// virtual void handleInsidePortal(::BlockPos const& portalPos);
Local<Value> ActorClass::handleInsidePortal(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockPos);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->handleInsidePortal(EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos);
    }
    Catch;
    return Local<Value>();
}

// virtual void changeDimension(::DimensionType toId);
// virtual void changeDimension(::ChangeDimensionPacket const&); // two overloads
Local<Value> ActorClass::changeDimension(const Arguments &args) {
    CheckArgsCount(args, 1);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (IsInstanceOf<DimensionTypeClass>(args[0])) {
            mActor->changeDimension(
                *EngineScope::currentEngine()->getNativeInstance<DimensionTypeClass>(args[0])->mDimensionType
            );
            return Local<Value>();
        }
        if (IsInstanceOf<ChangeDimensionPacketClass>(args[0])) {
            mActor->changeDimension(*EngineScope::currentEngine()
                ->getNativeInstance<ChangeDimensionPacketClass>(args[0])
                ->mChangeDimensionPacket);
            return Local<Value>();
        }

        PrintWrongArgType();
        return Local<Value>();
    }
    Catch;
}

// virtual ::ActorUniqueID getControllingPlayer() const;
Local<Value> ActorClass::getControllingPlayer(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->getControllingPlayer());
    }
    Catch;
    return Local<Value>();
}

// virtual float causeFallDamageToActor(float, float, ::ActorDamageSource);
Local<Value> ActorClass::causeFallDamageToActor(const Arguments &args) {
    CheckArgsCount(args, 3);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckInstanceType(args[2], ActorDamageSourceClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(mActor->causeFallDamageToActor(
            args[0].asNumber().toFloat(),
            args[1].asNumber().toFloat(),
            *EngineScope::currentEngine()->getNativeInstance<ActorDamageSourceClass>(args[2])->mActorDamageSource
        ));
    }
    Catch;
    return Local<Value>();
}

// virtual void onSynchedDataUpdate(int dataId);
Local<Value> ActorClass::onSynchedDataUpdate(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onSynchedDataUpdate(args[0].asNumber().toInt32());
    }
    Catch;
    return Local<Value>();
}

// virtual bool canAddPassenger(::Actor& passenger) const;
Local<Value> ActorClass::canAddPassenger(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(
            mActor->canAddPassenger(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        );
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual bool canPickupItem(::ItemStack const&) const;
Local<Value> ActorClass::canPickupItem(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ItemStackClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(
            mActor->canPickupItem(*EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack)
        );
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void sendMotionPacketIfNeeded(::PlayerMovementSettings const& playerMovementSettings);
Local<Value> ActorClass::sendMotionPacketIfNeeded(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], PlayerMovementSettingsClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->sendMotionPacketIfNeeded(*EngineScope::currentEngine()
            ->getNativeInstance<PlayerMovementSettingsClass>(args[0])
            ->mPlayerMovementSettings);
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}


// virtual void startSwimming();
Local<Value> ActorClass::startSwimming(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->startSwimming();
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// virtual void stopSwimming();
Local<Value> ActorClass::stopSwimming(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->stopSwimming();
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// virtual void buildDebugInfo(::std::string&) const;
Local<Value> ActorClass::buildDebugInfo(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->buildDebugInfo(&args[0].asString().toString());
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// virtual ::CommandPermissionLevel getCommandPermissionLevel() const;
Local<Value> ActorClass::getCommandPermissionLevel(const Arguments &args) {
    CheckInstanceType(args[1], CommandPermissionLevel);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->getCommandPermissionLevel());
    }
    Catch;
    return Local<Value>();
}

// virtual bool canBeAffected(uint id) const;
Local<Value> ActorClass::canBeAffected(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->canBeAffected(args[0].asNumber().toInt64()));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual bool canBeAffectedByArrow(::MobEffectInstance const& effect) const;
Local<Value> ActorClass::canBeAffectedByArrow(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], MobEffectInstanceClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->canBeAffectedByArrow(
            *EngineScope::currentEngine()->getNativeInstance<MobEffectInstanceClass>(args[0])->mMobEffectInstance
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void onEffectRemoved(::MobEffectInstance& effect);
Local<Value> ActorClass::onEffectRemoved(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], MobEffectInstanceClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onEffectRemoved(
            *EngineScope::currentEngine()->getNativeInstance<MobEffectInstanceClass>(args[0])->mMobEffectInstance
        );
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// very useless func, ignore it
// I don't want to add a new class for this.
// virtual ::AnimationComponent& getAnimationComponent();

// virtual void openContainerComponent(::Player& player);
Local<Value> ActorClass::openContainerComponent(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], PlayerClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->openContainerComponent(*EngineScope::currentEngine()->getNativeInstance<PlayerClass>(args[0])->get());
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// virtual void swing();
Local<Value> ActorClass::swing(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->swing();
    }
    Catch;
    return Local<Value>();
}

// virtual void useItem(::ItemStackBase& item, ::ItemUseMethod itemUseMethod, bool consumeItem);
Local<Value> ActorClass::useItem(const Arguments &args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], ItemStackBaseClass);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckArgType(args[2], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->useItem(
            *EngineScope::currentEngine()->getNativeInstance<ItemStackBaseClass>(args[0])->mItemStackBase,
            ConvertFromScriptX<ItemUseMethod>(args[1]),
            args[2].asBoolean().value()
        );
    }
    Catch;
    return Local<Value>();
}

// I don't want to implement this.
// virtual void getDebugText(::std::vector<::std::string>& outputInfo);

// virtual float getPassengerYRotation(::Actor const& passenger) const;
Local<Value> ActorClass::getPassengerYRotation(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(
            mActor->getPassengerYRotation(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        );
    }
    Catch;
    return Number::newNumber(0.0f);
}

// virtual bool add(::ItemStack& item);
Local<Value> ActorClass::add(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ItemStackClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(
            mActor->add(*EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack)
        );
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual bool drop(::ItemStack const& item, bool const randomly);
Local<Value> ActorClass::drop(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ItemStackClass);
    CheckArgType(args[1], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return ConvertToScriptX(mActor->drop(
            *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack,
            args[1].asBoolean().value()
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

//  virtual bool getInteraction(::Player& player, ::ActorInteraction& interaction, ::Vec3 const&);
Local<Value> ActorClass::getInteraction(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], PlayerClass);
    CheckInstanceType(args[1], ActorInteractionClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->getInteraction(
            *EngineScope::currentEngine()->getNativeInstance<PlayerClass>(args[0])->get(),
            *EngineScope::currentEngine()->getNativeInstance<ActorInteractionClass>(args[1])->mActorInteraction,
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[2])->mVec3
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual bool canDestroyBlock(::Block const&) const;
Local<Value> ActorClass::canDestroyBlock(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(
            mActor->canDestroyBlock(*EngineScope::currentEngine()->getNativeInstance<BlockClass>(args[0])->mBlock)
        );
    }
    Catch;
    return Boolean::newBoolean(false);
}

// virtual void setAuxValue(int);
Local<Value> ActorClass::setAuxValue(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->setAuxValue(args[0].asNumber().toInt32());
    }
    Catch;
    return Local<Value>();
}

// I don't want to implement this. XD
// virtual void renderDebugServerState(::Options const&);


// virtual void kill();
Local<Value> ActorClass::kill(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->kill();
    }
    Catch;
    return Local<Value>();
}

// virtual void die(::ActorDamageSource const& source);
Local<Value> ActorClass::die(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorDamageSourceClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->die(
            *EngineScope::currentEngine()->getNativeInstance<ActorDamageSourceClass>(args[0])->mActorDamageSource
        );
    }
    Catch;
    return Local<Value>();
}

// Too complex func, ignoring it.
// virtual void applySnapshot(
//                            ::EntityContext const&                                   snapshotEntity,
//                            ::MovementDataExtractionUtility::SnapshotAccessor const& originalSnapshotEntity
// );

// virtual float getNextStep(float const moveDist);
Local<Value> ActorClass::getNextStep(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // return Number::newNumber(mActor->getNextStep(args[0].asNumber().toFloat()));
    }
    Catch;
    return Number::newNumber(0.0f);
}

// virtual void onPush(::Actor&);
Local<Value> ActorClass::onPush(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->onPush(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor);
    }
    Catch;
    return Local<Value>();
}

// virtual ::std::optional<::BlockPos> getLastDeathPos() const;
Local<Value> ActorClass::getLastDeathPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto pos = mActor->getLastDeathPos();
        if (pos.has_value()) {
            return BlockPosClass::newBlockPosClass(pos.value());
        }
    }
    Catch;
    return Local<Value>();
}

// virtual ::std::optional<::DimensionType> getLastDeathDimension() const;
Local<Value> ActorClass::getLastDeathDimension(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        auto dim = mActor->getLastDeathDimension();
        if (dim.has_value()) {
            return DimensionTypeClass::newDimensionType(&dim.value());
        }
    }
    Catch;
    return Local<Value>();
}

// virtual void doEnterWaterSplashEffect();
Local<Value> ActorClass::doEnterWaterSplashEffect(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->doEnterWaterSplashEffect();
    }
    Catch;
    return Local<Value>();
}

// virtual void doExitWaterSplashEffect();
Local<Value> ActorClass::doExitWaterSplashEffect(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->doExitWaterSplashEffect();
    }
    Catch;
    return Local<Value>();
}

// virtual void doWaterSplashEffect();
Local<Value> ActorClass::doWaterSplashEffect(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->doWaterSplashEffect();
    }
    Catch;
    return Local<Value>();
}

// NBTAPI not available, ignoring it.
// virtual void readAdditionalSaveData(::CompoundTag const& tag, ::DataLoadHelper& dataLoadHelper);
// virtual void addAdditionalSaveData(::CompoundTag& tag) const;

/* MCAPI */

// MCAPI void addCategory(::ActorCategory const& category);
Local<Value> ActorClass::addCategory(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorCategory);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->addCategory(ConvertFromScriptX<ActorCategory>(args[0]));
    }
    Catch;
    return Local<Value>();
}

// MCAPI void addDefinitionGroup(::std::string const& name);
Local<Value> ActorClass::addDefinitionGroup(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->addDefinitionGroup(args[0].asString().toString());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void addEffect(::MobEffectInstance const& effect);
Local<Value> ActorClass::addEffect(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], MobEffectInstanceClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->addEffect(
            *EngineScope::currentEngine()->getNativeInstance<MobEffectInstanceClass>(args[0])->mMobEffectInstance
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI bool addTag(::std::string const& tag);
Local<Value> ActorClass::addTag(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(mActor->addTag(args[0].asString().toString()));
    }
    Catch;
    return Local<Value>();
}

// MCAPI void applyImpulse(::Vec3 const& impulse);
Local<Value> ActorClass::applyImpulse(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], Vec3Class);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->applyImpulse(EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3);
    }
    Catch;
    return Local<Value>();
}

// MCAPI void buildDebugGroupInfo(::std::string& out) const;
Local<Value> ActorClass::buildDebugGroupInfo(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        string out = args[0].asString().toString();
        mActor->buildDebugGroupInfo(out);
    }
    Catch;
    return Local<Value>();
}

// MCAPI ::Vec3 buildForward() const;
Local<Value> ActorClass::buildForward(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Vec3Class::newVec3Class(mActor->buildForward());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void burn(int dmg, bool bInFire);
Local<Value> ActorClass::burn(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->burn(args[0].asNumber().toInt32(), args[1].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// MCAPI ::Vec3 calcCenterPos() const;
Local<Value> ActorClass::calcCenterPos(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // return Vec3Class::newVec3Class(mActor->calcCenterPos());
        return Local<Value>();
    }
    Catch;
    return Local<Value>();
}

// MCAPI float calculateAttackDamage(::Actor& entity);
Local<Value> ActorClass::calculateAttackDamage(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(
            mActor->calculateAttackDamage(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI bool canAttack(::Actor const& entity) const;
Local<Value> ActorClass::canAttack(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Boolean::newBoolean(
            mActor->canAttack(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI bool canMate(::Actor const& partner) const;
Local<Value> ActorClass::canMate(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // return Boolean::newBoolean(
        // mActor->canMate(*EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor)
        // );
    }
    Catch;
    return Local<Value>();
}

// MCAPI bool canSee(::Actor const& target, ::ShapeType obstructionType) const;
// MCAPI bool canSee(::Vec3 const& targetPos, ::ShapeType obstructionType) const;
// MCAPI bool canSee(::Actor const& target, ::ActorLocation targetLocationPart, ::ShapeType obstructionType) const;
Local<Value> ActorClass::canSee(const Arguments &args) {
    CheckArgsCount(args, 2);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (args.size() == 2) {
            CheckInstanceType(args[1], ShapeType)
            const auto obstructionType = ConvertFromScriptX<ShapeType>(args[1]);
            if (IsInstanceOf<ActorClass>(args[0])) {
                return Boolean::newBoolean(mActor->canSee(
                    *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
                    obstructionType
                ));
            }
            if (IsInstanceOf<Vec3Class>(args[0])) {
                return Boolean::newBoolean(mActor->canSee(
                    EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
                    obstructionType
                ));
            }
            PrintWrongArgType();
            return Boolean::newBoolean(false);
        }
        CheckArgsCount(args, 3);
        CheckInstanceType(args[0], ActorClass);
        // CheckInstanceType(args[1], ActorLocation);
        CheckInstanceType(args[2], ShapeType);
        return Boolean::newBoolean(mActor->canSee(
            *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
            // ConvertFromScriptX<ActorLocation>(args[1]),
            ConvertFromScriptX<ShapeType>(args[2])
        ));
    }
    Catch;
    return Boolean::newBoolean(false);
}

// MCAPI void celebrateHunt(int duration, bool special);
Local<Value> ActorClass::celebrateHunt(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->celebrateHunt(args[0].asNumber().toInt32(), args[1].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void checkFallDamage(float ya, bool onGround, bool recheckLiquid);
Local<Value> ActorClass::checkFallDamage(const Arguments &args) {
    CheckArgsCount(args, 3);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kBoolean);
    CheckArgType(args[2], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->checkFallDamage(args[0].asNumber().toFloat(), args[1].asBoolean().value(), args[2].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void chorusFruitTeleport(::Vec3 const& range);
Local<Value> ActorClass::chorusFruitTeleport(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], Vec3Class);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->chorusFruitTeleport(EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3);
    }
    Catch;
    return Local<Value>();
}

// MCAPI void clearFishingHookID();
Local<Value> ActorClass::clearFishingHookID(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->clearFishingHookID();
    }
    Catch;
    return Local<Value>();
}

// MCAPI bool closerThan(::Actor const& e, float distance) const;
// MCAPI bool closerThan(::Actor const& e, float distanceXZ, float distanceY) const;
Local<Value> ActorClass::closerThan(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ActorClass);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        const auto e = EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor;
        // Because distance and distanceXZ are in a same position, so we can use distance as distanceXZ.
        const auto distance = args[1].asNumber().toFloat();
        if (args.size() == 2) {
            return Boolean::newBoolean(mActor->closerThan(e, distance));
        }
        if (args.size() == 3) {
            CheckArgType(args[2], ValueKind::kNumber);
            return Boolean::newBoolean(mActor->closerThan(
                e,
                // used distance as distanceXZ.
                distance,
                args[2].asNumber().toFloat()
            ));
        }
    }
    Catch;
    return Local<Value>();
}

// MCAPI void consumeItem(::ItemActor& itemActor, int count);
Local<Value> ActorClass::consumeItem(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ItemActorClass);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->consumeItem(
            *EngineScope::currentEngine()->getNativeInstance<ItemActorClass>(args[0])->mItemActor,
            args[1].asNumber().toInt32()
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI ::UpdateEquipPacket createUpdateEquipPacket(int containerID);
Local<Value> ActorClass::createUpdateEquipPacket(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return UpdateEquipPacketClass::newUpdateEquipPacket(
            new UpdateEquipPacket(mActor->createUpdateEquipPacket(args[0].asNumber().toInt32()))
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI ::UpdateTradePacket createUpdateTradePacket(int containerID);
Local<Value> ActorClass::createUpdateTradePacket(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // return UpdateTradePacketClass::newUpdateTradePacket(
        //     &mActor->createUpdateTradePacket(args[0].asNumber().toInt32())
        // );
    }
    Catch;
    return Local<Value>();
}

// MCAPI void deregisterTagsFromLevelCache();
Local<Value> ActorClass::deregisterTagsFromLevelCache(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->deregisterTagsFromLevelCache();
    }
    Catch;
    return Local<Value>();
}

// MCAPI float distanceSqrToBlockPosCenter(::BlockPos const& pos) const;
Local<Value> ActorClass::distanceSqrToBlockPosCenter(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockPosClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // return Number::newNumber(mActor->distanceSqrToBlockPosCenter(
        //     EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos
        // ));
        return Number::newNumber(0);
    }
    Catch;
}

// MCAPI float distanceTo(::Actor const& e) const;
// MCAPI float distanceTo(::Vec3 const& pos) const;
Local<Value> ActorClass::distanceTo(const Arguments &args) {
    CheckArgsCount(args, 1);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (IsInstanceOf<ActorClass>(args[0])) {
            const auto e = EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor;
            return Number::newNumber(mActor->distanceTo(*e));
        }
        if (IsInstanceOf<Vec3Class>(args[1])) {
            const auto pos = EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3;
            return Number::newNumber(mActor->distanceTo(pos));
        }
    }
    Catch;
    return Number::newNumber(0.0f);
}

// MCAPI float distanceToSqr(::Actor const& e) const;
// MCAPI float distanceToSqr(::Vec3 const& pos) const;
Local<Value> ActorClass::distanceToSqr(const Arguments &args) {
    CheckArgsCount(args, 1);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (IsInstanceOf<ActorClass>(args[0])) {
            const auto e = EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor;
            return Number::newNumber(mActor->distanceToSqr(*e));
        }
        if (IsInstanceOf<Vec3Class>(args[1])) {
            const auto pos = EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3;
            return Number::newNumber(mActor->distanceToSqr(pos));
        }
    }
    Catch;
    return Number::newNumber(0.0f);
}

// MCAPI void dropLeash(bool createItemDrop, bool cutRope);
Local<Value> ActorClass::dropLeash(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kBoolean);
    CheckArgType(args[1], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->dropLeash(args[0].asBoolean().value(), args[1].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void dropTowards(::ItemStack const& item, ::Vec3 towards);
Local<Value> ActorClass::dropTowards(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ItemStackClass);
    CheckInstanceType(args[1], Vec3Class);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->dropTowards(
            EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack,
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[1])->mVec3
        );
    }
    Catch;
    return Local<Value>();
}

// MCAPI void enableAutoSendPosRot(bool enable);
Local<Value> ActorClass::enableAutoSendPosRot(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        // mActor->enableAutoSendPosRot(args[0].asBoolean().value());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void equip(::EquipmentTable const& equipmentTable);
// MCAPI void equip(::std::string const& lootTableFilePath);
Local<Value> ActorClass::equip(const Arguments &args) {
    CheckArgsCount(args, 1);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        if (IsInstanceOf<EquipmentTableClass>(args[0])) {
            mActor->equip(
                *EngineScope::currentEngine()->getNativeInstance<EquipmentTableClass>(args[0])->mEquipmentTable
            );
        }
        CheckArgType(args[0], ValueKind::kString);
        mActor->equip(args[0].asString().toString());
    }
    Catch;
    return Local<Value>();
}

// MCAPI void equipFromEquipmentDefinition();
Local<Value> ActorClass::equipFromEquipmentDefinition(const Arguments &args) {
    try {
        if (!mActor) {
            return Local<Value>();
        }
        mActor->equipFromEquipmentDefinition();
    }
    Catch;
    return Local<Value>();
}

// MCAPI float evaluateSeatRotation(::RideableComponent const& rideable, bool useVehicleRenderParams);
Local<Value> ActorClass::evaluateSeatRotation(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], RideableComponentClass);
    try {
        if (!mActor) {
            return Local<Value>();
        }
        return Number::newNumber(mActor->evaluateSeatRotation(
            *EngineScope::currentEngine()->getNativeInstance<RideableComponentClass>(args[0])->mRideableComponent,
            args[1].asBoolean().value()
        ));
    }
    Catch;
    return Number::newNumber(0.0f);
}

