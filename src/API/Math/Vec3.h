#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "mc/world/item/Item.h"

#include <mc/deps/core/math/Vec3.h>

class Vec3Class : public ScriptClass {
public:
    Vec3* mVec3;
    Vec3  mmVec3;

public:
    Vec3Class(Vec3* vec3);
    Vec3Class(Vec3 vec3);


public:
    static Local<Object> newVec3(Vec3* vec3);
    static Local<Object> newVec3(Vec3 vec3);

public: /* Member */
public: /* Method */
};

extern ClassDefine<Vec3Class> vec3ClassBuilder;