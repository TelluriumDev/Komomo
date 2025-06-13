#pragma once

#include "API/APIHelper.h"

#include <mc/nbt/Tag.h>

class TagClass : public ScriptClass {
public:
    Tag* mTag;

public:
    template <typename T>
    explicit TagClass(Tag* tag, ConstructFromCpp<T> tagT) : ScriptClass(tagT),
                                                            mTag(tag) {}

    explicit TagClass(Tag* tag) : ScriptClass(ConstructFromCpp<TagClass>()) { mTag = tag; };

public:
    static Local<Object> newTagClass(Tag* tag);
};

extern ClassDefine<TagClass> tagClassBuilder;