#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/phys/AABB.h>

class AABBClass : public ScriptClass {
public:
    AABB* mAABB;

public:
    AABBClass(AABB* aabb);

public:
    static Local<Object> newAABB(AABB* aabb);

public: /* Member */
public: /* Method */
};

extern ClassDefine<AABBClass> aabbClassBuilder;