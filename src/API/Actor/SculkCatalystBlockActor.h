#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

struct SculkCatalystBlockActor;

class SculkCatalystBlockActorClass : public ScriptClass {
public:
    SculkCatalystBlockActor* mSculkCatalystBlockActor;

public:
    SculkCatalystBlockActorClass(SculkCatalystBlockActor* sculkCatalystBlockActor);

public:
    static Local<Object> newSculkCatalystBlockActor(SculkCatalystBlockActor* sculkCatalystBlockActor);

public: /* Member */
public: /* Method */
};

extern ClassDefine<SculkCatalystBlockActorClass> sculkCatalystBlockActorClassBuilder;