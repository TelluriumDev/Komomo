#include "API/Actor/SculkCatalystBlockActor.h"

ClassDefine<SculkCatalystBlockActorClass> sculkCatalystBlockActorClassBuilder =
    defineClass<SculkCatalystBlockActorClass>("SculkCatalystBlockActor").constructor(nullptr).build();

SculkCatalystBlockActorClass::SculkCatalystBlockActorClass(SculkCatalystBlockActor* sculkCatalystBlockActor)
: ScriptClass(ConstructFromCpp<SculkCatalystBlockActorClass>{}) {
    this->mSculkCatalystBlockActor = sculkCatalystBlockActor;
}

Local<Object>
SculkCatalystBlockActorClass::newSculkCatalystBlockActor(SculkCatalystBlockActor* sculkCatalystBlockActor) {
    return (new SculkCatalystBlockActorClass(sculkCatalystBlockActor))->getScriptObject();
}