#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

class ItemActor;

class ItemActorClass : public ScriptClass {
public:
    ItemActor* mItemActor;

public:
    ItemActorClass(ItemActor* itemactor);

public:
    static Local<Object> newItemActor(ItemActor* itemactor);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemActorClass> itemActorClassBuilder;