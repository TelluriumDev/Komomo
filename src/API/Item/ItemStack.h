#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/item/ItemStack.h>

class ItemStackClass : public ScriptClass {
public:
    ItemStack* mItemStack;

public:
    ItemStackClass(ItemStack* itemStack);

public:
    static Local<Object> newItemStack(ItemStack* itemStack);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemStackClass> itemStackClassBuilder;