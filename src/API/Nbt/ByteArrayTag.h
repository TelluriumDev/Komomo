#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/ByteArrayTag.h>

class ByteArrayTagClass : public TagClass {
public:
    ByteArrayTag* mByteArrayTag;

public:
    template <typename T>
    explicit ByteArrayTagClass(ByteArrayTag* byteArrayTag, ConstructFromCpp<T> tagT)
    : TagClass(byteArrayTag, tagT),
      mByteArrayTag(byteArrayTag) {}

    explicit ByteArrayTagClass(ByteArrayTag* byteArrayTag)
    : TagClass(byteArrayTag, ConstructFromCpp<ByteArrayTagClass>()) {
        mByteArrayTag = byteArrayTag;
    };

public:
    static Local<Object> newByteArrayTagClass(ByteArrayTag* byteArrayTag);

    static Local<Object> createByteArrayTagClass(const Arguments& args);

    virtual Local<Value> toString();

    virtual Local<Value> getId();

    virtual Local<Value> getData();
};

extern ClassDefine<ByteArrayTagClass> byteArrayTagClassBuilder;
