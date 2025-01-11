#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/item/Item.h>

class ItemClass : public ScriptClass {
public:
    Item* mItem;

public:
    ItemClass(Item* item);

public:
    static ItemClass*    createItem(const Arguments& args);
    static Local<Object> newItem(Item* item);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ItemClass> itemClassBuilder;