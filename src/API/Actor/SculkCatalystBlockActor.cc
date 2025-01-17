#include "API/Actor/SculkCatalystBlockActor.h"

#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

ClassDefine<SculkCatalystBlockActorClass> sculkCatalystBlockActorClassBuilder =
    defineClass<SculkCatalystBlockActorClass>("SculkCatalystBlockActor").constructor(nullptr).build();

SculkCatalystBlockActorClass::SculkCatalystBlockActorClass(SculkCatalystBlockActor* sculkCatalystBlockActor)
: ScriptClass(ConstructFromCpp<SculkCatalystBlockActorClass>{}) {
    this->mSculkCatalystBlockActor = sculkCatalystBlockActor;
}

Local<Object> SculkCatalystBlockActorClass::newSculkCatalystBlockActor(SculkCatalystBlockActor* sculkCatalystBlockActor
) {
    return (new SculkCatalystBlockActorClass(sculkCatalystBlockActor))->getScriptObject();
}