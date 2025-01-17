#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class CommandRegistry;

class CommandRegistryClass : public ScriptClass {
public:
    CommandRegistry* mCommandRegistry;

public:
    CommandRegistryClass(CommandRegistry* commandRegistry);

public:
    static Local<Object> newCommandRegistry(CommandRegistry* commandRegistry);

public: /* Member */
public: /* Method */
};

extern ClassDefine<CommandRegistryClass> commandRegistryClassBuilder;