#include "API/Block/BlockPos.h"


ClassDefine<BlockPosClass> blockPosClassBuilder = defineClass<BlockPosClass>("BlockPos")
                                                      .constructor(nullptr)

                                                      .build();

BlockPosClass::BlockPosClass(BlockPos blockpos) : ScriptClass(ConstructFromCpp<BlockPosClass>{}) {
    this->mBlockPos = blockpos;
}

Local<Object> BlockPosClass::newBlockPosClass(BlockPos blockpos) {
    return (new BlockPosClass(blockpos))->getScriptObject();
}
