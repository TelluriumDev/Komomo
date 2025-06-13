#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/FloatTag.h>

class FloatTagClass : public TagClass {
public:
    FloatTag* mFloatTag;

public:
    template <typename T>
    explicit FloatTagClass(FloatTag* floatTag, ConstructFromCpp<T> tagT)
    : TagClass(floatTag, tagT),
      mFloatTag(floatTag) {}

    explicit FloatTagClass(FloatTag* floatTag) : TagClass(floatTag, ConstructFromCpp<FloatTagClass>()) {
        mFloatTag = floatTag;
    };

public:
    static Local<Object> newFloatTagClass(FloatTag* floatTag);
};

extern ClassDefine<FloatTagClass> floatTagClassBuilder;