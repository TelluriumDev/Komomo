#pragma once

#include "API/APIHelper.h"             // IWYU pragma: keep
#include "API/Command/CommandOrigin.h" // IWYU pragma: keep
#include "API/Command/CommandOutput.h"


#include <functional>
#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/command/Optional.h>
#include <ll/api/command/runtime/ParamKind.h>
#include <ll/api/command/runtime/RuntimeCommand.h>
#include <ll/api/command/runtime/RuntimeOverload.h>


#include <ll/api/service/Bedrock.h>
#include <ll/api/service/Service.h>

#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandPermissionLevel.h>


#include <memory>
#include <unordered_map>
#include <vector>


struct Parameter {
    std::string                  name;
    ll::command::ParamKind::Kind type;
    bool                         optional;
    std::string                  enumName;
    CommandParameterOption       option;
    std::string                  identifier;
};

struct CommandData {
    std::string            name;
    std::string            description;
    CommandPermissionLevel permissionLevel = CommandPermissionLevel::Admin;
    CommandFlag            flags           = CommandFlagValue::None;
    ScriptEngine*          engine          = nullptr;
    std::vector<Parameter> parameters      = {};
    Global<Function>       callback;
    CommandOutput*         output = nullptr;
    CommandOrigin*         origin = nullptr;
};


extern std::unordered_map<std::string, std::shared_ptr<CommandData>> commands;


class CommandClass : public ScriptClass {

private:
    std::shared_ptr<CommandData> data;

    CommandClass(std::shared_ptr<CommandData> data);

    ll::command::CommandHandle& getCommandHandle();

std::function<void(CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& runtime)> onExecute;

    public : static Local<Object> newCommandClass(std::shared_ptr<CommandData> data);

    static Local<Object> newCommand(const Arguments& args);

    Local<Value> setAlias(const Arguments& args);

    Local<Value> optional(const Arguments& args);

    Local<Value> required(const Arguments& args);

    Local<Value> overload(const Arguments& args);

    Local<Value> execute(const Arguments& args);

    
};

extern ClassDefine<CommandClass> commandClassBuilder;