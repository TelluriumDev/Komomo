#include "API/ItemStack/ItemStack.h"

ClassDefine<ItemStackClass> itemStackClassBuilder = defineClass<ItemStackClass>("ItemStack").build();

ItemStackClass::ItemStackClass(ItemStack* itemStack) : ScriptClass(ConstructFromCpp<ItemStackClass>{}) {
    this->mItemStack = itemStack;
}

Local<Object> ItemStackClass::newItemStack(ItemStack* itemstack) {
    return (new ItemStackClass(itemstack))->getScriptObject();
}