#include "API/Command/Command.h"
#include "API/Command/CommandContext.h"
#include "API/Command/CommandOrigin.h"
#include "API/Command/MCRESULT.h"
#include "API/Command/MinecraftCommands.h"
#include "API/Level/Level.h"

using namespace Komomo;

ClassDefine<CommandClass> commandClassBuilder = defineClass<CommandClass>("Command")
                                                    .constructor(nullptr)

                                                    .function("newCommand", &CommandClass::newCommand)
                                                    .function("run", &CommandClass::run)
                                                    .instanceFunction("setCallback", &CommandClass::setCallback)
                                                    .instanceFunction("optional", &CommandClass::optional)
                                                    .instanceFunction("required", &CommandClass::required)
                                                    .instanceFunction("text", &CommandClass::text)
                                                    .instanceFunction("addEnum", &CommandClass::addEnum)
                                                    .instanceFunction("addSoftEnum", &CommandClass::addSoftEnum)
                                                    .instanceFunction("setSoftEnum", &CommandClass::setSoftEnum)
                                                    .instanceFunction("removeSoftEnum", &CommandClass::removeSoftEnum)
                                                    .instanceFunction("overload", &CommandClass::overload)

                                                    .build();

std::unordered_map<std::string, std::shared_ptr<CommandData>> commands;

CommandClass::CommandClass(std::shared_ptr<CommandData> data) : ScriptClass(ConstructFromCpp<CommandClass>{}) {
    this->data = data;
}


ll::command::CommandHandle& CommandClass::getCommandHandle() {
    return ll::command::CommandRegistrar::getInstance().getOrCreateCommand(data->name);
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
            auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(data->name, data->description);
            return newCommandClass(data);
        } else if (args.size() == 3 && args[0].isString() && args[1].isString() && args[2].isNumber()) {
            data->name            = args[0].asString().toString();
            data->description     = args[1].asString().toString();
            data->permissionLevel = CommandPermissionLevel(args[2].asNumber().toInt32());
            auto& cmd             = ll::command::CommandRegistrar::getInstance()
                            .getOrCreateCommand(data->name, data->description, data->permissionLevel);
            return newCommandClass(data);
        } else if (args.size() == 4 && args[0].isString() && args[1].isString() && args[2].isNumber()
                   && args[3].isNumber()) {
            data->name            = args[0].asString().toString();
            data->description     = args[1].asString().toString();
            data->permissionLevel = CommandPermissionLevel(args[2].asNumber().toInt32());
            data->flag            = CommandFlagValue(args[3].asNumber().toInt32());
            auto& cmd             = ll::command::CommandRegistrar::getInstance()
                            .getOrCreateCommand(data->name, data->description, data->permissionLevel, data->flag);
            return newCommandClass(data);
        }
    }
    CatchNotReturn;
    return Object::newObject();
}


Local<Value> CommandClass::setAlias(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        ll::command::CommandRegistrar::getInstance()
            .getOrCreateCommand(args[0].asString().toString())
            .alias(args[0].asString().toString());
        return Boolean::newBoolean(true);
    }
    CatchReturn(Boolean::newBoolean(false));
}


Local<Value> CommandClass::setCallback(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kFunction);

    try {
        data->callback = Global<Function>(args[0].asFunction());
    }
    CatchNotReturn;
    return Local<Value>();
}

void CommandClass::onExecute(
    CommandOrigin const&               origin,
    CommandOutput&                     output,
    ll::command::RuntimeCommand const& runtime
) {
    auto        cmdName = runtime.getCommandName();
    auto        data    = commands[cmdName];
    EngineScope scope(data->engine);
    auto        func = data->callback;

    Local<Object> args = Object::newObject();

    for (auto& info : commands[cmdName]->parameters) {
        try {
            if (info.type == ll::command::ParamKind::Kind::Enum
                || info.type == ll::command::ParamKind::Kind::SoftEnum) {
                auto& param = runtime[info.enumName];
                args.set(info.name, convertResult(param, origin, output));
            } else {
                auto& param = runtime[info.name];
                args.set(info.name, convertResult(param, origin, output));
            }
        } catch (std::out_of_range&) {
            continue;
        }
    }
    try {
        func.get().call(
            {},
            CommandClass::newCommandClass(data),
            CommandOriginClass::newCommandOrigin(&origin),
            CommandOutputClass::newCommandOutput(&output),
            args
        );
    }
    CatchNotReturn;
}

Local<Value> CommandClass::optional(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckArgType(args[2], ValueKind::kNumber);

    try {
        Parameter p;
        p.name     = args[0].asString().toString();
        p.type     = ParamKind::Kind(args[1].asNumber().toInt32());
        p.optional = true;
        p.option   = CommandParameterOption(args[2].asNumber().toInt32());
        if (args.size() >= 4 && args[3].isString()) {
            p.enumName = args[3].asString().toString();
        }
        data->parameters.push_back(p);
    } catch (std::runtime_error& e) {
        throw e;
    }
    return this->getScriptObject();
};

Local<Value> CommandClass::required(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kNumber);
    CheckArgType(args[2], ValueKind::kNumber);
    try {
        Parameter p;
        p.name     = args[0].asString().toString();
        p.type     = ParamKind::Kind(args[1].asNumber().toInt32());
        p.optional = false;
        p.option   = CommandParameterOption(args[2].asNumber().toInt32());
        if (args.size() >= 4 && args[3].isString()) {
            p.enumName = args[3].asString().toString();
        }
        data->parameters.push_back(p);
    } catch (std::runtime_error& e) {
        throw e;
    }
    return this->getScriptObject();
};

Local<Value> CommandClass::overload(const Arguments& args) {
    try {
        auto cmd = getCommandHandle().runtimeOverload(ENGINE_DATA()->mMod);
        for (auto& param : data->parameters) {
            if (!param.text.empty()) {
                auto& a = cmd.text(param.text);
                continue;
            }
            if (param.name.empty()) continue;
            if (param.optional) {
                if (param.type == ParamKind::Kind::Enum || param.type == ParamKind::Kind::SoftEnum) {
                    auto& a = cmd.optional(param.name, param.type, param.enumName).option(param.option);
                } else {
                    auto& a = cmd.optional(param.name, param.type).option(param.option);
                }
            } else {
                if (param.type == ParamKind::Kind::Enum || param.type == ParamKind::Kind::SoftEnum) {
                    auto& a = cmd.required(param.enumName, param.type, param.enumName).option(param.option);
                } else {
                    auto& a = cmd.required(param.name, param.type).option(param.option);
                }
            }
        }
        cmd.execute(onExecute);
        data->parameters.clear();
    } catch (std::runtime_error& e) {
        throw e;
    }
    return Local<Value>();
};

Local<Value> CommandClass::text(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        Parameter p;
        p.text = args[0].asString().toString();
        data->parameters.push_back(p);
    }
    CatchNotReturn;
    return this->getScriptObject();
};


Local<Value> CommandClass::addEnum(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kArray);

    auto enumName  = args[0].asString().toString();
    auto enumArray = args[1].asArray();

    if (enumArray.size() == 0 || !enumArray.get(0).isString()) return Local<Value>();

    std::vector<std::pair<std::string, uint64>> enumValues;
    if (enumArray.size() == 0 || !enumArray.get(0).isString()) return Local<Value>();

    for (int i = 0; i < enumArray.size(); i++) {
        enumValues.push_back({enumArray.get(i).asString().toString(), i});
    }

    try {
        CommandRegistrar::getInstance().tryRegisterRuntimeEnum(enumName, std::move(enumValues));
    } catch (const std::exception& e) {
        throw e;
    }
    return Local<Value>();
}

Local<Value> CommandClass::setSoftEnum(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kArray);

    auto enumName  = args[0].asString().toString();
    auto enumArray = args[1].asArray();

    std::vector<std::string> enumValues;
    for (int i = 0; i < enumArray.size(); i++) {
        if (enumArray.size() == 0 || !enumArray.get(i).isString()) return Local<Value>();
        enumValues.push_back(enumArray.get(i).asString().toString());
    }

    try {
        CommandRegistrar::getInstance().tryRegisterSoftEnum(enumName, std::move(enumValues));
    } catch (const std::exception& e) {
        throw e;
    }
    return Local<Value>();
}

Local<Value> CommandClass::addSoftEnum(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kArray);

    auto enumName  = args[0].asString().toString();
    auto enumArray = args[1].asArray();

    std::vector<std::string> enumValues;
    for (int i = 0; i < enumArray.size(); i++) {
        if (enumArray.size() == 0 || !enumArray.get(i).isString()) return Local<Value>();
        enumValues.push_back(enumArray.get(i).asString().toString());
    }

    try {
        CommandRegistrar::getInstance().addSoftEnumValues(enumName, std::move(enumValues));
    } catch (const std::exception& e) {
        throw e;
    }
    return Local<Value>();
}

Local<Value> CommandClass::removeSoftEnum(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kArray);

    auto enumName  = args[0].asString().toString();
    auto enumArray = args[1].asArray();

    std::vector<std::string> enumValues;
    for (int i = 0; i < enumArray.size(); i++) {
        if (enumArray.size() == 0 || !enumArray.get(i).isString()) return Local<Value>();
        enumValues.push_back(enumArray.get(i).asString().toString());
    }

    try {
        CommandRegistrar::getInstance().removeSoftEnumValues(enumName, std::move(enumValues));
    } catch (const std::exception& e) {
        throw e;
    }
    return Local<Value>();
}

Local<Value> CommandClass::run(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    CommandContext context = CommandContext(
        args[0].asString().toString(),
        std::make_unique<ServerCommandOrigin>(
            "Server",
            ll::service::getLevel()->asServer(),
            CommandPermissionLevel::Owner,
            0
        ),
        CommandVersion::CurrentVersion()
    );
    try {
        return Boolean::newBoolean(ll::service::getMinecraft()->getCommands().executeCommand(context, false).mSuccess);
    }
    CatchNotReturn;
    return Boolean::newBoolean(false);
}