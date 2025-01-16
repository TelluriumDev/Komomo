#include "API/Actor/ActorDamageSource.h"


ClassDefine<ActorDamageSourceClass> actorDamageSourceClassBuilder =
    defineClass<ActorDamageSourceClass>("ActorDamageSource")
        .constructor(nullptr)

        .build();

ActorDamageSourceClass::ActorDamageSourceClass(ActorDamageSource* actorDamageSource)
: ScriptClass(ConstructFromCpp<ActorDamageSourceClass>{}) {
    this->mActorDamageSource = actorDamageSource;
}

Local<Object> ActorDamageSourceClass::newActorDamageSource(ActorDamageSource* actorDamageSource) {
    return (new ActorDamageSourceClass(actorDamageSource))->getScriptObject();
}
