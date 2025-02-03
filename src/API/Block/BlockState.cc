#include "API/Block/BlockState.h"

using namespace Komomo;

ClassDefine<BlockStateClass> materialClassBuilder = defineClass<BlockStateClass>("Block")
                                                        .constructor(nullptr)
                                                        // .InstanceFunction(fromNBT, BlockStateClass)
                                                        // .InstanceFunction(toNBT, BlockStateClass)
                                                        .build();


BlockStateClass::BlockStateClass(BlockState* blockState)
: ScriptClass(ConstructFromCpp<BlockStateClass>{}),
  mBlockState(blockState) {}

Local<Object> BlockStateClass::newBlockState(BlockState* blockState) {
    return (new BlockStateClass(blockState))->getScriptObject();
}

    // Local<Value> fromNBT(const Arguments& args) {}
    // Local<Value> toNBT(const Arguments& args) {}
