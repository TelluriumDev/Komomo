#pragma once

#include "API/APIHelper.h"

#include <mc/nbt/CompoundTagVariant.h>

class CompoundTagVariantClass : public ScriptClass {
public:
    CompoundTagVariant* mCompoundTagVariant;
    Local<Object>       mObject = Object::newObject();


public:
    CompoundTagVariantClass(CompoundTagVariant* compoundTagVariant);

public:
    static Local<Object> newCompoundTagVariantClass(CompoundTagVariant* compoundTagVariant);

public:
};

extern ClassDefine<CompoundTagVariantClass> compoundTagVariantClassBuilder;
