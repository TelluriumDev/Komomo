#include "API/Block/BlockPos.h"


ClassDefine<BlockPosClass> blockPosClassBuilder = defineClass<BlockPosClass>("BlockPos")
                                                      .constructor(nullptr)

                                                      .build();

BlockPosClass::BlockPosClass(int x, int y, int z) : ScriptClass(ConstructFromCpp<BlockPosClass>{}) {
    this->x         = x;
    this->y         = y;
    this->z         = z;
    this->mBlockPos = BlockPos(x, y, z);
}

BlockPosClass::BlockPosClass(BlockPos& blockpos) : BlockPosClass(blockpos.x, blockpos.y, blockpos.z) {}
Local<Object> BlockPosClass::newBlockPos(int x, int y, int z) {
    return (new BlockPosClass(x, y, z))->getScriptObject();
}
