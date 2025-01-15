#include "API/Item/ItemActor.h"

ClassDefine<ItemActorClass> itemActorClassBuilder =
    defineClass<ItemActorClass>("ItemActor").constructor(nullptr).build();

ItemActorClass::ItemActorClass(ItemActor* itemActor) : ScriptClass(ConstructFromCpp<ItemActorClass>{}) {
    this->mItemActor = itemActor;
}

Local<Object> ItemActorClass::newItemActor(ItemActor* itemactor) {
    return (new ItemActorClass(itemactor))->getScriptObject();
}