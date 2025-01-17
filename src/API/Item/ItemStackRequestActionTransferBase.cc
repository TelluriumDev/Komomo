#include "API/Item/ItemStackRequestActionTransferBase.h"

ClassDefine<ItemStackRequestActionTransferBaseClass> itemStackRequestActionTransferBaseClassBuilder =
    defineClass<ItemStackRequestActionTransferBaseClass>("ItemStackRequestActionTransferBase").constructor(nullptr).build();

ItemStackRequestActionTransferBaseClass::ItemStackRequestActionTransferBaseClass(ItemStackRequestActionTransferBase* itemStackRequestActionTransferBase) : ScriptClass(ConstructFromCpp<ItemStackRequestActionTransferBaseClass>{}) {
    this->mItemStackRequestActionTransferBase = itemStackRequestActionTransferBase;
}

Local<Object> ItemStackRequestActionTransferBaseClass::newItemStackRequestActionTransferBase(ItemStackRequestActionTransferBase* itemStackRequestActionTransferBase) {
    return (new ItemStackRequestActionTransferBaseClass(itemStackRequestActionTransferBase))->getScriptObject();
}