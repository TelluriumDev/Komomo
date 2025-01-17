#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/util/Random.h>

class RandomClass : public ScriptClass {
public:
    Random* mRandom;

public:
    RandomClass(Random* random);

public:
    static Local<Object> newRandom(Random* random);

public: /* Member */
public: /* Method */
};

extern ClassDefine<RandomClass> randomClassBuilder;