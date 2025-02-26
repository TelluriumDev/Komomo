#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Command/CommandOutput.h"
#include "API/Item/ItemStack.h"
#include "API/Math/Vec3.h"
#include "API/Player/Player.h"


#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/command/Optional.h>
#include <ll/api/command/runtime/ParamKind.h>
#include <ll/api/command/runtime/RuntimeCommand.h>
#include <ll/api/command/runtime/RuntimeOverload.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/service/Service.h>

#include <mc/server/commands/CommandBlockName.h>
#include <mc/server/commands/CommandBlockNameResult.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandMessage.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/server/commands/GenerateMessageResult.h>
#include <mc/server/commands/ServerCommandOrigin.h>
#include <mc/util/JsonHelpers.h>
#include <mc/world/Minecraft.h>
#include <mc/world/item/ItemInstance.h>
#include <mc/world/item/ItemStack.h>


#include <string>
#include <unordered_map>

using namespace ll::command;

struct Parameter {
    std::string                  name;
    ll::command::ParamKind::Kind type;
    bool                         optional;
    std::string                  enumName;
    CommandParameterOption       option;
    std::string                  text;
};

struct CommandData {
    std::string            name;
    std::string            description     = "";
    CommandPermissionLevel permissionLevel = CommandPermissionLevel::Admin;
    CommandFlag            flag            = CommandFlagValue::None;
    ScriptEngine*          engine          = nullptr;
    std::vector<Parameter> parameters      = {};
    Global<Function>       callback        = Global(Function::newFunction([]() {}));
    CommandOutput*         output          = nullptr;
    CommandOrigin*         origin          = nullptr;
};


extern std::unordered_map<std::string, std::shared_ptr<CommandData>> commands;


class CommandClass : public ScriptClass {

private:
    std::shared_ptr<CommandData> data;

    CommandClass(std::shared_ptr<CommandData> data);

    ll::command::CommandHandle& getCommandHandle();

public:
    static Local<Object> newCommandClass(std::shared_ptr<CommandData> data);

    static Local<Object> newCommand(const Arguments& args);

    Local<Value> setAlias(const Arguments& args);

    Local<Value> setCallback(const Arguments& args);

    Local<Value> optional(const Arguments& args);

    Local<Value> required(const Arguments& args);

    Local<Value> overload(const Arguments& args);

    Local<Value> text(const Arguments& args);

    Local<Value> addEnum(const Arguments& args);

    Local<Value> setSoftEnum(const Arguments& args);

    Local<Value> addSoftEnum(const Arguments& args);

    Local<Value> removeSoftEnum(const Arguments& args);

    static Local<Value> run(const Arguments& args);

    static void
    onExecute(CommandOrigin const& origin, CommandOutput& output, ll::command::RuntimeCommand const& runtime);

    static Local<Value>
    convertResult(ll::command::ParamStorageType const& result, CommandOrigin const& origin, CommandOutput& output);
};

extern ClassDefine<CommandClass> commandClassBuilder;