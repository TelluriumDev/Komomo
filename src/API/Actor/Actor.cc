#include "API/Actor/Actor.h"

ClassDefine<ActorClass> actorClassBuilder = defineClass<ActorClass>("Actor")
                                                .constructor(nullptr)

                                                .build();

ActorClass::ActorClass(Actor* actor) : ScriptClass(ConstructFromCpp<ActorClass>{}) { this->mActor = actor; }

Local<Object> ActorClass::newActor(Actor* actor) { return (new ActorClass(actor))->getScriptObject(); }

Local<Value> ActorClass::isSleeping() { return Local<Value>(); }