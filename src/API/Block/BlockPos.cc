#include "API/Block/BlockPos.h"


ClassDefine<BlockPosClass> blockposClassBuilder = defineClass<BlockPosClass>("BlockPos")
                                                      .constructor(nullptr)

                                                      .build();

BlockPosClass::BlockPosClass(BlockPos* blockpos) : ScriptClass(ConstructFromCpp<BlockPosClass>{}) {
    this->mBlockPos = blockpos;
}

Local<Object> BlockPosClass::newBlockPos(BlockPos* blockpos) {
    return (new BlockPosClass(blockpos))->getScriptObject();
}
