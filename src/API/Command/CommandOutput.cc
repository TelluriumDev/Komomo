#include "API/Command/CommandOutput.h"


ClassDefine<CommandOutputClass> commandOutputClassBuilder = defineClass<CommandOutputClass>("CommandOutput")
                                                                  .constructor(nullptr)

                                                                  .build();

CommandOutputClass::CommandOutputClass(CommandOutput* commandOutput)
: ScriptClass(ConstructFromCpp<CommandOutputClass>{}) {
    this->mCommandOutput = commandOutput;
}

Local<Object> CommandOutputClass::newCommandOutput(CommandOutput* commandOutput) {
    return (new CommandOutputClass(commandOutput))->getScriptObject();
}
