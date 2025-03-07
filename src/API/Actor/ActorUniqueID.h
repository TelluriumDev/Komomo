#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/legacy/ActorUniqueID.h>

class ActorUniqueIDClass : public ScriptClass {
public:
    ActorUniqueID *mActorUniqueID;

public:
    ActorUniqueIDClass(ActorUniqueID *actorUniqueID);

public:
    static Local<Object> newActorUniqueID(ActorUniqueID *actorUniqueID);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ActorUniqueIDClass> actorUniqueIDClassBuilder;
