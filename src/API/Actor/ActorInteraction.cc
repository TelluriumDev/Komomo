#include "API/Actor/ActorInteraction.h"


ClassDefine<ActorInteractionClass> actorInteractionClassBuilder = defineClass<ActorInteractionClass>("ActorInteraction")
                                                                      .constructor(nullptr)

                                                                      .build();

ActorInteractionClass::ActorInteractionClass(ActorInteraction* actorInteraction)
: ScriptClass(ConstructFromCpp<ActorInteractionClass>{}) {
    this->mActorInteraction = actorInteraction;
}

Local<Object> ActorInteractionClass::newActorInteraction(ActorInteraction* actorInteraction) {
    return (new ActorInteractionClass(actorInteraction))->getScriptObject();
}
