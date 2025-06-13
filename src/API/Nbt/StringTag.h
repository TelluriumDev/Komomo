#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/StringTag.h>

class StringTagClass : public TagClass {
public:
    StringTag* mStringTag;

public:
    template <typename T>
    explicit StringTagClass(StringTag* stringTag, ConstructFromCpp<T> tagT)
    : TagClass(stringTag, tagT),
      mStringTag(stringTag) {}

    explicit StringTagClass(StringTag* stringTag) : TagClass(stringTag, ConstructFromCpp<StringTagClass>()) {
        mStringTag = stringTag;
    };

public:
    static Local<Object> newStringTagClass(StringTag* stringTag);
};

extern ClassDefine<StringTagClass> stringTagClassBuilder;