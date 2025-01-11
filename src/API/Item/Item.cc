#include "API/Item/Item.h"

using namespace Komomo;

ClassDefine<ItemClass> itemClassBuilder = defineClass<ItemClass>("Item").constructor(nullptr).build();

ItemClass::ItemClass(Item* item) : ScriptClass(ConstructFromCpp<ItemClass>{}) { this->mItem = item; }

ItemClass* ItemClass::createItem(const Arguments& args) {
    CheckArgsCountReturn(args, 2, nullptr);
    CheckArgTypeReturn(args[0], ValueKind::kString, nullptr);
    CheckArgTypeReturn(args[1], ValueKind::kNumber, nullptr);

    try {
        Item* item = new Item(args[0].asString().toString(), args[1].asNumber().toInt32());
        return new ItemClass(item);
    }
    CatchReturn(nullptr)
}

Local<Object> ItemClass::newItem(Item* item) { return (new ItemClass(item))->getScriptObject(); }