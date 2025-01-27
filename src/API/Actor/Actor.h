#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/Actor.h>

class ActorClass : public ScriptClass {
public:
    Actor* mActor;

public:
    template <typename T>
    explicit ActorClass(Actor* actor, ScriptClass::ConstructFromCpp<T> tag) : ScriptClass(tag) {
        this->mActor = actor;
    };

    explicit ActorClass(Actor* actor) : ScriptClass(ConstructFromCpp<ActorClass>{}) { this->mActor = actor; };

public:
    static Local<Object> newActor(Actor* actor);

public: /* Member */
    Local<Value> isSleeping();

public: /* Method */
};

extern ClassDefine<ActorClass> actorClassBuilder;