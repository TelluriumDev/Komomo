#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class CommandContext;

class CommandContextClass : public ScriptClass {
private:
    CommandContext* mCommandContext;

public:
    CommandContextClass(CommandContext* commandContext);

public:
    static Local<Object> newCommandContext(CommandContext* commandContext);

public: /* Member */
public: /* Method */
};

extern ClassDefine<CommandContextClass> commandContextClassBuilder;