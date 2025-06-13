#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/DoubleTag.h>

class DoubleTagClass : public TagClass {
public:
    DoubleTag* mDoubleTag;

public:
    template <typename T>
    explicit DoubleTagClass(DoubleTag* doubleTag, ConstructFromCpp<T> tagT)
    : TagClass(doubleTag, tagT),
      mDoubleTag(doubleTag) {}

    explicit DoubleTagClass(DoubleTag* doubleTag) : TagClass(doubleTag, ConstructFromCpp<DoubleTagClass>()) {
        mDoubleTag = doubleTag;
    };

public:
    static Local<Object> newDoubleTagClass(DoubleTag* doubleTag);
};

extern ClassDefine<DoubleTagClass> doubleTagClassBuilder;