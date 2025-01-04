#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/Actor.h>

class ActorClass : public ScriptClass {
private:
    Actor* mActor;

public:
    ActorClass(Actor* actor);

public:
    static Local<Object> newActor(Actor* actor);

public: /* Member */
    
public: /* Method */
};

extern ClassDefine<ActorClass> ActorClassBuilder;