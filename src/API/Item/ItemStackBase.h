#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/item/ItemStackBase.h>

class ItemStackBaseClass : public ScriptClass {
public:
    optional_ref<ItemStackBase> mItemStackBase;

public:
    template <typename T>
    explicit ItemStackBaseClass(ItemStackBase* itemStackBase, ConstructFromCpp<T> tag) : ScriptClass(tag),
                                                                 mItemStackBase(itemStackBase) {}

    explicit ItemStackBaseClass(ItemStackBase* itemStackBase) : ScriptClass(ConstructFromCpp<ItemStackBaseClass>()) { mItemStackBase = itemStackBase; };

public:
    static Local<Object> newItemStackBase(ItemStackBase* itemStackBase);
public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemStackBaseClass> itemStackBaseClassBuilder;