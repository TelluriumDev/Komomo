#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/IntTag.h>

class IntTagClass : public TagClass {
public:
    IntTag* mIntTag;

public:
    template <typename T>
    explicit IntTagClass(IntTag* intTag, ConstructFromCpp<T> tagT) : TagClass(intTag, tagT) {
        this->mIntTag = intTag;
    };

    explicit IntTagClass(IntTag* intTag) : TagClass(intTag, ConstructFromCpp<IntTagClass>()) {
        this->mIntTag = intTag;
    };

public:
    static Local<Object> newIntTagClass(IntTag* int64Tag);
};

extern ClassDefine<IntTagClass> intTagClassBuilder;
