#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include "API/Item/ItemStackBase.h"
#include <mc/world/item/ItemStack.h>

class ItemStackClass : public ItemStackBaseClass {
public:
    optional_ref<ItemStack> mItemStack;

public:
    template <typename T>
    explicit ItemStackClass(ItemStack* itemStack, ScriptClass::ConstructFromCpp<T> tag)
    : ItemStackBaseClass(itemStack, tag) {
        this->mItemStack = itemStack;
    };

    explicit ItemStackClass(ItemStack* itemStack) : ItemStackBaseClass(itemStack, ConstructFromCpp<ItemStackClass>{}) {
        this->mItemStack = itemStack;
    };

public:
    static Local<Object> newItemStack(ItemStack* itemStack);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemStackClass> itemStackClassBuilder;