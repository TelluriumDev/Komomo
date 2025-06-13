#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/ShortTag.h>

class ShortTagClass : public TagClass {
public:
    ShortTag* mShortTag;

public:
    template <typename T>
    explicit ShortTagClass(ShortTag* shortTag, ConstructFromCpp<T> tagT)
    : TagClass(shortTag, tagT),
      mShortTag(shortTag) {}

    explicit ShortTagClass(ShortTag* shortTag) : TagClass(shortTag, ConstructFromCpp<ShortTagClass>()) {
        mShortTag = shortTag;
    };

public:
    static Local<Object> newShortTagClass(ShortTag* shortTag);
};

extern ClassDefine<ShortTagClass> shortTagClassBuilder;