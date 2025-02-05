#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/deps/core/math/Vec2.h>

class Vec2Class : public ScriptClass {
public:
    Vec2 mVec2;

public:
    Vec2Class(Vec2 vec2);


public:
    static Local<Object> newVec2Class(Vec2 vec2);

};

extern ClassDefine<Vec2Class> vec2ClassBuilder;