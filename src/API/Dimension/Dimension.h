#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class Dimension;

class DimensionClass : public ScriptClass {
public:
    Dimension* mDimension;

public:
    DimensionClass(Dimension* dimension);

public:
    static Local<Object> newDimension(Dimension* dimension);

public: /* Member */
public: /* Method */
};

extern ClassDefine<DimensionClass> dimensionClassBuilder;