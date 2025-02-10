#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/IConstBlockSource.h>

class IConstBlockSourceClass : public ScriptClass {
public:
    IConstBlockSource* mIConstBlockSource;

public:
    IConstBlockSourceClass(IConstBlockSource* iConstBlockSource);

public:
    // static IConstBlockSourceClass* create(const Arguments& args); // TODO
    static Local<Object> newIConstBlockSource(IConstBlockSource* iConstBlockSource);

public: /* Member */
public: /* Method */
};

extern ClassDefine<IConstBlockSourceClass> iConstBlockSourceClassBuilder;
