#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Math/Vec3.h" // IWYU pragma: keep
#include "API/Math/Vec2.h" // IWYU pragma: keep

class VecClass : public ScriptClass {
public:
    VecClass();

    // public:
    static Local<Object> newVec3(float x = 0, float y = 0, float z = 0);
    static Local<Object> newVec2(float x = 0, float y = 0);
};

extern ClassDefine<VecClass> vecClassBuilder;