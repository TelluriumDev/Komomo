#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/inventory/network/ItemStackRequestActionTransferBase.h>

class ItemStackRequestActionTransferBaseClass : public ScriptClass {
public:
    ItemStackRequestActionTransferBase* mItemStackRequestActionTransferBase;

public:
    ItemStackRequestActionTransferBaseClass(ItemStackRequestActionTransferBase* itemStackRequestActionTransferBase);

public:
    static Local<Object> newItemStackRequestActionTransferBase(ItemStackRequestActionTransferBase* itemStackRequestActionTransferBase);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemStackRequestActionTransferBaseClass> itemStackRequestActionTransferBaseClassBuilder;