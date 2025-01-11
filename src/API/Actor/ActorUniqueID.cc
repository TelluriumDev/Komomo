#include "API/Actor/ActorUniqueID.h"


ClassDefine<ActorUniqueIDClass> actoruniqueidClassBuilder = defineClass<ActorUniqueIDClass>("ActorUniqueID")
                                                                .constructor(nullptr)

                                                                .build();

ActorUniqueIDClass::ActorUniqueIDClass(ActorUniqueID* actoruniqueid)
: ScriptClass(ConstructFromCpp<ActorUniqueIDClass>{}) {
    this->mActorUniqueID = actoruniqueid;
}

Local<Object> ActorUniqueIDClass::newActorUniqueID(ActorUniqueID* actoruniqueid) {
    return (new ActorUniqueIDClass(actoruniqueid))->getScriptObject();
}
