#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/world/level/Block.h>

class Block;

class BlockClass : public ScriptClass {
public:
    Block* mBlock;

public:
    BlockClass(Block* block);

public:
    // static BlockClass* create(const Arguments& args); // TODO
    static Local<Object> newBlock(Block* block);

public: /* Member */
public: /* Method */
};

extern ClassDefine<BlockClass> blockClassBuilder;
