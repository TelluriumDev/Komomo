#include "API/Item/ItemStackBase.h"

ClassDefine<ItemStackBaseClass> itemStackBaseClassBuilder =
    defineClass<ItemStackBaseClass>("ItemStackBase").constructor(nullptr).build();


Local<Object> ItemStackBaseClass::newItemStackBase(ItemStackBase* itemStackBase) {
    return (new ItemStackBaseClass(itemStackBase))->getScriptObject();
}