#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep



#include <mc/world/level/block/Block.h>

class BlockClass : public ScriptClass {
public:
    Block* mBlock;

public:
    BlockClass(Block* block);

public:
    // static BlockClass* create(const Arguments& args); // TODO
    static Local<Object> newBlock(Block* block);

public: /* Member */
    Local<Value> getAllowsRunes();
    //Local<Value> getBlockEntityType();
    Local<Value> getBurnOdds();
    // Local<Value> getDefaultState();
    Local<Value> getDescriptionId();
    Local<Value> getDestroySpeed();
    Local<Value> getFlameOdds();
    Local<Value> getFriction();
    Local<Value> getExplosionResistance();
    //Local<Value> getLight();
    //Local<Value> getLightEmission();
    //Local<Value> getMaterial();
    //Local<Value> getName();
    Local<Value> getRuntimeId();
    //Local<Value> getSerializationId();
    Local<Value> getThickness();
    Local<Value> getTranslucency();
    Local<Value> getVariant();

    Local<Value> isAir();
    Local<Value> isBounceBlock();
    Local<Value> isButtonBlock();
    Local<Value> isContainerBlock();
    Local<Value> isCropBlock();
    Local<Value> isDoorBlock();
    Local<Value> isEmpty();
    Local<Value> isFallingBlock();
    Local<Value> isFenceBlock();
    Local<Value> isFenceGateBlock();
    Local<Value> isInteractiveBlock();
    Local<Value> isLavaFlammable();
    Local<Value> isLeverBlock();
    Local<Value> isMotionBlockingBlock();
    Local<Value> isMultifaceBlock();
    Local<Value> isRailBlock();
    Local<Value> isSignalSource();
    Local<Value> isSlabBlock();
    Local<Value> isSolid();
    Local<Value> isSolidBlockingBlock();
    Local<Value> isSolidBlockingBlockAndNotSignalSource();
    Local<Value> isStairBlock();
    Local<Value> isStemBlock();
    Local<Value> isThinFenceBlock();
    Local<Value> isUnbreakable();
    Local<Value> isWallBlock();

    Local<Value> canBeBrokenFromFalling();
    Local<Value> canBeOriginalSurface();
    Local<Value> canHaveExtraData();
    Local<Value> canHurtAndBreakItem();
    Local<Value> canInstatick();
    Local<Value> canReactToNeighborsDuringInstatick();

    Local<Value> hasBlockEntity();
    Local<Value> hasComparatorSignal();

public: /* Method */
    Local<Value> addAABBs(const Arguments& args);
    // Local<Value> addCollisionShapes(const Arguments& args);
    // Local<Value> addTags(const Arguments& args);
    Local<Value> allowStateMismatchOnPlacement(const Arguments& args);
    // Local<Value> asItemInstance(const Arguments& args);
    Local<Value> attack(const Arguments& args);
    //Local<Value> breaksFallingBlocks(const Arguments& args);
    Local<Value> buildDescriptionId();
    Local<Value> buildDescriptionName();
    Local<Value> buildSerializationIdString();
    Local<Value> cacheComponentData();
    Local<Value> canBeBuiltOver(const Arguments& args);
    Local<Value> canBeFertilized(const Arguments& args);
    Local<Value> canConnect(const Arguments& args);
    Local<Value> canProvideFullSupport(const Arguments& args);
    Local<Value> canProvideMultifaceSupport(const Arguments& args);
    // Local<Value> canProvideSupport(const Arguments& args);
    Local<Value> canSlide(const Arguments& args);
    Local<Value> canSurvive(const Arguments& args);
    Local<Value> causesFreezeEffect();
    Local<Value> checkIsPathable(const Arguments& args);
    // Local<Value> clip(const Arguments& args);
    Local<Value> computeRawSerializationIdHashForNetwork();
    // Local<Value> copyState(const Arguments& args);
    Local<Value> dealsContactDamage(const Arguments& args);
    Local<Value> destroy(const Arguments& args);
    // Local<Value> entityInside(const Arguments& args);
    // Local<Value> executeEvent(const Arguments& args);
    // Local<Value> executeItemEvent(const Arguments& args);
    // Local<Value> executeTrigger(const Arguments& args);
    // Local<Value> forEachState(const Arguments& args);
    // Local<Value> getClientPredictionOverride(const Arguments& args);
    // Local<Value> getCollisionShape(const Arguments& args);
    // Local<Value> getCollisionShapeForCamera(const Arguments& args);
    Local<Value> getComparatorSignal(const Arguments& args);
    // Local<Value> getConnectedDirections(const Arguments& args);
    Local<Value> getDebugText(const Arguments& args);
    Local<Value> getDirectSignal(const Arguments& args);
    // Local<Value> getExperienceDrop(const Arguments& args);
    Local<Value> getIgnoresDestroyPermissions(const Arguments& args);
    // Local<Value> getMapColor(const Arguments& args);
    // Local<Value> getMobToSpawn(const Arguments& args);
    // Local<Value> getOutline(const Arguments& args);
    Local<Value> getPlacementBlock(const Arguments& args);
    Local<Value> getSecondPart(const Arguments& args);
    Local<Value> getVisualShape(const Arguments& args);
    // Local<Value> getVisualShapeInWorld(const Arguments& args);
    // Local<Value> hasProperty(const Arguments& args);
    // Local<Value> hasState(const Arguments& args);
    Local<Value> hasTag(const Arguments& args);
    Local<Value> ignoreEntitiesOnPistonMove();
    Local<Value> isAttachedTo(const Arguments& args);
    // Local<Value> isFilteredOut(const Arguments& args);
    Local<Value> isObstructingChests(const Arguments& args);
    Local<Value> isPartialBlock(const Arguments& args);
    Local<Value> isPreservingMediumWhenPlaced(const Arguments& args);
    Local<Value> isTopPartialBlock(const Arguments& args);
    // Local<Value> keepStates(const Arguments& args);
    Local<Value> mayConsumeFertilizer(const Arguments& args);
    Local<Value> mayPick(const Arguments& args);
    Local<Value> mayPlace(const Arguments& args);
    Local<Value> mayPlaceOn(const Arguments& args);
    Local<Value> movedByPiston(const Arguments& args);
    Local<Value> neighborChanged(const Arguments& args);
    Local<Value> onExploded(const Arguments& args);
    Local<Value> onFallOn(const Arguments& args);
    // Local<Value> onFertilized(const Arguments& args);
    Local<Value> onHitByActivatingAttack(const Arguments& args);
    Local<Value> onLightningHit(const Arguments& args);
    Local<Value> onPlace(const Arguments& args);
    Local<Value> onProjectileHit(const Arguments& args);
    Local<Value> onRemove(const Arguments& args);
    // Local<Value> onStandOn(const Arguments& args);
    Local<Value> onStepOff(const Arguments& args);
    Local<Value> onStepOn(const Arguments& args);
    Local<Value> onStructureBlockPlace(const Arguments& args);
    Local<Value> onStructureNeighborBlockPlace(const Arguments& args);
    Local<Value> playerDestroy(const Arguments& args);
    Local<Value> playerWillDestroy(const Arguments& args);
    // Local<Value> popResource(const Arguments& args);
    Local<Value> pushesOutItems();
    Local<Value> pushesUpFallingBlocks();
    // Local<Value> queuedTick(const Arguments& args);
    // Local<Value> randomTick(const Arguments& args);
    Local<Value> randomlyModifyPosition(const Arguments& args);
    Local<Value> requiresCorrectToolForDrops();
    Local<Value> setRuntimeId(const Arguments& args);
    Local<Value> shouldRandomTick();
    Local<Value> shouldRandomTickExtraLayer();
    Local<Value> shouldStopFalling(const Arguments& args);
    Local<Value> shouldTickOnSetBlock();
    // Local<Value> spawnResources(const Arguments& args);
    Local<Value> telemetryVariant(const Arguments& args);
    Local<Value> toDebugString();
    Local<Value> transformOnFall(const Arguments& args);
    Local<Value> triggerEvent(const Arguments& args);
    // Local<Value> tryGetCopperBehavior();
    Local<Value> tryGetInfested();
    Local<Value> tryGetUninfested();
    // Local<Value> tryToPlace(const Arguments& args);
    Local<Value> tryToTill(const Arguments& args);
    // Local<Value> updateEntityAfterFallOn(const Arguments& args);
    // Local<Value> updateTallestCollisionShape(const Arguments& args);
    Local<Value> use(const Arguments& args);

    //static
    // Local<Value> BLOCK_DESCRIPTION_PREFIX()
    // Local<Value> SIZE_OFFSET()

};

extern ClassDefine<BlockClass> blockClassBuilder;
