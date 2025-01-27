#include "API/Actor/Actor.h"

ClassDefine<ActorClass> actorClassBuilder = defineClass<ActorClass>("Actor")
                                                .constructor(nullptr)

                                                .build();


Local<Object> ActorClass::newActor(Actor* actor) { return (new ActorClass(actor))->getScriptObject(); }

Local<Value> ActorClass::isSleeping() { return Local<Value>(); }