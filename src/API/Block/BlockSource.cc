#include "API/Block/BlockSource.h"


ClassDefine<BlockSourceClass> blockSourceClassBuilder = defineClass<BlockSourceClass>("BlockSource")
                                                                  .constructor(nullptr)

                                                                  .build();

BlockSourceClass::BlockSourceClass(BlockSource* blockSource) : ScriptClass(ConstructFromCpp<BlockSourceClass>{}) {
    this->mBlockSource = blockSource;
}

Local<Object> BlockSourceClass::newBlockSource(BlockSource* blockSource) {
    return (new BlockSourceClass(blockSource))->getScriptObject();
}
