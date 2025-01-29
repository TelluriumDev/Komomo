#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/server/commands/MinecraftCommands.h>

class MinecraftCommands;

class MinecraftCommandsClass : public ScriptClass {
public:
    MinecraftCommands* mMinecraftCommands;

public:
    MinecraftCommandsClass(MinecraftCommands* minecraftCommands);

public:
    static Local<Object> newMinecraftCommands(MinecraftCommands* minecraftCommands);

public: /* Member */
public: /* Method */
};

extern ClassDefine<MinecraftCommandsClass> minecraftCommandsClassBuilder;