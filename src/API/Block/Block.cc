#include "API/Block/Block.h"

#include "API/Actor/Actor.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Item/ItemStack.h"
#include "API/Math/AABB.h"
#include "API/Math/Vec3.h"
#include "API/Player/Player.h"

using namespace Komomo;

ClassDefine<BlockClass> blockClassBuilder =
    defineClass<BlockClass>("Block")
        .constructor(nullptr)

        .instanceProperty("allowsRunes", &BlockClass::getAllowsRunes)
        //.instanceProperty("blockEntityType", &BlockClass::getBlockEntityType)
        // .instanceProperty("blockTintType", &BlockClass::getBlockTintType)
        .instanceProperty("blockItemId", &BlockClass::getBlockItemId)
        .instanceProperty("burnOdds", &BlockClass::getBurnOdds)
        .instanceProperty("data", &BlockClass::getData)
        // .instanceProperty("defaultState", &BlockClass::getDefaultState)
        .instanceProperty("descriptionId", &BlockClass::getDescriptionId)
        .instanceProperty("flameOdds", &BlockClass::getFlameOdds)
        .instanceProperty("hardness", &BlockClass::getFriction)
        .instanceProperty("explosionResistance", &BlockClass::getExplosionResistance)
        //.instanceProperty("light", &BlockClass::getLight)
        //.instanceProperty("lightEmission", &BlockClass::getLightEmission)
        //.instanceProperty("material", &BlockClass::getMaterial)
        .instanceProperty("runtimeId", &BlockClass::getRuntimeId)
        //.instanceProperty("serializationId", &BlockClass::getSerializationId)
        .instanceProperty("thickness", &BlockClass::getThickness)
        .instanceProperty("translucency", &BlockClass::getTranslucency)
        .instanceProperty("typeName", &BlockClass::getTypeName)
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

        .instanceProperty("canBeBrokenFromFalling", &BlockClass::canBeBrokenFromFalling)
        .instanceProperty("canBeOriginalSurface", &BlockClass::canBeOriginalSurface)
        .instanceProperty("canHaveExtraData", &BlockClass::canHaveExtraData)
        .instanceProperty("canHurtAndBreakItem", &BlockClass::canHurtAndBreakItem)
        .instanceProperty("canInstatick", &BlockClass::canInstatick)
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
        // .InstanceFunction(entityInside, BlockClass)
        // .InstanceFunction(executeEvent, BlockClass)
        // .InstanceFunction(executeItemEvent, BlockClass)
        // .InstanceFunction(executeTrigger, BlockClass)
        // .InstanceFunction(forEachState, BlockClass)
        // .InstanceFunction(getClientPredictionOverride, BlockClass)
        // .InstanceFunction(getCollisionShape, BlockClass)
        // .InstanceFunction(getCollisionShapeForCamera, BlockClass)
        .InstanceFunction(getComparatorSignal, BlockClass)
        // .InstanceFunction(getConnectedDirections, BlockClass)
        .InstanceFunction(getDebugText, BlockClass)
        .InstanceFunction(getDestroySpeed, BlockClass)
        .InstanceFunction(getDirectSignal, BlockClass)
        // .InstanceFunction(getExperienceDrop, BlockClass)
        .InstanceFunction(getIgnoresDestroyPermissions, BlockClass)
        // .InstanceFunction(getMapColor, BlockClass)
        // .InstanceFunction(getMobToSpawn, BlockClass)
        // .InstanceFunction(getOutline, BlockClass)
        .InstanceFunction(getPlacementBlock, BlockClass)
        .InstanceFunction(getSecondPart, BlockClass)
        .InstanceFunction(getVisualShape, BlockClass)
        // .InstanceFunction(getVisualShapeInWorld, BlockClass)
        // .InstanceFunction(hasProperty, BlockClass)
        // .InstanceFunction(hasState, BlockClass)
        .InstanceFunction(hasTag, BlockClass)
        .InstanceFunction(ignoreEntitiesOnPistonMove, BlockClass)
        .InstanceFunction(isAttachedTo, BlockClass)
        // .InstanceFunction(isFilteredOut, BlockClass)
        .InstanceFunction(isObstructingChests, BlockClass)
        .InstanceFunction(isPartialBlock, BlockClass)
        .InstanceFunction(isPreservingMediumWhenPlaced, BlockClass)
        .InstanceFunction(isTopPartialBlock, BlockClass)
        // .InstanceFunction(keepStates, BlockClass)
        .InstanceFunction(mayConsumeFertilizer, BlockClass)
        .InstanceFunction(mayPick, BlockClass)
        .InstanceFunction(mayPlace, BlockClass)
        .InstanceFunction(mayPlaceOn, BlockClass)
        .InstanceFunction(movedByPiston, BlockClass)
        .InstanceFunction(neighborChanged, BlockClass)
        .InstanceFunction(onExploded, BlockClass)
        .InstanceFunction(onFallOn, BlockClass)
        // .InstanceFunction(onFertilized, BlockClass)
        .InstanceFunction(onHitByActivatingAttack, BlockClass)
        .InstanceFunction(onLightningHit, BlockClass)
        .InstanceFunction(onPlace, BlockClass)
        .InstanceFunction(onProjectileHit, BlockClass)
        .InstanceFunction(onRemove, BlockClass)
        // .InstanceFunction(onStandOn, BlockClass)
        .InstanceFunction(onStepOff, BlockClass)
        .InstanceFunction(onStepOn, BlockClass)
        .InstanceFunction(onStructureBlockPlace, BlockClass)
        .InstanceFunction(onStructureNeighborBlockPlace, BlockClass)
        .InstanceFunction(playerDestroy, BlockClass)
        .InstanceFunction(playerWillDestroy, BlockClass)
        // .InstanceFunction(popResource, BlockClass)
        .InstanceFunction(pushesOutItems, BlockClass)
        .InstanceFunction(pushesUpFallingBlocks, BlockClass)
        // .InstanceFunction(queuedTick, BlockClass)
        // .InstanceFunction(randomTick, BlockClass)
        .InstanceFunction(randomlyModifyPosition, BlockClass)
        .InstanceFunction(requiresCorrectToolForDrops, BlockClass)
        .InstanceFunction(setRuntimeId, BlockClass)
        .InstanceFunction(shouldRandomTick, BlockClass)
        .InstanceFunction(shouldRandomTickExtraLayer, BlockClass)
        .InstanceFunction(shouldStopFalling, BlockClass)
        .InstanceFunction(shouldTickOnSetBlock, BlockClass)
        // .InstanceFunction(spawnResources, BlockClass)
        .InstanceFunction(telemetryVariant, BlockClass)
        .InstanceFunction(toDebugString, BlockClass)
        .InstanceFunction(transformOnFall, BlockClass)
        .InstanceFunction(triggerEvent, BlockClass)
        // .InstanceFunction(tryGetCopperBehavior, BlockClass)
        .InstanceFunction(tryGetInfested, BlockClass)
        .InstanceFunction(tryGetUninfested, BlockClass)
        // .InstanceFunction(tryToPlace, BlockClass)
        .InstanceFunction(tryToTill, BlockClass)
        // .InstanceFunction(updateEntityAfterFallOn, BlockClass)
        // .InstanceFunction(updateTallestCollisionShape, BlockClass)
        .InstanceFunction(use, BlockClass)

        // static
        //  .function(BLOCK_DESCRIPTION_PREFIX, BlockClass)
        //  .function(SIZE_OFFSET, BlockClass)
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

// MCAPI ::BlockTintType getBlockTintType() const;
//  Local<Value> BlockClass::getBlockTintType() { CallFunction(Number, getBlockTintType()); }
Local<Value> BlockClass::getBlockItemId() { CallFunction(Number, getBlockItemId()); }
Local<Value> BlockClass::getBurnOdds() { CallFunction(Number, getBurnOdds()); }
Local<Value> BlockClass::getData() { CallFunction(Number, getData()); }
Local<Value> BlockClass::getDescriptionId() { CallFunction(String, getDescriptionId()); }

Local<Value> BlockClass::getExplosionResistance() { CallFunction(Number, getExplosionResistance()); }
Local<Value> BlockClass::getFlameOdds() { CallFunction(Number, getFlameOdds()); }
Local<Value> BlockClass::getFriction() { CallFunction(Number, getFriction()); }

// symbol: ?getLight@Block@@QEBA?AUBrightness@@XZ
// Local<Value> BlockClass::getLight() { CallFunction(Number, getLight()); }

// Local<Value> BlockClass::getLightEmission() { CallFunction(Number, getLightEmission()); }
// Local<Value> BlockClass::getMaterial() { CallFunction(String, getMaterial()); }

Local<Value> BlockClass::getRuntimeId() { CallFunction(Number, getRuntimeId()); }

// symbol: ?getSerializationId@Block@@QEBAAEBVCompoundTag@@XZ
// Local<Value> BlockClass::getSerializationId() { CallFunction(String, getSerializationId()); }

Local<Value> BlockClass::getThickness() { CallFunction(Number, getThickness()); }
Local<Value> BlockClass::getTranslucency() { CallFunction(Number, getTranslucency()); }
Local<Value> BlockClass::getTypeName() { CallFunction(String, getTypeName()); };
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

Local<Value> BlockClass::canBeBrokenFromFalling() { CallFunction(Boolean, canBeBrokenFromFalling()); }
Local<Value> BlockClass::canBeOriginalSurface() { CallFunction(Boolean, canBeOriginalSurface()); }
Local<Value> BlockClass::canHaveExtraData() { CallFunction(Boolean, canHaveExtraData()); }
Local<Value> BlockClass::canHurtAndBreakItem() { CallFunction(Boolean, canHurtAndBreakItem()); }
Local<Value> BlockClass::canInstatick() { CallFunction(Boolean, canInstatick()); }
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
        auto intersectTestBox = engine->getNativeInstance<AABBClass>(args[2])->mAABB;
        auto inoutBoxes       = args[3].asArray();
        auto inoutBoxesVector = std::vector<AABB>(inoutBoxes.size());
        for (decltype(inoutBoxes.size()) i = 0; i < inoutBoxes.size(); i++) {
            auto value = inoutBoxes.get(i);
            CheckInstanceType(value, AABBClass);
            auto inputAABB      = engine->getNativeInstance<AABBClass>(value);
            inoutBoxesVector[i] = *(inputAABB->mAABB);
        }
        mBlock->addAABBs(*region, pos, intersectTestBox, inoutBoxesVector);
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
        auto player = engine->getNativeInstance<PlayerClass>(args[0])->get();
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->attack(player, pos));
    }
    Catch;
}

// MCAPI bool breaksFallingBlocks(class BaseGameVersion version) const;
// Local<Value> BlockClass::breaksFallingBlocks(const Arguments& args) { }

Local<Value> BlockClass::buildDescriptionId() { CallFunction(String, buildDescriptionId()); }
Local<Value> BlockClass::buildDescriptionName() { CallFunction(String, buildDescriptionName()); }
Local<Value> BlockClass::buildSerializationIdString() { CallFunction(String, buildSerializationIdString()); }
Local<Value> BlockClass::cacheComponentData() { CallVoidMethod(cacheComponentData()); }

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
        return Boolean::newBoolean(mBlock->canBeBuiltOver(*region, pos));
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
        return Boolean::newBoolean(mBlock->canBeFertilized(*region, pos, *aboveBlock));
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
        auto  otherBlock = engine->getNativeInstance<BlockClass>(args[0])->mBlock;
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
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->canSlide(*region, pos));
    }
    Catch;
}

Local<Value> BlockClass::canSurvive(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->canSurvive(*region, pos));
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
        if (!mBlock) return Local<Value>();
        auto engine      = EngineScope::currentEngine();
        auto entity      = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto lastPathPos = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto pathPos     = engine->getNativeInstance<BlockPosClass>(args[2])->mBlockPos;
        return Boolean::newBoolean(mBlock->checkIsPathable(*entity, lastPathPos, pathPos));
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
        if (!mBlock) return Local<Value>();
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
        if (!mBlock) return Local<Value>();
        auto engine       = EngineScope::currentEngine();
        auto region       = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos          = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entitySource = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        mBlock->destroy(*region, pos, entitySource);
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

// BlockState not implemented
// MCAPI void forEachState(std::function<bool(class BlockState const&, int)> callback) const;
// Local<Value> BlockClass::forEachState(const Arguments& args) {}

// MCAPI ::BlockState const* getBlockState(::HashedString const& name) const;
// Local<Value> getBlockState(const Arguments& args) {}

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

Local<Value> BlockClass::getComparatorSignal(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto dir    = static_cast<uchar>(args[2].asNumber().toInt32());
        return Number::newNumber(mBlock->getComparatorSignal(*region, pos, dir));
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
        if (!mBlock) return Local<Value>();
        auto outputInfo       = args[0].asArray();
        auto outputInfoVector = std::vector<std::string>(outputInfo.size());
        for (decltype(outputInfo.size()) i = 0; i < outputInfo.size(); i++) {
            auto value = outputInfo.get(i);
            CheckArgType(value, ValueKind::kString);
            outputInfoVector[i] = value.asString().toString();
        }
        auto pos = EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->getDebugText(outputInfoVector, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI float getDestroySpeed() const;
// MCAPI float getDestroySpeed(::ItemStackBase const& item) const; //not implemented
Local<Value> BlockClass::getDestroySpeed(const Arguments& args) { CallFunction(Number, getDestroySpeed()); }

Local<Value> BlockClass::getDirectSignal(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto dir    = args[2].asNumber().toInt32();
        return Number::newNumber(mBlock->getDirectSignal(*region, pos, dir));
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
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto entity = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->getIgnoresDestroyPermissions(*entity, pos));
    }
    Catch;
}

// MCAPI ::mce::Color getMapColor(::BlockSource& region, ::BlockPos const& pos) const;
// Local<Value> BlockClass::getMapColor(const Arguments& args) {}

// MCAPI ::MobSpawnerData const* getMobToSpawn(::SpawnConditions const& conditions, ::BlockSource& region) const;
// Local<Value> BlockClass::getMobToSpawn(const Arguments& args) {}

// MCAPI ::AABB const& getOutline(::IConstBlockSource const& region, ::BlockPos const& pos, ::AABB& bufferValue) const;
// Local<Value> BlockClass::getOutline(const Arguments& args) {}

Local<Value> BlockClass::getPlacementBlock(const Arguments& args) {
    CheckArgsCount(args, 5);
    CheckInstanceType(args[0], ActorClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    CheckInstanceType(args[3], Vec3Class);
    CheckArgType(args[4], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto  engine    = EngineScope::currentEngine();
        auto  by        = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto  pos       = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto  face      = static_cast<uchar>(args[2].asNumber().toInt32());
        auto  clickPos  = engine->getNativeInstance<Vec3Class>(args[3])->mVec3;
        auto  itemValue = args[4].asNumber().toInt32();
        auto& result    = const_cast<Block&>(mBlock->getPlacementBlock(*by, pos, face, clickPos, itemValue));
        return BlockClass::newBlock(&result);
    }
    Catch;
}

Local<Value> BlockClass::getSecondPart(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckInstanceType(args[2], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto out    = engine->getNativeInstance<BlockPosClass>(args[2])->mBlockPos;
        return Boolean::newBoolean(mBlock->getSecondPart(*region, pos, out));
    }
    Catch;
}

Local<Value> BlockClass::getVisualShape(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], AABBClass);
    try {
        if (!mBlock) return Local<Value>();
        auto bufferAABB = EngineScope::currentEngine()->getNativeInstance<AABBClass>(args[0])->mAABB;
        auto shape      = mBlock->getVisualShape(*bufferAABB);
        return (new AABBClass(&shape))->getScriptObject();
    }
    Catch;
}

// MCAPI ::AABB const&
//     getVisualShapeInWorld(::IConstBlockSource const& region, ::BlockPos const& pos, ::AABB& bufferAABB) const;
// Local<Value> BlockClass::getVisualShapeInWorld(const Arguments& args) {}

// BlockProperty not implemented
// MCAPI bool hasProperty(::BlockProperty type) const;
// Local<Value> BlockClass::hasProperty(const Arguments& args) {}

// BlockState not implemented
// MCAPI bool hasState(::BlockState const& stateType) const;
// Local<Value> BlockClass::hasState(const Arguments& args) {}

// another overload: HashedString not implemented
// MCAPI bool hasTag(::HashedString const& tagName) const;
Local<Value> BlockClass::hasTag(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mBlock) return Local<Value>();
        auto hash = static_cast<uint64>(args[0].asNumber().toInt64());
        return Boolean::newBoolean(mBlock->hasTag(hash));
    }
    Catch;
}

Local<Value> BlockClass::ignoreEntitiesOnPistonMove() { CallVoidMethod(ignoreEntitiesOnPistonMove()); }

Local<Value> BlockClass::isAttachedTo(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckInstanceType(args[2], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine        = EngineScope::currentEngine();
        auto region        = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos           = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto outAttachedTo = engine->getNativeInstance<BlockPosClass>(args[2])->mBlockPos;
        return Boolean::newBoolean(mBlock->isAttachedTo(*region, pos, outAttachedTo));
    }
    Catch;
}

// BlockRenderLayer not implemented
// MCAPI bool isFilteredOut(::BlockRenderLayer heldItemRenderLayer) const;
// Local<Value> BlockClass::isFaceSturdy(const Arguments& args) {}

Local<Value> BlockClass::isObstructingChests(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->isObstructingChests(*region, pos));
    }
    Catch;
}

Local<Value> BlockClass::isPartialBlock(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->isPartialBlock(*region, pos));
    }
    Catch;
}

Local<Value> BlockClass::isPreservingMediumWhenPlaced(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto medium = engine->getNativeInstance<BlockClass>(args[0])->mBlock;
        return Boolean::newBoolean(mBlock->isPreservingMediumWhenPlaced(*medium));
    }
    Catch;
}

Local<Value> BlockClass::isTopPartialBlock(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->isTopPartialBlock(*region, pos));
    }
    Catch;
}

// BlockState not implemented
// MCAPI ::Block const& keepStates(::std::vector<::BlockState const*> const& statesToKeep) const;
// Local<Value> BlockClass::keepStates(const Arguments& args) { }

Local<Value> BlockClass::mayConsumeFertilizer(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockSourceClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        return Boolean::newBoolean(mBlock->mayConsumeFertilizer(*region));
    }
    Catch;
}

Local<Value> BlockClass::mayPick(const Arguments& args) {
    if (!mBlock) return Local<Value>();
    switch (args.size()) {
    case size_t(0):
        return Boolean::newBoolean(mBlock->mayPick());
    case size_t(2): {
        CheckInstanceType(args[0], BlockSourceClass);
        CheckArgType(args[1], ValueKind::kBoolean);
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto liquid = args[1].asBoolean().value();
        return Boolean::newBoolean(mBlock->mayPick(*region, liquid));
    }
    default:
        PrintWrongArgsCount();
        return Local<Value>();
    }
}

Local<Value> BlockClass::mayPlace(const Arguments& args) {
    if (!mBlock) return Local<Value>();
    switch (args.size()) {
    case size_t(2): {
        CheckInstanceType(args[0], BlockSourceClass);
        CheckInstanceType(args[1], BlockPosClass);
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->mayPlace(*region, pos));
    }
    case size_t(3): {
        CheckInstanceType(args[0], BlockSourceClass);
        CheckInstanceType(args[1], BlockPosClass);
        CheckArgType(args[2], ValueKind::kNumber);
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto face   = static_cast<uchar>(args[2].asNumber().toInt32());
        return Boolean::newBoolean(mBlock->mayPlace(*region, pos, face));
    }
    default:
        PrintWrongArgsCount();
        return Local<Value>();
    }
}

Local<Value> BlockClass::mayPlaceOn(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Boolean::newBoolean(mBlock->mayPlaceOn(*region, pos));
    }
    Catch;
}

Local<Value> BlockClass::movedByPiston(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->movedByPiston(*region, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::neighborChanged(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine      = EngineScope::currentEngine();
        auto region      = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos         = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto neighborPos = engine->getNativeInstance<BlockPosClass>(args[2])->mBlockPos;
        mBlock->neighborChanged(*region, pos, neighborPos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onExploded(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine       = EngineScope::currentEngine();
        auto region       = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos          = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entitySource = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        mBlock->onExploded(*region, pos, entitySource);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onFallOn(const Arguments& args) {
    CheckArgsCountReturn(args, 4, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[3], ValueKind::kBoolean, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine       = EngineScope::currentEngine();
        auto region       = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos          = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entity       = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        auto fallDistance = args[3].asNumber().toFloat();
        mBlock->onFallOn(*region, pos, *entity, fallDistance);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// FertilizerType not implemented
// MCAPI bool
// onFertilized(::BlockSource& region, ::BlockPos const& pos, ::Actor* entity, ::FertilizerType fType) const;
// Local<Value> BlockClass::onFertilized(const Arguments& args) {}

Local<Value> BlockClass::onHitByActivatingAttack(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine      = EngineScope::currentEngine();
        auto region      = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos         = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto sourceActor = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        mBlock->onHitByActivatingAttack(*region, pos, sourceActor);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onLightningHit(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onLightningHit(*region, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onPlace(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], BlockClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine        = EngineScope::currentEngine();
        auto region        = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos           = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto previousBlock = engine->getNativeInstance<BlockClass>(args[2])->mBlock;
        mBlock->onPlace(*region, pos, *previousBlock);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onProjectileHit(const Arguments& args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine     = EngineScope::currentEngine();
        auto region     = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos        = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto projectile = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        mBlock->onProjectileHit(*region, pos, *projectile);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onRemove(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onRemove(*region, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// EntityContext not implemented
// MCAPI void onStandOn(::EntityContext& entity, ::BlockPos const& pos) const;
// Local<Value> BlockClass::onStandOn(const Arguments& args) {}

Local<Value> BlockClass::onStepOff(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto entity = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onStepOff(*entity, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onStepOn(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], ActorClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto entity = engine->getNativeInstance<ActorClass>(args[0])->mActor;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onStepOn(*entity, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onStructureBlockPlace(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onStructureBlockPlace(*region, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::onStructureNeighborBlockPlace(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->onStructureNeighborBlockPlace(*region, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::playerDestroy(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], PlayerClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto player = engine->getNativeInstance<PlayerClass>(args[0])->get();
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        mBlock->playerDestroy(*player, pos);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::playerWillDestroy(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], PlayerClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto player = engine->getNativeInstance<PlayerClass>(args[0])->get();
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto result = const_cast<Block*>(mBlock->playerWillDestroy(*player, pos));
        return BlockClass::newBlock(result);
    }
    Catch;
}

// ItemInstance, ItemActor not implemented
// MCAPI ::ItemActor*
//     popResource(::BlockSource& region, ::BlockPos const& pos, ::ItemInstance const& itemInstance) const;
// Local<Value> BlockClass::popResource(const Arguments& args) { }

Local<Value> BlockClass::pushesOutItems() { CallFunction(Boolean, pushesOutItems()); }

Local<Value> BlockClass::pushesUpFallingBlocks() { CallFunction(Boolean, pushesUpFallingBlocks()); }

// Random not implemented
// MCAPI void queuedTick(::BlockSource& region, ::BlockPos const& pos, ::Random& random) const;
// Local<Value> BlockClass::queuedTick(const Arguments& args) { }

// Random not implemented
// MCAPI void randomTick(::BlockSource& region, ::BlockPos const& pos, ::Random& random) const;
// Local<Value> BlockClass::randomTick(const Arguments& args) { }

Local<Value> BlockClass::randomlyModifyPosition(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto pos    = EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos;
        auto result = mBlock->randomlyModifyPosition(pos);
        return (new Vec3Class(result))->getScriptObject();
    }
    Catch;
}

Local<Value> BlockClass::requiresCorrectToolForDrops() { CallFunction(Boolean, requiresCorrectToolForDrops()); }

Local<Value> BlockClass::setRuntimeId(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto runtimeId = static_cast<uint>(args[0].asNumber().toInt64());
        mBlock->setRuntimeId(runtimeId);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::shouldRandomTick() { CallFunction(Boolean, shouldRandomTick()); }

Local<Value> BlockClass::shouldRandomTickExtraLayer() { CallFunction(Boolean, shouldRandomTickExtraLayer()); }

Local<Value> BlockClass::shouldStopFalling(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckInstanceType(args[0], ActorClass);
    try {
        if (!mBlock) return Local<Value>();
        auto entity = EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor;
        return Boolean::newBoolean(mBlock->shouldStopFalling(*entity));
    }
    Catch;
}

Local<Value> BlockClass::shouldTickOnSetBlock() { CallFunction(Boolean, shouldTickOnSetBlock()); }


// MCAPI void spawnResources(
//         ::BlockSource&                region,
//         ::BlockPos const&             pos,
//         ::Randomize&                  randomize,
//         ::ResourceDropsContext const& resourceDropsContext
//     ) const;
// Local<Value> BlockClass::spawnResources(const Arguments& args) { }

Local<Value> BlockClass::telemetryVariant(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        return Number::newNumber(mBlock->telemetryVariant(*region, pos));
    }
    Catch;
}

Local<Value> BlockClass::toDebugString() { CallFunction(String, toDebugString()); }

Local<Value> BlockClass::transformOnFall(const Arguments& args) {
    CheckArgsCountReturn(args, 4, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[2], ActorClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[3], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine       = EngineScope::currentEngine();
        auto region       = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos          = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entity       = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        auto fallDistance = args[3].asNumber().toInt32();
        mBlock->transformOnFall(*region, pos, entity, fallDistance);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> BlockClass::triggerEvent(const Arguments& args) {
    CheckArgsCountReturn(args, 4, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], BlockSourceClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[3], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto b0     = args[2].asNumber().toInt32();
        auto b1     = args[3].asNumber().toInt32();
        mBlock->triggerEvent(*region, pos, b0, b1);
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}

// MCAPI ::CopperBehavior const* tryGetCopperBehavior() const;
// Local<Value> BlockClass::tryGetCopperBehavior() { }

Local<Value> BlockClass::tryGetInfested() {
    try {
        if (!mBlock) return Local<Value>();
        auto result = const_cast<Block*>(mBlock->tryGetInfested());
        return BlockClass::newBlock(result);
    }
    Catch;
}

Local<Value> BlockClass::tryGetUninfested() {
    try {
        if (!mBlock) return Local<Value>();
        auto result = const_cast<Block*>(mBlock->tryGetUninfested());
        return BlockClass::newBlock(result);
    }
    Catch;
}

// MCAPI bool tryToPlace(::BlockSource& region, ::BlockPos const& pos, ::ActorBlockSyncMessage const* syncMsg) const;
// Local<Value> BlockClass::tryToPlace(const Arguments& args) { }

Local<Value> BlockClass::tryToTill(const Arguments& args) {
    CheckArgsCount(args, 4);
    CheckInstanceType(args[0], BlockSourceClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckInstanceType(args[2], ActorClass);
    CheckInstanceType(args[3], ItemStackClass);
    try {
        if (!mBlock) return Local<Value>();
        auto engine = EngineScope::currentEngine();
        auto region = engine->getNativeInstance<BlockSourceClass>(args[0])->mBlockSource;
        auto pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto entity = engine->getNativeInstance<ActorClass>(args[2])->mActor;
        auto item   = engine->getNativeInstance<ItemStackClass>(args[2])->mItemStack;
        return Boolean::newBoolean(mBlock->tryToTill(*region, pos, *entity, *item));
    }
    Catch;
}

// MCAPI void updateEntityAfterFallOn(::BlockPos const& pos, ::UpdateEntityAfterFallOnInterface& entity) const;
//  Local<Value> BlockClass::updateEntityAfterFallOn(const Arguments& args) { }

// MCAPI bool updateTallestCollisionShape(
//         ::BlockSource const&                               region,
//         ::BlockPos const&                                  pos,
//         ::AABB const&                                      intersectTestBox,
//         ::optional_ref<::GetCollisionShapeInterface const> entity,
//         ::AABB&                                            result,
//         ::Vec3 const&                                      posToMinimizeDistanceToIfMatchingHeight,
//         float&                                             currentDistanceSqr
//     ) const;
// Local<Value> BlockClass::updateTallestCollisionShape(const Arguments& args) { }

Local<Value> BlockClass::use(const Arguments& args) {
    CheckArgsCount(args, 3) // check if < 3
        CheckInstanceType(args[0], PlayerClass);
    CheckInstanceType(args[1], BlockPosClass);
    CheckArgType(args[2], ValueKind::kNumber);
    if (args.size() >= 4) {
        CheckInstanceType(args[3], Vec3Class);
    }
    try {
        if (!mBlock) return Local<Value>();
        auto                engine = EngineScope::currentEngine();
        auto                player = engine->getNativeInstance<PlayerClass>(args[0])->get();
        auto                pos    = engine->getNativeInstance<BlockPosClass>(args[1])->mBlockPos;
        auto                face   = static_cast<uchar>(args[2].asNumber().toInt32());
        std::optional<Vec3> hit;
        if (args.size() >= 4) {
            hit.emplace(static_cast<Vec3>(engine->getNativeInstance<Vec3Class>(args[3])->mVec3));
        }
        return Boolean::newBoolean(mBlock->use(*player, pos, face, hit));
    }
    Catch;
}