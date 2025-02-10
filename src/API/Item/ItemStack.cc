#include "API/Item/ItemStack.h"

ClassDefine<ItemStackClass> itemStackClassBuilder =
    defineClass<ItemStackClass>("ItemStack").constructor(nullptr).build();



Local<Object> ItemStackClass::newItemStack(ItemStack* itemStack) {
    return (new ItemStackClass(itemStack))->getScriptObject();
}