#include "API/Block/BlockSource.h"


ClassDefine<BlockSourceClass> blocksourceClassBuilder = defineClass<BlockSourceClass>("BlockSource")
                                                            .constructor(nullptr)

                                                            .build();

BlockSourceClass::BlockSourceClass(BlockSource* blocksource) : ScriptClass(ConstructFromCpp<BlockSourceClass>{}) {
    this->mBlockSource = blocksource;
}

Local<Object> BlockSourceClass::newBlockSource(BlockSource* blocksource) {
    return (new BlockSourceClass(blocksource))->getScriptObject();
}
