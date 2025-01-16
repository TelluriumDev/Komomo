#include "API/Actor/ActorUniqueID.h"


ClassDefine<ActorUniqueIDClass> actorUniqueIDClassBuilder = defineClass<ActorUniqueIDClass>("ActorUniqueID")
                                                                .constructor(nullptr)

                                                                .build();

ActorUniqueIDClass::ActorUniqueIDClass(ActorUniqueID* actorUniqueID)
: ScriptClass(ConstructFromCpp<ActorUniqueIDClass>{}) {
    this->mActorUniqueID = actorUniqueID;
}

Local<Object> ActorUniqueIDClass::newActorUniqueID(ActorUniqueID* actorUniqueID) {
    return (new ActorUniqueIDClass(actorUniqueID))->getScriptObject();
}
