#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/world/DimensionType.h>

// using DimensionType;

class DimensionTypeClass : public ScriptClass {
public:
    DimensionType* mDimensionType;

public:
    DimensionTypeClass(DimensionType* dimensionType);

public:
    static Local<Object> newDimensionType(DimensionType* dimensionType);

public: /* Member */
public: /* Method */
};

extern ClassDefine<DimensionTypeClass> dimensionTypeClassBuilder;