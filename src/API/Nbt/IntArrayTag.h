#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/IntArrayTag.h>

class IntArrayTagClass : public TagClass {
public:
    IntArrayTag* mIntArrayTag;

public:
    template <typename T>
    explicit IntArrayTagClass(IntArrayTag* intArrayTag, ConstructFromCpp<T> tagT)
    : TagClass(intArrayTag, tagT),
      mIntArrayTag(intArrayTag) {}

    explicit IntArrayTagClass(IntArrayTag* intArrayTag) : TagClass(intArrayTag, ConstructFromCpp<IntArrayTagClass>()) {
        mIntArrayTag = intArrayTag;
    };

public:
    static Local<Object> newIntArrayTagClass(IntArrayTag* intArrayTag);
};

extern ClassDefine<IntArrayTagClass> intArrayTagClassBuilder;
