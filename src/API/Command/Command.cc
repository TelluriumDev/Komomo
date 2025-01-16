#include "API/Command/Command.h"
#include "Command.h"
#include "Entry.h"
#include "Loader/ModManager.h"
#include "Manager/EngineData.h"
#include "ll/api/command/CommandRegistrar.h"

#include <memory>

using namespace Komomo;

ClassDefine<CommandClass> commandClassBuilder = defineClass<CommandClass>("Command")
                                                    .constructor(nullptr)

                                                    .function("newCommand", &CommandClass::newCommand)

                                                    .build();

std::unordered_map<std::string, std::shared_ptr<CommandData>> commands;

CommandClass::CommandClass(std::shared_ptr<CommandData> data) : ScriptClass(ConstructFromCpp<CommandClass>{}) {
    this->data = data;
}

Local<Object> CommandClass::newCommandClass(std::shared_ptr<CommandData> data) {
    commands[data->name] = data;
    return (new CommandClass(data))->getScriptObject();
}

Local<Object> CommandClass::newCommand(const Arguments& args) {
    try {
        std::shared_ptr<CommandData> data = std::make_shared<CommandData>();
        data->engine                      = EngineScope::currentEngine();
        if (args.size() == 2 && args[0].isString() && args[1].isString()) {
            data->name        = args[0].asString().toString();
            data->description = args[1].asString().toString();
            return newCommandClass(data);
        } else if (args.size() == 3 && args[0].isString() && args[1].isString() && args[2].isNumber()) {
            data->name            = args[0].asString().toString();
            data->description     = args[1].asString().toString();
            data->permissionLevel = CommandPermissionLevel(args[2].asNumber().toInt32());
            return newCommandClass(data);
        } else if (args.size() == 4 && args[0].isString() && args[1].isString() && args[2].isNumber()
                   && args[3].isNumber()) {
            data->name            = args[0].asString().toString();
            data->description     = args[1].asString().toString();
            data->permissionLevel = CommandPermissionLevel(args[2].asNumber().toInt32());
            data->flags           = CommandFlagValue(args[3].asNumber().toInt32());
            return newCommandClass(data);
        }
    }
    CatchNotReturn;
    return Object::newObject();
}

ll::command::CommandHandle& CommandClass::getCommandHandle() {
    return ll::command::CommandRegistrar::getInstance()
        .getOrCreateCommand(data->name, data->description, data->permissionLevel, data->flags);
}

Local<Value> CommandClass::setAlias(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        getCommandHandle().alias(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}


Local<Value> CommandClass::addParameter(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);

    Parameter p = {};
    try {
        if (args.size() == 2 && args[1].isNumber()) {
            p.name = args[0].asString().toString();
            p.type = ll::command::ParamKind::Kind(args[1].asNumber().toInt32());
            data->parameters.push_back(p);
        } else if (args.size() == 3 && args[1].isNumber() && args[2].isBoolean()) {
            p.name     = args[0].asString().toString();
            p.type     = ll::command::ParamKind::Kind(args[1].asNumber().toInt32());
            p.optional = args[2].asBoolean().value();
            data->parameters.push_back(p);
        } else if (args.size() == 4 && args[1].isNumber() && args[2].isBoolean() && args[3].isString()) {
            p.name     = args[0].asString().toString();
            p.type     = ll::command::ParamKind::Kind(args[1].asNumber().toInt32());
            p.optional = args[2].asBoolean().value();
            p.enumName = args[3].asString().toString();
            data->parameters.push_back(p);
        } else if (args.size() == 5 && args[1].isNumber() && args[2].isBoolean() && args[3].isString()
                   && args[4].isNumber()) {
            p.name     = args[0].asString().toString();
            p.type     = ll::command::ParamKind::Kind(args[1].asNumber().toInt32());
            p.optional = args[2].asBoolean().value();
            p.enumName = args[3].asString().toString();
            p.option   = CommandParameterOption(args[4].asNumber().toInt32());
            data->parameters.push_back(p);
        } else if (args.size() == 6 && args[1].isNumber() && args[2].isBoolean() && args[3].isString()
                   && args[4].isNumber() && args[5].isString()) {
            p.name       = args[0].asString().toString();
            p.type       = ll::command::ParamKind::Kind(args[1].asNumber().toInt32());
            p.optional   = args[2].asBoolean().value();
            p.enumName   = args[3].asString().toString();
            p.option     = CommandParameterOption(args[4].asNumber().toInt32());
            p.identifier = args[5].asString().toString();
            data->parameters.push_back(p);
            return Boolean::newBoolean(true);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
    return Boolean::newBoolean(true);
}


Local<Value> CommandClass::setCallBack(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kFunction);

    try {
        this->data->callBack = Global<Function>(args[0].asFunction());
    }
    CatchNotReturn;
    return Local<Value>();
}

void CommandClass::onExecute(
    CommandOrigin const&               origin,
    CommandOutput&                     output,
    ll::command::RuntimeCommand const& runtime
) {
    const auto name = runtime.getCommandName();
    if (commands.empty()) {
        return;
    }

    auto command = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(name).runtimeOverload(
        GET_ENGINE_DATA(commands[name]->engine)->mMod
    );

    
}