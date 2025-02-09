#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/ActorInteraction.h>

class ActorInteractionClass : public ScriptClass {
public:
    ActorInteraction* mActorInteraction;

public:
    ActorInteractionClass(ActorInteraction* actorInteraction);

public:
    static Local<Object> newActorInteraction(ActorInteraction* actorInteraction);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ActorInteractionClass> actorInteractionClassBuilder;