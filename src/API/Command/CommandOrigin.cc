#include "API/Command/CommandOrigin.h"


ClassDefine<CommandOriginClass> commandOriginClassBuilder = defineClass<CommandOriginClass>("CommandOrigin")
                                                                .constructor(nullptr)

                                                                .build();

CommandOriginClass::CommandOriginClass(CommandOrigin* commandOrigin)
: ScriptClass(ConstructFromCpp<CommandOriginClass>{}) {
    this->mCommandOrigin = commandOrigin;
}

Local<Object> CommandOriginClass::newCommandOrigin(CommandOrigin* commandOrigin) {
    return (new CommandOriginClass(commandOrigin))->getScriptObject();
}
