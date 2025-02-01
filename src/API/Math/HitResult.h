#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/phys/HitResult.h>

class HitResultClass : public ScriptClass {
public:
    HitResult* mHitResult;

public:
    HitResultClass(HitResult* hitResult);

public:
    static Local<Object> newHitResult(HitResult* hitResult);

public: /* Member */
public: /* Method */
};

extern ClassDefine<HitResultClass> hitResultClassBuilder;