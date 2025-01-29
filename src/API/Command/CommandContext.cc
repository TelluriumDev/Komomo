#include "API/Command/CommandContext.h"

ClassDefine<CommandContextClass> commandContextClassBuilder = defineClass<CommandContextClass>("CommandContext")
                                                                  .constructor(nullptr)

                                                                  .build();

CommandContextClass::CommandContextClass(CommandContext* commandContext)
: ScriptClass(ConstructFromCpp<CommandContextClass>{}) {
    this->mCommandContext = commandContext;
}

Local<Object> CommandContextClass::newCommandContext(CommandContext* commandContext) {
    return (new CommandContextClass(commandContext))->getScriptObject();
}
