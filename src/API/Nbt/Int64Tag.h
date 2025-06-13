#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/Int64Tag.h>

class Int64TagClass : public TagClass {
public:
    Int64Tag* mInt64Tag;

public:
    template <typename T>
    explicit Int64TagClass(Int64Tag* int64Tag, ConstructFromCpp<T> tagT) : TagClass(int64Tag, tagT) {
        this->mInt64Tag = int64Tag;
    };

    explicit Int64TagClass(Int64Tag* int64Tag) : TagClass(int64Tag, ConstructFromCpp<Int64TagClass>()) {
        this->mInt64Tag = int64Tag;
    };

public:
    static Local<Object> newInt64TagClass(Int64Tag* int64Tag);
};

extern ClassDefine<Int64TagClass> int64TagClassBuilder;
