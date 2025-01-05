#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/item/Item.h>

class ItemStackClass : public ScriptClass {
public:
    ItemStack* mItemStack;

public:
    ItemStackClass(ItemStack* itemstack);

public:
    static Local<Object> newItemStack(ItemStack* itemstack);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemStackClass> itemStackClassBuilder;