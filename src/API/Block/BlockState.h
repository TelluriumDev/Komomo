#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/block/states/BlockState.h>

class BlockStateClass : public ScriptClass {
public:
    BlockState* mBlockState;

public:
    BlockStateClass(BlockState* blockState);

public:
    static Local<Object> newBlockState(BlockState* blockState);

public: /* Member */

public: /* Method */

    // Local<Value> fromNBT(const Arguments& args);
    // Local<Value> toNBT(const Arguments& args);

};

extern ClassDefine<BlockStateClass> blockStateClassBuilder;