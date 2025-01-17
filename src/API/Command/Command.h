#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Block/Block.h"
#include "API/Command/CommandOrigin.h" // IWYU pragma: keep
#include "API/Command/CommandOutput.h"
#include "API/Item/ItemStack.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"
#include "mc/world/level/block/Block.h"


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
    std::string            description;
    CommandPermissionLevel permissionLevel = CommandPermissionLevel::Admin;
    CommandFlag            flag           = CommandFlagValue::None;
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

        static void onExecute(
            CommandOrigin const&               origin,
            CommandOutput&                     output,
            ll::command::RuntimeCommand const& runtime
        );

    static Local<Value>
    convertResult(ll::command::ParamStorageType const& result, CommandOrigin const& origin, CommandOutput& output) {
        using namespace ll::command;
        if (!result.has_value()) return {};
        if (result.hold(ParamKind::Kind::Enum)) {
            return String::newString(std::get<RuntimeEnum>(result.value()).name);
        } else if (result.hold(ParamKind::Kind::SoftEnum)) {
            return String::newString(std::get<RuntimeSoftEnum>(result.value()));
        } else if (result.hold(ParamKind::Kind::BlockName)) {
            return BlockClass::newBlock(
                const_cast<Block*>(std::get<CommandBlockName>(result.value()).resolveBlock(0).getBlock())
            );
        } else if (result.hold(ParamKind::Kind::Item)) {
            return ItemStackClass::newItemStack(new ItemStack(std::get<CommandItem>(result.value())
                                                                  .createInstance(1, 1, output, true)
                                                                  .value_or(ItemInstance::EMPTY_ITEM()))
            ); // Not managed by BDS, pointer will be saved as unique_ptr
        } else if (result.hold(ParamKind::Kind::Actor)) {
            // auto arr = Array::newArray();
            // for (auto i : std::get<CommandSelector<Actor>>(result.value()).results(origin)) {
            //     arr.add(EntityClass::newEntity(i));
            // }
            // return arr;
        } else if (result.hold(ParamKind::Kind::Player)) {
            auto arr = Array::newArray();
            for (auto i : std::get<CommandSelector<Player>>(result.value()).results(origin)) {
                arr.add(PlayerClass::newPlayer(i));
            }
            return arr;
        } else if (result.hold(ParamKind::Kind::BlockPos)) {
            auto dim = origin.getDimension();
            // return IntPos::newPos(
            //     std::get<CommandPosition>(result.value())
            //         .getBlockPos(CommandVersion::CurrentVersion(), origin, Vec3::ZERO()),
            //     dim ? dim->getDimensionId().id : -1
            // );
        } else if (result.hold(ParamKind::Kind::Vec3)) {
            auto dim = origin.getDimension();
            // return FloatPos::newPos(
            //     std::get<CommandPosition>(result.value())
            //         .getPosition(CommandVersion::CurrentVersion(), origin, Vec3::ZERO()),
            //     dim ? dim->getDimensionId().id : -1
            // );
        } else if (result.hold(ParamKind::Kind::Message)) {
            return String::newString(std::get<CommandMessage>(result.value())
                                         .generateMessage(origin, CommandVersion::CurrentVersion())
                                         .mMessage->c_str());
        } else if (result.hold(ParamKind::Kind::RawText)) {
            return String::newString(std::get<CommandRawText>(result.value()).getText());
        } else if (result.hold(ParamKind::Kind::JsonValue)) {
            // return String::newString(JsonHelpers::serialize(std::get<Json::Value>(result.value())));
        } else if (result.hold(ParamKind::Kind::Effect)) {
            return String::newString(std::get<MobEffect const*>(result.value())->getResourceName());
        } else if (result.hold(ParamKind::Kind::Command)) {
            return String::newString(std::get<std::unique_ptr<::Command>>(result.value())->getCommandName());
        } else if (result.hold(ParamKind::Kind::ActorType)) {
            return String::newString(std::get<ActorDefinitionIdentifier const*>(result.value())->getCanonicalName());
        } else if (result.hold(ParamKind::Kind::Bool)) {
            return Boolean::newBoolean(std::get<bool>(result.value()));
        } else if (result.hold(ParamKind::Kind::Int)) {
            return Number::newNumber(std::get<int>(result.value()));
        } else if (result.hold(ParamKind::Kind::Float)) {
            return Number::newNumber(std::get<float>(result.value()));
        } else if (result.hold(ParamKind::Kind::String)) {
            return String::newString(std::get<std::string>(result.value()));
        }
        return {};
    }
};

extern ClassDefine<CommandClass> commandClassBuilder;