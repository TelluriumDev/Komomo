#include "API/Player/SimulatedPlayer.h"
#include "API/APIHelper.h"
#include "API/Dimension/DimensionType.h"
#include "API/Item/ItemStack.h"
#include "API/Math/Vec2.h"
#include "API/Math/Vec3.h"
#include "Utils/Using.h"


using namespace Komomo;

ClassDefine<SimulatedPlayerClass> simulatedPlayerClassBuilder =
    defineClass<SimulatedPlayerClass>("SimulatedPlayer")
        .constructor(nullptr)

        .function("newSimulatedPlayer", &SimulatedPlayerClass::newSimulatedPlayer)

        .build();

SimulatedPlayerClass::SimulatedPlayerClass(
    std::string const&         name,
    std::optional<Vec3> const& pos,
    DimensionType              id,
    Vec2 const&                vec2
)
: ScriptClass(ConstructFromCpp<SimulatedPlayerClass>{}) {
    this->mSimulatedPlayer = SimulatedPlayer::create(name, pos, id, vec2);
}

Local<Object> SimulatedPlayerClass::newSimulatedPlayer(const Arguments& args) {
    if (args.size() >= 1) {
        if (args.size() == 1) {
            CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());
            return (new SimulatedPlayerClass(args[0].asString().toString()))->getScriptObject();
        } else if (args.size() == 2) {
            CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());

            auto engine = EngineScope::currentEngine();

            if (!IsInstanceOf<Vec3Class>(args[1])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto vec3 = engine->getNativeInstance<Vec3Class>(args[1]);

            return (new SimulatedPlayerClass(args[0].asString().toString(), vec3->mVec3))->getScriptObject();
        } else if (args.size() == 3) {
            CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());

            auto engine = EngineScope::currentEngine();

            if (!IsInstanceOf<Vec3Class>(args[1])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto vec3 = engine->getNativeInstance<Vec3Class>(args[1]);

            if (!IsInstanceOf<DimensionType>(args[2])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto dimension = engine->getNativeInstance<DimensionTypeClass>(args[2]);

            return (new SimulatedPlayerClass(args[0].asString().toString(), vec3->mVec3, *dimension->mDimensionType))
                ->getScriptObject();


        } else if (args.size() == 4) {
            CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());

            auto engine = EngineScope::currentEngine();

            if (!IsInstanceOf<Vec3Class>(args[1])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto vec3 = engine->getNativeInstance<Vec3Class>(args[1]);

            if (!IsInstanceOf<DimensionType>(args[2])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto dimension = engine->getNativeInstance<DimensionTypeClass>(args[2]);

            if (!IsInstanceOf<Vec2Class>(args[3])) {
                PrintWrongArgType();
                return Object::newObject();
            }

            auto vec2 = engine->getNativeInstance<Vec2Class>(args[3]);

            return (new SimulatedPlayerClass(
                        args[0].asString().toString(),
                        vec3->mVec3,
                        *dimension->mDimensionType,
                        vec2->mVec2
                    ))
                ->getScriptObject();
        }

    } else PrintArgsTooFew();
    return Object::newObject();
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

Local<Value> SimulatedPlayerClass::simulateSneaking(const Arguments& args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateSneaking());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateStopSneaking(const Arguments& args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateStopSneaking());
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateUseItem(const Arguments& args) {
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        if (args.size() == 0) {
            return Boolean::newBoolean(mSimulatedPlayer->simulateUseItem());
        } else if (args.size() == 1 && IsInstanceOf<ItemStackClass>(args[0])) {

            return Boolean::newBoolean(mSimulatedPlayer->simulateUseItem(
                *EngineScope::currentEngine()->getNativeInstance<ItemStackClass>(args[0])->mItemStack
            ));
        } else PrintWrongArgType();
        return Boolean::newBoolean(false);
    }
    CatchReturn(Boolean::newBoolean(false));
}

Local<Value> SimulatedPlayerClass::simulateDestroyLookAt(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kBoolean);
    try {
        if (!mSimulatedPlayer) return Boolean::newBoolean(false);
        return Boolean::newBoolean(mSimulatedPlayer->simulateDestroyLookAt(args[0].asNumber().toFloat()));
    }
    CatchReturn(Boolean::newBoolean(false));
}

// Local<Value> SimulatedPlayerClass::initializeComponents(const Arguments& args); // TODO

Local<Value> SimulatedPlayerClass::aiStep(const Arguments& args) {
    try {
        if (!mSimulatedPlayer) return Local<Value>();
        mSimulatedPlayer->aiStep();
    }
    Catch;
    return Local<Value>();
}

// Local<Value> SimulatedPlayerClass::getMovementSettings(); // TODO

// Local<Value> SimulatedPlayerClass::teleportTo(const Arguments& args) {
//     CheckArgsCount(args, 1);
//     try {
//         if (!mSimulatedPlayer) return Boolean::newBoolean(false);
//         auto engine = EngineScope::currentEngine();
//         if (!IsInstanceOf<Vec3Class>(args[0])) {
//             PrintWrongArgType();
//             return Boolean::newBoolean(false);
//         }
//         auto vec3 = engine->getNativeInstance<Vec3Class>(args[0]);
//         return Boolean::newBoolean(mSimulatedPlayer->teleportTo(vec3->mVec3));
//     }
//     CatchReturn(Boolean::newBoolean(false));
// }