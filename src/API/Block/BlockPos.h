#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/BlockPos.h>

class BlockPosClass : public ScriptClass {
public:
    BlockPos mBlockPos;

    int x = 0;
    int y = 0;
    int z = 0;

public:
    BlockPosClass(int x, int y, int z);
    BlockPosClass(BlockPos& blockpos);


public:
    static Local<Object> newBlockPos(int x, int y, int z);

public: /* Member */
public: /* Method */
    Local<Value> setX(int x);
    Local<Value> setY(int y);
    Local<Value> setZ(int z);
};

extern ClassDefine<BlockPosClass> blockPosClassBuilder;