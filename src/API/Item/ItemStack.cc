#include "API/Item/ItemStack.h"

ClassDefine<ItemStackClass> itemStackClassBuilder =
    defineClass<ItemStackClass>("ItemStack").constructor(nullptr).build();

ItemStackClass::ItemStackClass(ItemStack* itemStack) : ScriptClass(ConstructFromCpp<ItemStackClass>{}) {
    this->mItemStack = itemStack;
}

Local<Object> ItemStackClass::newItemStack(ItemStack* itemStack) {
    return (new ItemStackClass(itemStack))->getScriptObject();
}