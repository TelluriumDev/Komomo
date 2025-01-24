#include "API/Player/SimulatedPlayer.h"
#include "API/Dimension/DimensionType.h"
#include "API/Math/Vec2.h"
#include "API/Math/Vec3.h"


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