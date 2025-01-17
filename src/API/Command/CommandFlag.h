#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class CommandFlag;

class CommandFlagClass : public ScriptClass {
public:
    CommandFlag* mCommandFlag;

public:
    CommandFlagClass(CommandFlag* commandFlag);

public:
    static Local<Object> newCommandFlag(CommandFlag* commandFlag);

public: /* Member */
public: /* Method */
};

extern ClassDefine<CommandFlagClass> commandFlagClassBuilder;