#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include "API/Actor/Actor.h"

#include <mc/world/actor/Mob.h>

class MobClass : public ActorClass {
public:
    Mob* mMob;

public:
    template <typename T>
    explicit MobClass(Mob* mob, ScriptClass::ConstructFromCpp<T> tag) : ActorClass(mob, tag) {
        this->mMob = mob;
    };

    explicit MobClass(Mob* mob) : ActorClass(mob, ConstructFromCpp<MobClass>{}) { this->mMob = mob; };

public:
    static Local<Object> newMobClass(Mob *mob);

public: /* Member */
public: /* Method */
};

extern ClassDefine<MobClass> mobClassBuilder;