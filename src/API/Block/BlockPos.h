#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/BlockPos.h>

class BlockPosClass : public ScriptClass {
public:
    BlockPos mBlockPos;

public:
    BlockPosClass(BlockPos blockpos);


public:
    static Local<Object> newBlockPosClass(BlockPos blockpos);
};

extern ClassDefine<BlockPosClass> blockPosClassBuilder;