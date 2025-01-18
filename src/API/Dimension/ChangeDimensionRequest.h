#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include "mc/world/level/ChangeDimensionRequest.h"


class ChangeDimensionRequest;

class ChangeDimensionRequestClass : public ScriptClass {
public:
    ChangeDimensionRequest* mChangeDimensionRequest;

public:
    ChangeDimensionRequestClass(ChangeDimensionRequest* changeDimensionRequest);

public:
    static Local<Object> newChangeDimensionRequest(ChangeDimensionRequest* changeDimensionRequest);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ChangeDimensionRequestClass> changeDimensionRequestClassBuilder;