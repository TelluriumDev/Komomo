#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/common/ActorUniqueID.h>

class ActorUniqueIDClass : public ScriptClass {
public:
    ActorUniqueID* mActorUniqueID;

public:
    ActorUniqueIDClass(ActorUniqueID* actoruniqueid);

public:
    static Local<Object> newActorUniqueID(ActorUniqueID* actoruniqueid);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ActorUniqueIDClass> actoruniqueidClassBuilder;