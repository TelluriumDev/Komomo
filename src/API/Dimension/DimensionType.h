#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/world/DimensionType.h>

// using DimensionType;

class DimensionTypeClass : public ScriptClass {
public:
    DimensionType* mDimensionType;

public:
    DimensionTypeClass(DimensionType* dimensiontype);

public:
    static Local<Object> newDimensionType(DimensionType* dimensiontype);

public: /* Member */
public: /* Method */
};

extern ClassDefine<DimensionTypeClass> dimensiontypeClassBuilder;