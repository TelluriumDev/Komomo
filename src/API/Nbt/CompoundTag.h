#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/CompoundTag.h>

class CompoundTagClass : public TagClass {

public:
    CompoundTag*  mCompoundTag;
    Local<Object> mObject = Object::newObject();

public:
    template <typename T>
    explicit CompoundTagClass(CompoundTag* compoundTag, ConstructFromCpp<T> tagT)
    : ScriptClass(tagT),
      mCompoundTag(compoundTag) {}

    explicit CompoundTagClass(CompoundTag* compoundTag) : TagClass(compoundTag, ConstructFromCpp<CompoundTagClass>()) {
        mCompoundTag = compoundTag;
    };

public:
    static Local<Object> newCompoundTagClass(CompoundTag* compoundTag);
};

extern ClassDefine<CompoundTagClass> compoundTagClassBuilder;
