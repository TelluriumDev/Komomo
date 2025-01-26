#include "API/Block/Block.h"
#include "API/Actor/Actor.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Math/AABB.h"
#include "API/Player/Player.h"


ClassDefine<BlockClass> blockClassBuilder =
    defineClass<BlockClass>("Block")
        .constructor(nullptr)

        .instanceProperty("allowsRunes", &BlockClass::getAllowsRunes)
        //.instanceProperty("blockEntityType", &BlockClass::getBlockEntityType)
        .instanceProperty("burnOdds", &BlockClass::getBurnOdds)
        // .instanceProperty("defaultState", &BlockClass::getDefaultState)
        .instanceProperty("descriptionId", &BlockClass::getDescriptionId)
        .instanceProperty("destroySpeed", &BlockClass::getDestroySpeed)
        .instanceProperty("flameOdds", &BlockClass::getFlameOdds)
        .instanceProperty("hardness", &BlockClass::getFriction)
        .instanceProperty("explosionResistance", &BlockClass::getExplosionResistance)
        //.instanceProperty("light", &BlockClass::getLight)
        //.instanceProperty("lightEmission", &BlockClass::getLightEmission)
        //.instanceProperty("material", &BlockClass::getMaterial)
        //.instanceProperty("name", &BlockClass::getName)
        .instanceProperty("runtimeId", &BlockClass::getRuntimeId)
        //.instanceProperty("serializationId", &BlockClass::getSerializationId)
        .instanceProperty("thickness", &BlockClass::getThickness)
        .instanceProperty("translucency", &BlockClass::getTranslucency)
        .instanceProperty("variant", &BlockClass::getVariant)

        .instanceProperty("isAir", &BlockClass::isAir)
        .instanceProperty("isBounceBlock", &BlockClass::isBounceBlock)
        .instanceProperty("isButtonBlock", &BlockClass::isButtonBlock)
        .instanceProperty("isContainerBlock", &BlockClass::isContainerBlock)
        .instanceProperty("isCropBlock", &BlockClass::isCropBlock)
        .instanceProperty("isDoorBlock", &BlockClass::isDoorBlock)
        .instanceProperty("isEmpty", &BlockClass::isEmpty)
        .instanceProperty("isFallingBlock", &BlockClass::isFallingBlock)
        .instanceProperty("isFenceBlock", &BlockClass::isFenceBlock)
        .instanceProperty("isFenceGateBlock", &BlockClass::isFenceGateBlock)
        .instanceProperty("isInteractiveBlock", &BlockClass::isInteractiveBlock)
        .instanceProperty("isLavaFlammable", &BlockClass::isLavaFlammable)
        .instanceProperty("isLeverBlock", &BlockClass::isLeverBlock)
        .instanceProperty("isMotionBlockingBlock", &BlockClass::isMotionBlockingBlock)
        .instanceProperty("isMultifaceBlock", &BlockClass::isMultifaceBlock)
        .instanceProperty("isRailBlock", &BlockClass::isRailBlock)
        .instanceProperty("isSignalSource", &BlockClass::isSignalSource)
        .instanceProperty("isSlabBlock", &BlockClass::isSlabBlock)
        .instanceProperty("isSolid", &BlockClass::isSolid)
        .instanceProperty("isSolidBlockingBlock", &BlockClass::isSolidBlockingBlock)
        .instanceProperty("isSolidBlockingBlockAndNotSignalSource", &BlockClass::isSolidBlockingBlockAndNotSignalSource)
        .instanceProperty("isStairBlock", &BlockClass::isStairBlock)
        .instanceProperty("isStemBlock", &BlockClass::isStemBlock)
        .instanceProperty("isThinFenceBlock", &BlockClass::isThinFenceBlock)
        .instanceProperty("isUnbreakable", &BlockClass::isUnbreakable)
        .instanceProperty("isWallBlock", &BlockClass::isWallBlock)
        .instanceProperty("isWaterBlocking", &BlockClass::isWaterBlocking)

        .instanceProperty("canBeBrokenFromFalling", &BlockClass::canBeBrokenFromFalling)
        .instanceProperty("canBeOriginalSurface", &BlockClass::canBeOriginalSurface)
        .instanceProperty("canDamperVibrations", &BlockClass::canDamperVibrations)
        .instanceProperty("canDropWithAnyTool", &BlockClass::canDropWithAnyTool)
        .instanceProperty("canHaveExtraData", &BlockClass::canHaveExtraData)
        .instanceProperty("canHurtAndBreakItem", &BlockClass::canHurtAndBreakItem)
        .instanceProperty("canInstatick", &BlockClass::canInstatick)
        .instanceProperty("canOccludeVibrations", &BlockClass::canOccludeVibrations)
        .instanceProperty("canReactToNeighborsDuringInstatick", &BlockClass::canReactToNeighborsDuringInstatick)

        .instanceProperty("hasBlockEntity", &BlockClass::hasBlockEntity)
        .instanceProperty("hasComparatorSignal", &BlockClass::hasComparatorSignal)

        .InstanceFunction(addAABBs, BlockClass)
        // .InstanceFunction(addCollisionShapes, BlockClass)
        // .InstanceFunction(addTags, BlockClass)
        .InstanceFunction(allowStateMismatchOnPlacement, BlockClass)
        // .InstanceFunction(asItemInstance, BlockClass)
        .InstanceFunction(attack, BlockClass)
        //.InstanceFunction(breaksFallingBlocks, BlockClass)
        .InstanceFunction(buildDescriptionId, BlockClass)
        .InstanceFunction(buildDescriptionName, BlockClass)
        .InstanceFunction(buildSerializationIdString, BlockClass)
        .InstanceFunction(cacheComponentData, BlockClass)
        .InstanceFunction(canBeBuiltOver, BlockClass)
        .InstanceFunction(canBeFertilized, BlockClass)
        .InstanceFunction(canConnect, BlockClass)
        .InstanceFunction(canProvideFullSupport, BlockClass)
        .InstanceFunction(canProvideMultifaceSupport, BlockClass)
        // .InstanceFunction(canProvideSupport, BlockClass)
        .InstanceFunction(canSlide, BlockClass)
        .InstanceFunction(canSurvive, BlockClass)
        .InstanceFunction(causesFreezeEffect, BlockClass)
        .InstanceFunction(checkIsPathable, BlockClass)
        // .InstanceFunction(clip, BlockClass)
        .InstanceFunction(computeRawSerializationIdHashForNetwork, BlockClass)
        // .InstanceFunction(copyState, BlockClass)
        .InstanceFunction(dealsContactDamage, BlockClass)
        .InstanceFunction(destroy, BlockClass)
        // .InstanceFunction(executeEvent, BlockClass)
        // .InstanceFunction(executeItemEvent, BlockClass)
        // .InstanceFunction(executeTrigger, BlockClass)
        .InstanceFunction(finalizeBlockComponentStorage, BlockClass)
        // .InstanceFunction(forEachState, BlockClass)
        // .InstanceFunction(getClientPredictionOverride, BlockClass)
        // .InstanceFunction(getCollisionShape, BlockClass)
        // .InstanceFunction(getCollisionShapeForCamera, BlockClass)
        .InstanceFunction(getColor, BlockClass)
        .InstanceFunction(getComparatorSignal, BlockClass)
        // .InstanceFunction(getConnectedDirections, BlockClass)
        .InstanceFunction(getDebugText, BlockClass)
        .InstanceFunction(getDirectSignal, BlockClass)
        // .InstanceFunction(getExperienceDrop, BlockClass)
        .InstanceFunction(getIgnoresDestroyPermissions, BlockClass)
        // .InstanceFunction(getMapColor, BlockClass)
        // .InstanceFunction(getMobToSpawn, BlockClass)
        // .InstanceFunction(getOutline, BlockClass)
        // .InstanceFunction(getPlacementBlock, BlockClass)
        // .InstanceFunction(getSecondPart, BlockClass)
        // .InstanceFunction(getVisualShape, BlockClass)
        // .InstanceFunction(getVisualShapeInWorld, BlockClass)
        // .InstanceFunction(hasProperty, BlockClass)
        // .InstanceFunction(hasState, BlockClass)
        // .InstanceFunction(hasTag, BlockClass)
        // .InstanceFunction(ignoreEntitiesOnPistonMove, BlockClass)
        // .InstanceFunction(isAttachedTo, BlockClass)
        // .InstanceFunction(isFilteredOut, BlockClass)
        // .InstanceFunction(isObstructingChests, BlockClass)
        // .InstanceFunction(isPartialBlock, BlockClass)
        // .InstanceFunction(isPreservingMediumWhenPlaced, BlockClass)
        // .InstanceFunction(isTopPartialBlock, BlockClass)
        // .InstanceFunction(keepState, BlockClass)
        // .InstanceFunction(keepStates, BlockClass)
        // .InstanceFunction(mayConsumeFertilizer, BlockClass)
        // .InstanceFunction(mayPick, BlockClass)
        // .InstanceFunction(mayPickWithArgs, BlockClass)
        // .InstanceFunction(mayPlace, BlockClass)
        // .InstanceFunction(mayPlaceOn, BlockClass)
        // .InstanceFunction(movedByPiston, BlockClass)
        // .InstanceFunction(neighborChanged, BlockClass)
        // .InstanceFunction(onExploded, BlockClass)
        // .InstanceFunction(onFallOn, BlockClass)
        // .InstanceFunction(onFertilized, BlockClass)
        // .InstanceFunction(onHitByActivatingAttack, BlockClass)
        // .InstanceFunction(onLightningHit, BlockClass)
        // .InstanceFunction(onPlace, BlockClass)
        // .InstanceFunction(onPlayerPlacing, BlockClass)
        // .InstanceFunction(onProjectileHit, BlockClass)
        // .InstanceFunction(onRemove, BlockClass)
        // .InstanceFunction(onStandOn, BlockClass)
        // .InstanceFunction(onStepOff, BlockClass)
        // .InstanceFunction(onStepOn, BlockClass)
        // .InstanceFunction(onStructureBlockPlace, BlockClass)
        // .InstanceFunction(onStructureNeighborBlockPlace, BlockClass)
        // .InstanceFunction(playerDestroy, BlockClass)
        // .InstanceFunction(playerWillDestroy, BlockClass)
        // .InstanceFunction(popResource, BlockClass)
        // .InstanceFunction(pushesOutItems, BlockClass)
        // .InstanceFunction(pushesUpFallingBlocks, BlockClass)
        // .InstanceFunction(queuedTick, BlockClass)
        // .InstanceFunction(randomTick, BlockClass)
        // .InstanceFunction(randomlyModifyPosition, BlockClass)
        // .InstanceFunction(shouldRandomTick, BlockClass)
        // .InstanceFunction(shouldRandomTickExtraLayer, BlockClass)
        // .InstanceFunction(shouldStopFalling, BlockClass)
        // .InstanceFunction(shouldTickOnSetBlock, BlockClass)
        // .InstanceFunction(spawnResources, BlockClass)
        // .InstanceFunction(telemetryVariant, BlockClass)
        // .InstanceFunction(toDebugString, BlockClass)
        // .InstanceFunction(transformOnFall, BlockClass)
        // .InstanceFunction(triggerEvent, BlockClass)
        // .InstanceFunction(tryGetCopperBehavior, BlockClass)
        // .InstanceFunction(tryGetInfested, BlockClass)
        // .InstanceFunction(tryGetUninfested, BlockClass)
        // .InstanceFunction(tryToPlace, BlockClass)
        // .InstanceFunction(tryToTill, BlockClass)
        // .InstanceFunction(updateEntityAfterFallOn, BlockClass)
        // .InstanceFunction(updateTallestCollisionShape, BlockClass)
        // .InstanceFunction(use, BlockClass)
        // .InstanceFunction(waterSpreadCausesSpawn, BlockClass)
        // .InstanceFunction(buildSerializationId, BlockClass)
        // .InstanceFunction(setRuntimeId, BlockClass)
        // .InstanceFunction(_queueForTickBasedOnComponentConfiguration, BlockClass)
        // .InstanceFunction(_removeFromTickingQueues, BlockClass)
        // .InstanceFunction(entityInside, BlockClass)
        .build();

BlockClass::BlockClass(Block* block) : ScriptClass(ConstructFromCpp<BlockClass>{}) { this->mBlock = block; }

Local<Object> BlockClass::newBlock(Block* block) { return (new BlockClass(block))->getScriptObject(); }

#define CallFunction(Type, Function)                                                                                   \
    try {                                                                                                              \
        if (!mBlock) return Local<Value>();                                                                            \
        return Type::new##Type(mBlock->Function);                                                                      \
    }                                                                                                                  \
    Catch;

#define CallVoidMethod(Function)                                                                                       \
    try {                                                                                                              \
        if (!mBlock) return Local<Value>();                                                                            \
        mBlock->Function;                                                                                              \
        return Boolean::newBoolean(true);                                                                              \
    }                                                                                                                  \
    CatchReturn(Boolean::newBoolean(false));

Local<Value> BlockClass::getAllowsRunes() { CallFunction(Boolean, getAllowsRunes()); }
// Local<Value> BlockClass::getBlockEntityType() {}
Local<Value> BlockClass::getBurnOdds() { CallFunction(Number, getBurnOdds()); }
// Local<Value> BlockClass::getDefaultState() {
//     try {
//         if (!mBlock) return Local<Value>();
//         return (new BlockClass(mBlock->getDefaultState()))->getScriptObject();
//     }
//     Catch;
// }
Local<Value> BlockClass::getDescriptionId() { CallFunction(String, getDescriptionId()); }
Local<Value> BlockClass::getDestroySpeed() { CallFunction(Number, getDestroySpeed()); }
Local<Value> BlockClass::getExplosionResistance() { CallFunction(Number, getExplosionResistance()); }
Local<Value> BlockClass::getFlameOdds() { CallFunction(Number, getFlameOdds()); }
Local<Value> BlockClass::getFriction() { CallFunction(Number, getFriction()); }

// symbol: ?getLight@Block@@QEBA?AUBrightness@@XZ
// Local<Value> BlockClass::getLight() { CallFunction(Number, getLight()); }

// Local<Value> BlockClass::getLightEmission() { CallFunction(Number, getLightEmission()); }
// Local<Value> BlockClass::getMaterial() { CallFunction(String, getMaterial()); }

// symbol: ?getName@Block@@QEBAAEBVHashedString@@XZ
// Local<Value> BlockClass::getName() { CallFunction(String, getName()); }

Local<Value> BlockClass::getRuntimeId() { CallFunction(Number, getRuntimeId()); }

// symbol: ?getSerializationId@Block@@QEBAAEBVCompoundTag@@XZ
// Local<Value> BlockClass::getSerializationId() { CallFunction(String, getSerializationId()); }

Local<Value> BlockClass::getThickness() { CallFunction(Number, getThickness()); }
Local<Value> BlockClass::getTranslucency() { CallFunction(Number, getTranslucency()); }
Local<Value> BlockClass::getVariant() { CallFunction(Number, getVariant()); }

Local<Value> BlockClass::isAir() { CallFunction(Boolean, isAir()); }
Local<Value> BlockClass::isBounceBlock() { CallFunction(Boolean, isBounceBlock()); }
Local<Value> BlockClass::isButtonBlock() { CallFunction(Boolean, isButtonBlock()); }
Local<Value> BlockClass::isContainerBlock() { CallFunction(Boolean, isContainerBlock()); }
Local<Value> BlockClass::isCropBlock() { CallFunction(Boolean, isCropBlock()); }
Local<Value> BlockClass::isDoorBlock() { CallFunction(Boolean, isDoorBlock()); }
Local<Value> BlockClass::isEmpty() { CallFunction(Boolean, isEmpty()); }
Local<Value> BlockClass::isFallingBlock() { CallFunction(Boolean, isFallingBlock()); }
Local<Value> BlockClass::isFenceBlock() { CallFunction(Boolean, isFenceBlock()); }
Local<Value> BlockClass::isFenceGateBlock() { CallFunction(Boolean, isFenceGateBlock()); }
Local<Value> BlockClass::isInteractiveBlock() { CallFunction(Boolean, isInteractiveBlock()); }
Local<Value> BlockClass::isLavaFlammable() { CallFunction(Boolean, isLavaFlammable()); }
Local<Value> BlockClass::isLeverBlock() { CallFunction(Boolean, isLeverBlock()); }
Local<Value> BlockClass::isMotionBlockingBlock() { CallFunction(Boolean, isMotionBlockingBlock()); }
Local<Value> BlockClass::isMultifaceBlock() { CallFunction(Boolean, isMultifaceBlock()); }
Local<Value> BlockClass::isRailBlock() { CallFunction(Boolean, isRailBlock()); }
Local<Value> BlockClass::isSignalSource() { CallFunction(Boolean, isSignalSource()); }
Local<Value> BlockClass::isSlabBlock() { CallFunction(Boolean, isSlabBlock()); }
Local<Value> BlockClass::isSolid() { CallFunction(Boolean, isSolid()); }
Local<Value> BlockClass::isSolidBlockingBlock() { CallFunction(Boolean, isSolidBlockingBlock()); }
Local<Value> BlockClass::isSolidBlockingBlockAndNotSignalSource() {
    CallFunction(Boolean, isSolidBlockingBlockAndNotSignalSource());
}
Local<Value> BlockClass::isStairBlock() { CallFunction(Boolean, isStairBlock()); }
Local<Value> BlockClass::isStemBlock() { CallFunction(Boolean, isStemBlock()); }
Local<Value> BlockClass::isThinFenceBlock() { CallFunction(Boolean, isThinFenceBlock()); }
Local<Value> BlockClass::isUnbreakable() { CallFunction(Boolean, isUnbreakable()); }
Local<Value> BlockClass::isWallBlock() { CallFunction(Boolean, isWallBlock()); }
Local<Value> BlockClass::isWaterBlocking() { CallFunction(Boolean, isWaterBlocking()); }

Local<Value> BlockClass::canBeBrokenFromFalling() { CallFunction(Boolean, canBeBrokenFromFalling()); }
Local<Value> BlockClass::canBeOriginalSurface() { CallFunction(Boolean, canBeOriginalSurface()); }
Local<Value> BlockClass::canDamperVibrations() { CallFunction(Boolean, canDamperVibrations()); }
Local<Value> BlockClass::canDropWithAnyTool() { CallFunction(Boolean, canDropWithAnyTool()); }
Local<Value> BlockClass::canHaveExtraData() { CallFunction(Boolean, canHaveExtraData()); }
Local<Value> BlockClass::canHurtAndBreakItem() { CallFunction(Boolean, canHurtAndBreakItem()); }
Local<Value> BlockClass::canInstatick() { CallFunction(Boolean, canInstatick()); }
Local<Value> BlockClass::canOccludeVibrations() { CallFunction(Boolean, canOccludeVibrations()); }
Local<Value> BlockClass::canReactToNeighborsDuringInstatick() {
    CallFunction(Boolean, canReactToNeighborsDuringInstatick());
}

Local<Value> BlockClass::hasBlockEntity() { CallFunction(Boolean, hasBlockEntity()); }
Local<Value> BlockClass::hasComparatorSignal() { CallFunction(Boolean, hasComparatorSignal()); }

// MCAPI void addAABBs(
//         class BlockSource const& region,
//         class BlockPos const&    pos,
//         class AABB const*        intersectTestBox,
//         std::vector<class AABB>& inoutBoxes
//     ) const;
Local<Value> BlockClass::addAABBs(const Arguments& args) {
    CheckArgsCountReturn(args, 4, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], AABBClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[3], ValueKind::kArray, Boolean::newBoolean(false));

    try {
        if (!mBlock) return Local<Value>();
        auto engine           = EngineScope::currentEngine();
        auto region           = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos              = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto intersectTestBox = engine->getNativeInstance<AABBClass>(args[2]);
        auto inoutBoxes       = args[3].asArray();
        auto inoutBoxesVector = std::vector<AABB>(inoutBoxes.size());
        for (decltype(inoutBoxes.size()) i = 0; i < inoutBoxes.size(); i++) {
            CheckInstanceType(array[i], AABBClass);
            auto inputAABB      = engine->getNativeInstance<AABBClass>(inoutBoxes.get(i));
            inoutBoxesVector[i] = *(inputAABB->mAABB);
        }
        mBlock->addAABBs(*region, *pos, intersectTestBox, inoutBoxesVector);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI bool addCollisionShapes(
//     class IConstBlockSource const&                             region,
//     class BlockPos const&                                      pos,
//     class AABB const*                                          intersectTestBox,
//     std::vector<class AABB>&                                   inoutBoxes,
//     class optional_ref<class GetCollisionShapeInterface const> entity
// ) const;
// Local<Value> BlockClass::addCollisionShapes(const Arguments& args) { CallVoidMethod(addCollisionShapes, shapes); }

// MCAPI class Block& addTag(class HashedString const& tag);
// Local<Value> BlockClass::addTags(const Arguments& args) { }

Local<Value> BlockClass::allowStateMismatchOnPlacement(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockClass);
    try {
        if (!mBlock) return Local<Value>();
        auto other = EngineScope::currentEngine()->getNativeInstance<BlockClass>(args[0])->mBlock;
        return Boolean::newBoolean(mBlock->allowStateMismatchOnPlacement(*other));
    }
    Catch;
}

// MCAPI class ItemInstance asItemInstance(class BlockSource& region, class BlockPos const& pos) const;

// MCAPI class ItemInstance
// asItemInstance(class BlockSource& region, class BlockPos const& position, bool withData) const;
// Local<Value> BlockClass::asItemInstance(const Arguments& args) { CallFunction(ItemInstance, asItemInstance, state); }

Local<Value> BlockClass::attack(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], PlayerClass);
    CheckInstanceType(args[1], BlockPosClass);

    try {
        auto engine = EngineScope::currentEngine();
        auto player = engine->getNativeInstance<PlayerClass>(args[0])->mPlayer;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->attack(player, *pos));
    }
    Catch;
}

// MCAPI bool breaksFallingBlocks(class BaseGameVersion version) const;
// Local<Value> BlockClass::breaksFallingBlocks(const Arguments& args) { }

Local<Value> BlockClass::buildDescriptionId() { CallFunction(String, buildDescriptionId()); }
Local<Value> BlockClass::buildDescriptionName() { CallFunction(String, buildDescriptionName()); }
Local<Value> BlockClass::buildSerializationIdString() { CallFunction(String, buildSerializationIdString()); }
Local<Value> BlockClass::cacheComponentData() { CallVoidMethod(cacheComponentData()); }
Local<Value> BlockClass::canBeBrokenFromFalling() { CallFunction(Boolean, canBeBrokenFromFalling()); }

// MCAPI bool canBeBuiltOver(class BlockSource& region, class BlockPos const& pos) const;

// MCAPI bool
// canBeBuiltOver(class BlockSource& region, class BlockPos const& pos, class BlockItem const& newItem) const;
Local<Value> BlockClass::canBeBuiltOver(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    // another overload not implemented: BlockItem not implemented.
    try {
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->canBeBuiltOver(*region, *pos));
    }
    Catch;
}
Local<Value> BlockClass::canBeFertilized(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckInstanceType(args[2], BlockClass);
    try {
        auto engine     = EngineScope::currentEngine();
        auto region     = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos        = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto aboveBlock = engine->getNativeInstance<BlockClass>(args[2])->mBlock;
        return Boolean::newBoolean(mBlock->canBeFertilized(*region, *pos, *aboveBlock));
    }
    Catch;
}
Local<Value> BlockClass::canConnect(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockClass);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckInstanceType(args[2], BlockClass);
    try {
        if (!mBlock) return Local<Value>();
        auto  engine     = EngineScope::currentEngine();
        auto  otherBlock = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        uchar toOther    = args[1].asNumber().toInt32();
        auto  thisBlock  = engine->getNativeInstance<BlockClass>(args[2])->mBlock;
        return Boolean::newBoolean(mBlock->canConnect(*otherBlock, toOther, *thisBlock));
    }
    Catch;
}
Local<Value> BlockClass::canProvideFullSupport(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto face = static_cast<uchar>(args[0].asNumber().toInt32());
        return Boolean::newBoolean(mBlock->canProvideFullSupport(face));
    }
    Catch;
}
Local<Value> BlockClass::canProvideMultifaceSupport(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto face = static_cast<uchar>(args[0].asNumber().toInt32());
        return Boolean::newBoolean(mBlock->canProvideMultifaceSupport(face));
    }
    Catch;
}

// BlockSupportType not implemented
// MCAPI bool canProvideSupport(uchar face, ::BlockSupportType type) const;
// Local<Value> BlockClass::canProvideSupport(const Arguments& args) { CallFunction(Boolean, canProvideSupport()); }

Local<Value> BlockClass::canSlide(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->canSlide(*region, *pos));
    }
    Catch;
}

Local<Value> BlockClass::canSurvive(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->canSurvive(*region, *pos));
    }
    Catch;
}

Local<Value> BlockClass::causesFreezeEffect() { CallFunction(Boolean, causesFreezeEffect()); }

Local<Value> BlockClass::checkIsPathable(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], ActorClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckInstanceType(args[2], BlockPosClass);
    try {
        auto engine      = EngineScope::currentEngine();
        auto entity      = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto lastPathPos = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto pathPos     = engine->getNativeInstance<BlockPosClass>(args[2])->mBlockPos;
        return Boolean::newBoolean(mBlock->checkIsPathable(*entity, *start, *end));
    }
    Catch;
}

// HitResult not implemented
// MCAPI class HitResult clip(class BlockPos const&, class Vec3 const&, class Vec3 const&, class AABB const&) const;
//
// MCAPI class HitResult
// clip(class BlockSource const&, class BlockPos const&, class Vec3 const&, class Vec3 const&, ::ShapeType, class
// optional_ref<class GetCollisionShapeInterface const>)
//     const;
// Local<Value> BlockClass::clip(const Arguments& args) {}

Local<Value> BlockClass::computeRawSerializationIdHashForNetwork() {
    CallFunction(Number, computeRawSerializationIdHashForNetwork());
}

// BlockState not implemented
// MCAPI class Block const& copyState(class Block const& fromBlock, class BlockState const& state) const;
// Local<Value> BlockClass::copyState(const Arguments& args) { }

Local<Value> BlockClass::dealsContactDamage(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ActorClass);
    CheckArgType(args[1], ValueKind::kBoolean);
    try {
        auto engine        = EngineScope::currentEngine();
        auto actor         = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto isPathFinding = args[1].asBoolean().value();
        return Boolean::newBoolean(mBlock->dealsContactDamage(*actor, isPathFinding));
    }
    Catch;
}

Local<Value> BlockClass::destroy(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    try {
        auto engine       = EngineScope::currentEngine();
        auto region       = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos          = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entitySource = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        mBlock->destroy(*region, *pos, entitySource);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI void executeEvent(std::string const& name, class RenderParams& params) const;
// Local<Value> BlockClass::executeEvent(const Arguments& args) {}

// ItemStackBase not implemented
// MCAPI void executeItemEvent(
//         class ItemStackBase&  item,
//         std::string const&    eventName,
//         class BlockSource&    region,
//         class BlockPos const& pos,
//         class Actor*          actor
//     ) const;
// Local<Value> BlockClass::executeItemEvent(const Arguments& args) {}

Local<Value> BlockClass::finalizeBlockComponentStorage() { CallVoidMethod(finalizeBlockComponentStorage()); }

// BlockState not implemented
// MCAPI void forEachState(std::function<bool(class BlockState const&, int)> callback) const;
// Local<Value> BlockClass::forEachState(const Arguments& args) {}

// MCAPI bool getClientPredictionOverride(::BlockClientPredictionOverrides) const;
// Local<Value> getClientPredictionOverride(const Arguments& args) {}

// MCAPI bool getCollisionShape(
//         class AABB&                                                outAABB,
//         class IConstBlockSource const&                             region,
//         class BlockPos const&                                      pos,
//         class optional_ref<class GetCollisionShapeInterface const> entity
//     ) const;
// Local<Value> BlockClass::getCollisionShape(const Arguments& args) {}

// MCAPI bool getCollisionShapeForCamera(class AABB&, class IConstBlockSource const&, class BlockPos const&) const;
// Local<Value> BlockClass::getCollisionShapeForCamera(const Arguments& args) {}

Local<Value> BlockClass::getColor(const Arguments& args) {
    if (!mBlock) {
        return Local<Value>();
    }
    auto argsCount = args.size();
    switch (argsCount) {
    case size_t(0):
        return Number::newNumber(mBlock->getColor());
    case size_t(2):
        CheckInstanceType(args[0], BlockSourceClass);
        CheckInstanceType(args[1], BlockPosClass);
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Number::newNumber(mBlock->getColor(*region, *pos));
    default:
        PrintWrongArgsCount() return Local<Value>();
    }
}

Local<Value> BlockClass::getComparatorSignal(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    try {
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto dir    = static_cast<uchar>(args[2].asNumber().toInt32());
        return Number::newNumber(mBlock->getComparatorSignal(*region, *pos, dir));
    }
    Catch;
}

// MCAPI struct BlockLegacy::HorizontalDirectionBits
// getConnectedDirections(class BlockPos const& pos, class BlockSource& region) const;
// Local<Value> BlockClass::getConnectedDirections(const Arguments& args) { }

Local<Value> BlockClass::getDebugText(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kArray, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        auto outputInfo       = args[0].asArray();
        auto outputInfoVector = std::vector<std::string>(outputInfo.size());
        for (decltype(outputInfo.size()) i = 0; i < outputInfo.size(); i++) {
            CheckArgType(array[i], ValueKind::kString);
            outputInfoVector[i] = args[0].asArray().get(i).asString().toString();
        }
        auto pos = EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->getDebugText(outputInfoVector, *pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::getDirectSignal(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    try {
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto dir    = args[2].asNumber().toInt32();
        return Number::newNumber(mBlock->getDirectSignal(*region, *pos, dir));
    }
    Catch;
}

// MCAPI int getExperienceDrop(class Random& random) const;
// Local<Value> BlockClass::getExperienceDrop(const Arguments& args) {}

Local<Value> BlockClass::getIgnoresDestroyPermissions(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ActorClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        auto engine = EngineScope::currentEngine();
        auto entity  = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->getIgnoresDestroyPermissions(*entity, *pos));
    }
    Catch;
}