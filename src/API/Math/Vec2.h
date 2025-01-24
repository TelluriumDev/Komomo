#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/deps/core/math/Vec2.h>

class Vec2Class : public ScriptClass {
public:
    Vec2 mVec2;

    float x = 0;
    float y = 0;

public:
    Vec2Class(float x, float y);


public:
    static Local<Object> newVec2(float x, float y);

public: /* Method */
    Local<Value> setX(float x);
    Local<Value> setY(float y);
};

extern ClassDefine<Vec2Class> vec2ClassBuilder;