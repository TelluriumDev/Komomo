#include "API/Actor/ActorDefinitionIdentifier.h"

ClassDefine<ActorDefinitionIdentifierClass> actorDefinitionIdentifierClassBuilder =
    defineClass<ActorDefinitionIdentifierClass>("ActorDefinitionIdentifier").constructor(nullptr).build();

ActorDefinitionIdentifierClass::ActorDefinitionIdentifierClass(ActorDefinitionIdentifier* actorDefinitionIdentifier) : ScriptClass(ConstructFromCpp<ActorDefinitionIdentifierClass>{}) {
    this->mActorDefinitionIdentifier = actorDefinitionIdentifier;
}

Local<Object> ActorDefinitionIdentifierClass::newActorDefinitionIdentifier(ActorDefinitionIdentifier* actorDefinitionIdentifier) {
    return (new ActorDefinitionIdentifierClass(actorDefinitionIdentifier))->getScriptObject();
}