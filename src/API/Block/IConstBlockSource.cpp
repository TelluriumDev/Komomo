#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <API/Block/IConstBlockSource.h>

class IConstBlockSourceClass : public ScriptClass {
public:
    IConstBlockSource* mIConstBlockSource;

public:
    IConstBlockSourceClass(IConstBlockSource* iConstBlockSource);

public:
    static Local<Object> newIConstBlockSource(IConstBlockSource* iConstBlockSource);

public: /* Member */
public: /* Method */
    // Local<Value> fromNBT(const Arguments& args);
    // Local<Value> toNBT(const Arguments& args);
};

extern ClassDefine<IConstBlockSourceClass> iConstBlockSourceClassBuilder;