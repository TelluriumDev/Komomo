#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class CommandOutput;

class CommandOutputClass : public ScriptClass {
public:
    CommandOutput* mCommandOutput;

public:
    CommandOutputClass(CommandOutput* commandOutput);

public:
    static Local<Object> newCommandOutput(CommandOutput* commandOutput);

public: /* Member */
public: /* Method */
};

extern ClassDefine<CommandOutputClass> commandOutputClassBuilder;