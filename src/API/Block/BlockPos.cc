#include "API/Block/BlockPos.h"


ClassDefine<BlockPosClass> blockPosClassBuilder = defineClass<BlockPosClass>("BlockPos")
                                                      .constructor(nullptr)

                                                      .build();

BlockPosClass::BlockPosClass(BlockPos* blockPos) : ScriptClass(ConstructFromCpp<BlockPosClass>{}) {
    this->mBlockPos = blockPos;
}

Local<Object> BlockPosClass::newBlockPos(BlockPos* blockPos) {
    return (new BlockPosClass(blockPos))->getScriptObject();
}
