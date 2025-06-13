#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/EndTag.h>

class EndTagClass : public TagClass {
public:
    EndTag* mEndTag;

public:
    template <typename T>
    explicit EndTagClass(EndTag* endTag, ConstructFromCpp<T> tagT) : TagClass(endTag, tagT),
                                                                     mEndTag(endTag) {}

    explicit EndTagClass(EndTag* endTag) : TagClass(endTag, ConstructFromCpp<EndTagClass>()) { mEndTag = endTag; };

public:
    static Local<Object> newEndTagClass(EndTag* endTag);
};

extern ClassDefine<EndTagClass> endTagClassBuilder;
