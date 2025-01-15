#include "API/Block/Block.h"


ClassDefine<BlockClass> blockClassBuilder = defineClass<BlockClass>("Block")
                                                            .constructor(nullptr)

                                                            .build();

BlockClass::BlockClass(Block* block) : ScriptClass(ConstructFromCpp<BlockClass>{}) {
    this->mBlock = block;
}

Local<Object> BlockClass::newBlock(Block* block) {
    return (new BlockClass(block))->getScriptObject();
}
