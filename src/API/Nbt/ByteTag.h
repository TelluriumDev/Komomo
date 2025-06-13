#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/ByteTag.h>

class ByteTagClass : public TagClass {
public:
    ByteTag* mByteTag;

public:
    template <typename T>
    explicit ByteTagClass(ByteTag* byteTag, ConstructFromCpp<T> tagT) : TagClass(byteTag, tagT),
                                                                        mByteTag(byteTag) {}

    explicit ByteTagClass(ByteTag* byteTag) : TagClass(byteTag, ConstructFromCpp<ByteTagClass>()) {
        mByteTag = byteTag;
    };

public:
    static Local<Object> newByteTagClass(ByteTag* byteTag);
};

extern ClassDefine<ByteTagClass> byteTagClassBuilder;