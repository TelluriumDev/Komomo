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

    Local<Value> toSnbt();

    virtual Local<Value> toString();

    virtual Local<Value> getId();

    virtual Local<Value> deleteChildren();

    virtual Local<Value> hash();

    static Local<Value> getTagName(const Arguments& args);

    static Local<Value> NullString();

    virtual Local<Value> getData();
};

extern ClassDefine<TagClass> tagClassBuilder;