#include "API/Dimension/DimensionType.h"


ClassDefine<DimensionTypeClass> dimensionTypeClassBuilder = defineClass<DimensionTypeClass>("DimensionType")
                                                                .constructor(nullptr)

                                                                .build();

DimensionTypeClass::DimensionTypeClass(DimensionType* dimensionType)
: ScriptClass(ConstructFromCpp<DimensionTypeClass>{}) {
    this->mDimensionType = dimensionType;
}

Local<Object> DimensionTypeClass::newDimensionType(DimensionType* dimensionType) {
    return (new DimensionTypeClass(dimensionType))->getScriptObject();
}
