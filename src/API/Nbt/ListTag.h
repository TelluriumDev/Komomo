#pragma once

#include "API/APIHelper.h"
#include "API/Nbt/Tag.h"

#include <mc/nbt/ListTag.h>

class ListTagClass : public TagClass {
public:
    ListTag* mListTag;

public:
    template <typename T>
    explicit ListTagClass(ListTag* listTag, ConstructFromCpp<T> tagT) : TagClass(listTag, tagT) {
        this->mListTag = listTag;
    };

    explicit ListTagClass(ListTag* listTag) : TagClass(listTag, ConstructFromCpp<ListTagClass>()) {
        this->mListTag = listTag;
    };

public:
    static Local<Object> newListTagClass(ListTag* listTag);
};

extern ClassDefine<ListTagClass> listTagClassBuilder;


