#include "API/Dimension/ChangeDimensionRequest.h"


ClassDefine<ChangeDimensionRequestClass> changeDimensionRequestClassBuilder = defineClass<ChangeDimensionRequestClass>("ChangeDimensionRequest")
                                                                .constructor(nullptr)

                                                                .build();

ChangeDimensionRequestClass::ChangeDimensionRequestClass(ChangeDimensionRequest* changeDimensionRequest)
: ScriptClass(ConstructFromCpp<ChangeDimensionRequestClass>{}) {
    this->mChangeDimensionRequest = changeDimensionRequest;
}

Local<Object> ChangeDimensionRequestClass::newChangeDimensionRequest(ChangeDimensionRequest* changeDimensionRequest) {
    return (new ChangeDimensionRequestClass(changeDimensionRequest))->getScriptObject();
}

