#include "API/Command/CommandFlag.h"


ClassDefine<CommandFlagClass> commandFlagClassBuilder = defineClass<CommandFlagClass>("CommandFlag")
                                                                  .constructor(nullptr)

                                                                  .build();

CommandFlagClass::CommandFlagClass(CommandFlag* commandFlag)
: ScriptClass(ConstructFromCpp<CommandFlagClass>{}) {
    this->mCommandFlag = commandFlag;
}

Local<Object> CommandFlagClass::newCommandFlag(CommandFlag* commandFlag) {
    return (new CommandFlagClass(commandFlag))->getScriptObject();
}
