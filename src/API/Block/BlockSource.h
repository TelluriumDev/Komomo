#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/BlockSource.h>

class BlockSourceClass : public ScriptClass {
public:
    BlockSource* mBlockSource;

public:
    BlockSourceClass(BlockSource* blockSource);

public:
    // static BlockSourceClass* create(const Arguments& args); // TODO
    static Local<Object> newBlockSource(BlockSource* blockSource);

public: /* Member */
public: /* Method */
};

extern ClassDefine<BlockSourceClass> blockSourceClassBuilder;
