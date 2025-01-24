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
    Local<Value> getDescriptionId() const;


public: /* Method */
    // virtual bool initServer(::Json::Value const&, ::SemVersion const&, ::IPackLoadContext&, ::JsonBetaState const);

    // tearDown
    Method(tearDown);

    Method(setDescriptionId); 

    Method(getMaxUseDuration);

    Method(getLegacyBlockForRendering);
};

extern ClassDefine<ItemClass> itemClassBuilder;