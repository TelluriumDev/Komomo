#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/BlockSource.h>

class BlockSourceClass : public ScriptClass {
public:
    BlockSource* mBlockSource;

public:
    BlockSourceClass(BlockSource* blocksource);

public:
    // static BlockSourceClass* create(const Arguments& args); // TODO
    static Local<Object> newBlockSource(BlockSource* blocksource);

public: /* Member */
public: /* Method */
};

extern ClassDefine<BlockSourceClass> blocksourceClassBuilder;


