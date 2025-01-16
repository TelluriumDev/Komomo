#include "API/Command/MinecraftCommands.h"


ClassDefine<MinecraftCommandsClass> minecraftCommandsClassBuilder =
    defineClass<MinecraftCommandsClass>("MinecraftCommands")
        .constructor(nullptr)

        .build();

MinecraftCommandsClass::MinecraftCommandsClass(MinecraftCommands* minecraftCommands)
: ScriptClass(ConstructFromCpp<MinecraftCommandsClass>{}) {
    this->mMinecraftCommands = minecraftCommands;
}

Local<Object> MinecraftCommandsClass::newMinecraftCommands(MinecraftCommands* minecraftCommands) {
    return (new MinecraftCommandsClass(minecraftCommands))->getScriptObject();
}
