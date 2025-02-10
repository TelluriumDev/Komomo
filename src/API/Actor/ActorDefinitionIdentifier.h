#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/Actor/ActorDefinitionIdentifier.h>

struct ActorDefinitionIdentifier;

class ActorDefinitionIdentifierClass : public ScriptClass {
public:
    ActorDefinitionIdentifier* mActorDefinitionIdentifier;

public:
    ActorDefinitionIdentifierClass(ActorDefinitionIdentifier* actorDefinitionIdentifier);

public:
    static Local<Object> newActorDefinitionIdentifier(ActorDefinitionIdentifier* actorDefinitionIdentifier);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ActorDefinitionIdentifierClass> actorDefinitionIdentifierClassBuilder;