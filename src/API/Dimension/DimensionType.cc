#include "API/Dimension/DimensionType.h"


ClassDefine<DimensionTypeClass> dimensiontypeClassBuilder = defineClass<DimensionTypeClass>("DimensionType")
                                                                .constructor(nullptr)

                                                                .build();

DimensionTypeClass::DimensionTypeClass(DimensionType* dimensiontype)
: ScriptClass(ConstructFromCpp<DimensionTypeClass>{}) {
    this->mDimensionType = dimensiontype;
}

Local<Object> DimensionTypeClass::newDimensionType(DimensionType* dimensiontype) {
    return (new DimensionTypeClass(dimensiontype))->getScriptObject();
}
