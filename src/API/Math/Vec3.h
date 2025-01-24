#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/deps/core/math/Vec3.h>

class Vec3Class : public ScriptClass {
public:
    Vec3 mVec3;

    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

public:
    Vec3Class(float x, float y, float z);
    Vec3Class(Vec3& vec3);


public:
    static Local<Object> newVec3(float x, float y, float z);

public: /* Member */
public: /* Method */
    Local<Value> setX(float x);
    Local<Value> setY(float y);
    Local<Value> setZ(float z);
};

extern ClassDefine<Vec3Class> vec3ClassBuilder;