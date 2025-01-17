#include "API/Command/CommandRegistry.h"

ClassDefine<CommandRegistryClass> commandRegistryClassBuilder =
    defineClass<CommandRegistryClass>("CommandRegistry")
        .constructor(nullptr)

        .build();

CommandRegistryClass::CommandRegistryClass(CommandRegistry* commandRegistry)
: ScriptClass(ConstructFromCpp<CommandRegistryClass>{}) {
    this->mCommandRegistry = commandRegistry;
}

Local<Object> CommandRegistryClass::newCommandRegistry(CommandRegistry* commandRegistry) {
    return (new CommandRegistryClass(commandRegistry))->getScriptObject();
}
