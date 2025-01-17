#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/platform/UUID.h>

class UUIDClass : public ScriptClass {
public:
     mce::UUID* mUUID;

public:
    UUIDClass (mce::UUID* uuid);

public:
    static Local<Object> newUUID( mce::UUID* uuid);

public: /* Member */
public: /* Method */
};

extern ClassDefine<UUIDClass> uuidClassBuilder;