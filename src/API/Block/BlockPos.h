#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include "mc/world/level/BlockPos.h"

class BlockPos;

class BlockPosClass : public ScriptClass {
public:
    BlockPos* mBlockPos;

public:
    BlockPosClass(BlockPos* blockPos);

public:
    // static BlockPosClass* create(const Arguments& args); // TODO
    static Local<Object> newBlockPos(BlockPos* blockPos);

public: /* Member */
public: /* Method */
};

extern ClassDefine<BlockPosClass> blockPosClassBuilder;
