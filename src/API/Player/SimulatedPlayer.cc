#include "API/Player/SimulatedPlayer.h"
#include "API/APIHelper.h"
#include "API/Actor/Actor.h"
#include "API/Block/BlockPos.h"
#include "API/Dimension/DimensionType.h"
#include "API/Item/ItemStack.h"
#include "API/Math/Vec2.h"
#include "API/Math/Vec3.h"

ClassDefine<SimulatedPlayerClass> simulatedPlayerClassBuilder =
        defineClass<SimulatedPlayerClass>("SimulatedPlayer")
        .constructor(nullptr)

        .function("newSimulatedPlayer", &SimulatedPlayerClass::newSimulatedPlayer)

        .instanceProperty("isSimulated", &SimulatedPlayerClass::isSimulated)
        .instanceProperty("xuid", &SimulatedPlayerClass::getXuid)
        .instanceProperty("_getSpawnChunkLimit", &SimulatedPlayerClass::_getSpawnChunkLimit)

        .InstanceFunction(simulateSneaking, SimulatedPlayerClass)
        .InstanceFunction(simulateStopSneaking, SimulatedPlayerClass)
        .InstanceFunction(simulateUseItem, SimulatedPlayerClass)
        .InstanceFunction(simulateDestroyLookAt, SimulatedPlayerClass)
        // .InstanceFunction(initializeComponents, SimulatedPlayerClass)
        .InstanceFunction(aiStep, SimulatedPlayerClass)
        // .InstanceFunction(getMovementSettings, SimulatedPlayerClass)
        .InstanceFunction(teleportTo, SimulatedPlayerClass)
        // .InstanceFunction(_createChunkSource, SimulatedPlayerClass)
        .InstanceFunction(_updateChunkPublisherView, SimulatedPlayerClass)
        .InstanceFunction(_addMoveComponent, SimulatedPlayerClass)
        // .InstanceFunction(_createNavigationResult, SimulatedPlayerClass)
        .InstanceFunction(_trySwing, SimulatedPlayerClass)
        .InstanceFunction(_updateMovement, SimulatedPlayerClass)
        .InstanceFunction(_updateRidingComponents, SimulatedPlayerClass)
        // .InstanceFunction(getGameTestHelper, SimulatedPlayerClass)
        .InstanceFunction(postAiStep, SimulatedPlayerClass)
        .InstanceFunction(preAiStep, SimulatedPlayerClass)
        // .InstanceFunction(setGameTestHelper, SimulatedPlayerClass)
        .InstanceFunction(setXuid, SimulatedPlayerClass)
        .InstanceFunction(simulateAttack, SimulatedPlayerClass)
        .InstanceFunction(simulateChat, SimulatedPlayerClass)
        .InstanceFunction(simulateDestroyBlock, SimulatedPlayerClass)
        .InstanceFunction(simulateDisconnect, SimulatedPlayerClass)
        .InstanceFunction(simulateDropSelectedItem, SimulatedPlayerClass)
        .InstanceFunction(simulateFly, SimulatedPlayerClass)
        .InstanceFunction(simulateGiveItem, SimulatedPlayerClass)
        .InstanceFunction(simulateInteract, SimulatedPlayerClass)
        .InstanceFunction(simulateJump, SimulatedPlayerClass)
        .InstanceFunction(simulateLocalMove, SimulatedPlayerClass)
        .InstanceFunction(simulateLookAt, SimulatedPlayerClass)
        .InstanceFunction(simulateMoveToLocation, SimulatedPlayerClass)
        // .InstanceFunction(simulateNavigateToEntity, SimulatedPlayerClass)
        // .InstanceFunction(simulateNavigateToLocation, SimulatedPlayerClass)
        // .InstanceFunction(simulateNavigateToLocations, SimulatedPlayerClass)
        .InstanceFunction(simulateRespawn, SimulatedPlayerClass)
        .InstanceFunction(simulateSetBodyRotation, SimulatedPlayerClass)
        .InstanceFunction(simulateSetItem, SimulatedPlayerClass)
        .InstanceFunction(simulateStartBuildInSlot, SimulatedPlayerClass)
        .InstanceFunction(simulateStopBuild, SimulatedPlayerClass)
        .InstanceFunction(simulateStopDestroyingBlock, SimulatedPlayerClass)
        .InstanceFunction(simulateStopFlying, SimulatedPlayerClass)
        .InstanceFunction(simulateStopInteracting, SimulatedPlayerClass)
        .InstanceFunction(simulateStopMoving, SimulatedPlayerClass)
        .InstanceFunction(simulateStopUsingItem, SimulatedPlayerClass)
        .InstanceFunction(simulateUseItemInSlot, SimulatedPlayerClass)
        .InstanceFunction(simulateUseItemInSlotOnBlock, SimulatedPlayerClass)
        .InstanceFunction(simulateUseItemOnBlock, SimulatedPlayerClass)
        .InstanceFunction(simulateWorldMove, SimulatedPlayerClass)


        .build();


Local<Object> SimulatedPlayerClass::newSimulatedPlayer(const Arguments &args) {
    if (args.size() < 1) {
        PrintArgsTooFew();
        return Object::newObject();
    }
    CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());
    string name = args[0].asString().toString();
    auto engine = EngineScope::currentEngine();
    if (!IsInstanceOf<Vec3Class>(args[1])) {
        PrintWrongArgType();
        return Object::newObject();
    }
    auto vec3 = engine->getNativeInstance<Vec3Class>(args[1]);
    if (args.size() == 2) {
        return (new SimulatedPlayerClass(SimulatedPlayer::create(name, vec3->mVec3)))->getScriptObject();
    }
    if (!IsInstanceOf<DimensionTypeClass>(args[2])) {
        PrintWrongArgType();
        return Object::newObject();
    }
    auto dimension = engine->getNativeInstance<DimensionTypeClass>(args[2]);
    if (args.size() == 3) {
        return (new SimulatedPlayerClass(SimulatedPlayer::create(name, vec3->mVec3, *dimension->mDimensionType)))
                ->getScriptObject();
    }
    if (!IsInstanceOf<Vec2Class>(args[3])) {
        PrintWrongArgType();
        return Object::newObject();
    }
    auto vec2 = engine->getNativeInstance<Vec2Class>(args[3]);
    return (new SimulatedPlayerClass(SimulatedPlayer::create(name, vec3->mVec3, *dimension->mDimensionType, vec2->mVec2)
            ))
            ->getScriptObject();
}

Local<Value> SimulatedPlayerClass::isSimulated() {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->isSimulated());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::getXuid() {
    try {
        if (!mSimulatedPlayer) return String::newString("");
        return String::newString(mSimulatedPlayer->getXuid());
    }
    CatchReturn(String::newString(""));
}

Local<Value> SimulatedPlayerClass::_getSpawnChunkLimit() {
    try {
        if (!mSimulatedPlayer) return Number::newNumber(0);
        return Number::newNumber(mSimulatedPlayer->_getSpawnChunkLimit());
    }
    CatchReturn(Number::newNumber(0););
}

Local<Value> SimulatedPlayerClass::simulateSneaking(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateSneaking());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateStopSneaking(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateStopSneaking());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateUseItem(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        if (args.size() == 0) {
            return Boolean::newBoolean(mSimulatedPlayer->simulateUseItem());
        } else if (args.size() == 1 && IsInstanceOf<ItemStackClass>(args[0])) {
            // return Boolean::newBoolean(mSimulatedPlayer->simulateUseItem(
            //     *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack
            // ));
            return {};
        } else
            PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateDestroyLookAt(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateDestroyLookAt(args[0].asNumber().toFloat()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

// Local<Value> SimulatedPlayerClass::initializeComponents(const Arguments& args); // TODO

Local<Value> SimulatedPlayerClass::aiStep(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->aiStep();
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::getMovementSettings(); // TODO

Local<Value> SimulatedPlayerClass::teleportTo(const Arguments &args) {
    CheckArgsCount(args, 5);
    CheckInstanceType(args[0], Vec3Class);
    CheckArgType(args[1], ValueKind::kBoolean);
    CheckArgType(args[2], ValueKind::kNumber);
    CheckArgType(args[3], ValueKind::kNumber);
    CheckArgType(args[4], ValueKind::kBoolean);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        ScriptEngine *engine = EngineScope::currentEngine();
        Vec3Class *vec3 = engine->getNativeInstance<Vec3Class>(args[0]);
        mSimulatedPlayer->teleportTo(
            vec3->mVec3,
            args[1].asBoolean().value(),
            args[2].asNumber().toFloat(),
            args[3].asNumber().toFloat(),
            args[4].asBoolean().value()
        );
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::_createChunkSource(const Arguments& args) // TODO

Local<Value> SimulatedPlayerClass::_updateChunkPublisherView(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], Vec3Class)
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        ScriptEngine *engine = EngineScope::currentEngine();
        Vec3Class *vec3 = engine->getNativeInstance<Vec3Class>(args[0]);
        mSimulatedPlayer->_updateChunkPublisherView(vec3->mVec3, args[0].asNumber().toFloat());
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::_addMoveComponent(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->_addMoveComponent();
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::_createNavigationResult(const Arguments& args);  // TODO

Local<Value> SimulatedPlayerClass::_trySwing(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->_trySwing());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::_updateMovement(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->_updateMovement();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::_updateRidingComponents(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->_updateRidingComponents();
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::getGameTestHelper(const Arguments& args); // TODO

Local<Value> SimulatedPlayerClass::postAiStep(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->postAiStep();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::preAiStep(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->preAiStep();
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::setGameTestHelper(const Arguments& args) // TODO

Local<Value> SimulatedPlayerClass::setXuid(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->setXuid(args[0].asString().toString());
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateAttack(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        if (args.size() == 0) return Boolean::newBoolean(mSimulatedPlayer->simulateAttack());
        else if (args.size() == 1 && IsInstanceOf<ActorClass>(args[0])) {
            // return Boolean::newBoolean(mSimulatedPlayer->simulateAttack(
            //     EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor
            // ));
            return {};
        } else
            PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateChat(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateChat(args[0].asString().toString());
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateDestroyBlock(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], BlockPosClass);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateDestroyBlock(
            EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos,
            ScriptModuleMinecraft::ScriptFacing(args[1].asNumber().toInt32())
        ));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateDisconnect(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateDisconnect();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateDropSelectedItem(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        // return Boolean::newBoolean(mSimulatedPlayer->simulateDropSelectedItem());
        return {};
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateFly(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateFly();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateGiveItem(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], ItemStackClass);
    CheckArgType(args[1], ValueKind::kBoolean);

    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        // return Boolean::newBoolean(mSimulatedPlayer->simulateGiveItem(
        //     *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack,
        //     args[1].asBoolean().value()
        // ));
        return {};
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateInteract(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        if (args.size() == 0) return Boolean::newBoolean(mSimulatedPlayer->simulateInteract());
        else if (args.size() == 1 && IsInstanceOf<ActorClass>(args[0])) {
            // return Boolean::newBoolean(mSimulatedPlayer->simulateInteract(
            //     *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor
            // ));
            return {};
        } else if (args.size() == 2 && IsInstanceOf<BlockPosClass>(args[0]) && IsInstanceOf<Vec3Class>(args[1])) {
            return Boolean::newBoolean(mSimulatedPlayer->simulateInteract(
                EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos,
                ScriptModuleMinecraft::ScriptFacing(args[1].asNumber().toInt32())
            ));
        } else
            PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateJump(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateJump());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateLocalMove(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], Vec3Class);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateLocalMove(
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
            args[1].asNumber().toFloat()
        );
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateLookAt(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        // if (!mSimulatedPlayer) return Local<Value>();
        // if (IsInstanceOf<ActorClass>(args[0]))
        //     mSimulatedPlayer->simulateLookAt(
        //         *EngineScope::currentEngine()->getNativeInstance<ActorClass>(args[0])->mActor,
        //         sim::LookDuration(args[1].asNumber().toInt32())
        //     );
        // else if (IsInstanceOf<BlockPosClass>(args[0]))
        //     mSimulatedPlayer->simulateLookAt(
        //         EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[0])->mBlockPos,
        //         sim::LookDuration(args[1].asNumber().toInt32())
        //     );
        // else if (IsInstanceOf<Vec3Class>(args[0]))
        //     mSimulatedPlayer->simulateLookAt(
        //         EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
        //         sim::LookDuration(args[1].asNumber().toInt32())
        //     );
        // else
        //     PrintWrongArgType();
        return {};
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateMoveToLocation(const Arguments &args) {
    CheckArgsCount(args, 3);
    CheckInstanceType(args[0], Vec3Class);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckArgType(args[2], ValueKind::kBoolean);

    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateMoveToLocation(
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
            args[1].asNumber().toFloat(),
            args[2].asBoolean().value()
        );
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::simulateNavigateToEntity(const Arguments& args) // TODO

// Local<Value> SimulatedPlayerClass::simulateNavigateToLocation(const Arguments& args) // TODO

// Local<Value> SimulatedPlayerClass::simulateNavigateToLocation(const Arguments& args) // TODO

Local<Value> SimulatedPlayerClass::simulateNavigateToLocations(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kArray);
    CheckArgType(args[1], ValueKind::kNumber);

    std::vector<::Vec3> locations = {};
    for (size_t i = 0; i < args[0].asArray().size(); i++) {
        if (!IsInstanceOf<Vec3Class>(args[0].asArray().get(i))) {
            PrintWrongArgType();
            return Local<Value>();
        }
    }
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateNavigateToLocations(locations, args[1].asNumber().toFloat());
    }
    Catch;
    return Local<Value>();
}


Local<Value> SimulatedPlayerClass::simulateRespawn(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        // return Boolean::newBoolean(mSimulatedPlayer->simulateRespawn());
        return {};
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateSetBodyRotation(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateSetBodyRotation(args[0].asNumber().toFloat());
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateSetItem(const Arguments &args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], ItemStackClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kBoolean, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        // return Boolean::newBoolean(mSimulatedPlayer->simulateSetItem(
        //     *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack,
        //     args[1].asBoolean().value(),
        //     args[2].asNumber().toInt32()
        // ));
        return {};
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateStartBuildInSlot(const Arguments &args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStartBuildInSlot(args[0].asNumber().toInt32());
        return {};
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopBuild(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStopBuild();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopDestroyingBlock(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateStopDestroyingBlock();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopFlying(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStopFlying();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopInteracting(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStopInteracting();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopMoving(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStopMoving();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateStopUsingItem(const Arguments &args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        // mSimulatedPlayer->simulateStopUsingItem();
    }
    Catch;
    return Local<Value>();
}

Local<Value> SimulatedPlayerClass::simulateUseItemInSlot(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kNumber, Boolean::newBoolean(false));

    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateUseItemInSlot(args[0].asNumber().toInt32()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateUseItemInSlotOnBlock(const Arguments &args) {
    CheckArgsCountReturn(args, 3, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kNumber, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[3], Vec3Class, Boolean::newBoolean(false));

    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        // return Boolean::newBoolean(mSimulatedPlayer->simulateUseItemInSlotOnBlock(
        //     args[0].asNumber().toInt32(),
        //     EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[1])->mBlockPos,
        //     ScriptModuleMinecraft::ScriptFacing(args[2].asNumber().toInt32()),
        //     EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[3])->mVec3
        // ));
        return {};
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateUseItemOnBlock(const Arguments &args) {
    CheckArgsCountReturn(args, 4, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[0], ItemStackClass, Boolean::newBoolean(false));
    CheckInstanceTypeReturn(args[1], BlockPosClass, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[3], ValueKind::kNumber, Boolean::newBoolean(false));
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateUseItemOnBlock(
            *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack,
            EngineScope::currentEngine()->getNativeInstance<BlockPosClass>(args[1])->mBlockPos,
            ScriptModuleMinecraft::ScriptFacing(args[2].asNumber().toInt32()),
            args[3].asNumber().toFloat()
        ));
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateWorldMove(const Arguments &args) {
    CheckArgsCount(args, 2);
    CheckInstanceType(args[0], Vec3Class);
    CheckArgType(args[1], ValueKind::kNumber);
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->simulateWorldMove(
            EngineScope::currentEngine()->getNativeInstance<Vec3Class>(args[0])->mVec3,
            args[1].asNumber().toFloat()
        );
    }
    Catch;
    return Local<Value>();
}
