#include "API/Dimension/Dimension.h"


ClassDefine<DimensionClass> dimensionClassBuilder = defineClass<DimensionClass>("Dimension")
                                                                .constructor(nullptr)

                                                                .build();

DimensionClass::DimensionClass(Dimension* dimension)
: ScriptClass(ConstructFromCpp<DimensionClass>{}) {
    this->mDimension = dimension;
}

Local<Object> DimensionClass::newDimension(Dimension* dimension) {
    return (new DimensionClass(dimension))->getScriptObject();
}
