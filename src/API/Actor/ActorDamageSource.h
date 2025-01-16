#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/common/ActorDamageSource.h>

class ActorDamageSource;

class ActorDamageSourceClass : public ScriptClass {
public:
    ActorDamageSource* mActorDamageSource;

public:
    ActorDamageSourceClass(ActorDamageSource* actorDamageSource);

public:
    static Local<Object> newActorDamageSource(ActorDamageSource* actorDamageSource);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ActorDamageSourceClass> actorDamageSourceClassBuilder;