#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class CommandOrigin;

class CommandOriginClass : public ScriptClass {
public:
    CommandOrigin* mCommandOrigin;

public:
    CommandOriginClass(CommandOrigin* commandOrigin);

public:
    static Local<Object> newCommandOrigin(CommandOrigin* commandOrigin);

public: /* Member */
public: /* Method */
};

extern ClassDefine<CommandOriginClass> commandOriginClassBuilder;