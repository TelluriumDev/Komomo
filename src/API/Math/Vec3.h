#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/deps/core/math/Vec3.h>

class Vec3Class : public ScriptClass {
public:
    Vec3 mVec3;
public:
    Vec3Class(Vec3 vec3);

public:
    static Local<Object> newVec3Class(Vec3 vec3);

};

extern ClassDefine<Vec3Class> vec3ClassBuilder;