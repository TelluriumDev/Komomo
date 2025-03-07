#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Actor/Actor.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
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
#include <mc/server/commands/CommandMessage.h>
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
    std::string name;
    ll::command::ParamKind::Kind type;
    bool optional;
    std::string enumName;
    CommandParameterOption option;
    std::string text;
};

struct CommandData {
    std::string name;
    std::string description = "";
    CommandPermissionLevel permissionLevel = CommandPermissionLevel::Admin;
    CommandFlag flag = CommandFlagValue::None;
    ScriptEngine *engine = nullptr;
    std::vector<Parameter> parameters = {};
    Global<Function> callback = Global(Function::newFunction([]() {
    }));
    CommandOutput *output = nullptr;
    CommandOrigin *origin = nullptr;
};


extern std::unordered_map<std::string, std::shared_ptr<CommandData> > commands;


class CommandClass : public ScriptClass {
private:
    std::shared_ptr<CommandData> data;

    CommandClass(std::shared_ptr<CommandData> data);

    ll::command::CommandHandle &getCommandHandle();

public:
    static Local<Object> newCommandClass(std::shared_ptr<CommandData> data);

    static Local<Object> newCommand(const Arguments &args);

    Local<Value> setAlias(const Arguments &args);

    Local<Value> setCallback(const Arguments &args);

    Local<Value> optional(const Arguments &args);

    Local<Value> required(const Arguments &args);

    Local<Value> overload(const Arguments &args);

    Local<Value> text(const Arguments &args);

    Local<Value> addEnum(const Arguments &args);

    Local<Value> setSoftEnum(const Arguments &args);

    Local<Value> addSoftEnum(const Arguments &args);

    Local<Value> removeSoftEnum(const Arguments &args);

    static Local<Value> run(const Arguments &args);

    static void
    onExecute(CommandOrigin const &origin, CommandOutput &output, ll::command::RuntimeCommand const &runtime);

    static inline Local<Value>
    ConvertToScriptX(ll::command::ParamStorageType const &result, CommandOrigin const &origin, CommandOutput &output) {
        using namespace ll::command;
        if (!result.has_value()) return {};
        if (result.hold(ParamKind::Kind::Enum)) {
            return String::newString(std::get<RuntimeEnum>(result.value()).name);
        }
        if (result.hold(ParamKind::Kind::SoftEnum)) {
            return String::newString(std::get<RuntimeSoftEnum>(result.value()));
        }
        if (result.hold(ParamKind::Kind::BlockName)) {
            return BlockClass::newBlock(
                const_cast<Block *>(std::get<CommandBlockName>(result.value()).resolveBlock(0).mBlock)
            );
        }
        if (result.hold(ParamKind::Kind::Item)) {
            return ItemStackClass::newItemStack(new ItemStack(std::get<CommandItem>(result.value())
                .createInstance(1, 1, output, true)
                .value_or(ItemInstance::EMPTY_ITEM())));
        }
        if (result.hold(ParamKind::Kind::Actor)) {
            auto arr = Array::newArray();
            for (auto i: std::get<CommandSelector<Actor> >(result.value()).results(origin)) {
                arr.add(ActorClass::newActor(i));
            }
            return arr;
        }
        if (result.hold(ParamKind::Kind::Player)) {
            auto arr = Array::newArray();
            for (auto i: std::get<CommandSelector<Player> >(result.value()).results(origin)) {
                arr.add(PlayerClass::newPlayer(i));
            }
            return arr;
        }
        if (result.hold(ParamKind::Kind::BlockPos)) {
            return BlockPosClass::newBlockPosClass(
                std::get<CommandPosition>(result.value())
                .getBlockPos(CommandVersion::CurrentVersion(), origin, Vec3::ZERO())
            );
        }
        if (result.hold(ParamKind::Kind::Vec3)) {
            return Vec3Class::newVec3Class(std::get<CommandPosition>(result.value())
                .getPosition(CommandVersion::CurrentVersion(), origin, Vec3::ZERO()));
        }
        if (result.hold(ParamKind::Kind::Message)) {
            return String::newString(std::get<CommandMessage>(result.value())
                .generateMessage(origin, CommandVersion::CurrentVersion())
                .mMessage);
        }
        if (result.hold(ParamKind::Kind::RawText)) {
            return String::newString(std::get<CommandRawText>(result.value()).mText);
        }
        if (result.hold(ParamKind::Kind::JsonValue)) {
            return String::newString(JsonHelpers::serialize(std::get<Json::Value>(result.value())));
        }
        if (result.hold(ParamKind::Kind::Effect)) {
            return String::newString(std::get<MobEffect const *>(result.value())->mResourceName);
        }
        if (result.hold(ParamKind::Kind::Command)) {
            return String::newString(std::get<std::unique_ptr<::Command> >(result.value())->getCommandName());
        }
        if (result.hold(ParamKind::Kind::ActorType)) {
            return String::newString(
                std::get<ActorDefinitionIdentifier const *>(result.value())->mCanonicalName->c_str());
        }
        if (result.hold(ParamKind::Kind::Bool)) {
            return Boolean::newBoolean(std::get<bool>(result.value()));
        }
        if (result.hold(ParamKind::Kind::Int)) {
            return Number::newNumber(std::get<int>(result.value()));
        }
        if (result.hold(ParamKind::Kind::Float)) {
            return Number::newNumber(std::get<float>(result.value()));
        }
        if (result.hold(ParamKind::Kind::String)) {
            return String::newString(std::get<std::string>(result.value()));
        }
        return {};
    }

    static ClassDefine<CommandClass> commandClassBuilder;
};


