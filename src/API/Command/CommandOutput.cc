#include "API/Command/CommandOutput.h"
#include "API/APIHelper.h"
#include "API/Actor/Actor.h"

using namespace Komomo;


ClassDefine<CommandOutputClass> commandOutputClassBuilder =
    defineClass<CommandOutputClass>("CommandOutput")
        .constructor(nullptr)

        .instanceFunction("success", &CommandOutputClass::success)
        .instanceFunction("error", &CommandOutputClass::error)
        .instanceFunction("addToResultList", &CommandOutputClass::addToResultList)
        .instanceFunction("empty", &CommandOutputClass::empty)
        .instanceFunction("setHasPlayerText", &CommandOutputClass::setHasPlayerText)
        .instanceFunction("wantsData", &CommandOutputClass::wantsData)

        .build();

CommandOutputClass::CommandOutputClass(CommandOutput* commandOutput)
: ScriptClass(ConstructFromCpp<CommandOutputClass>{}) {
    this->mCommandOutput = commandOutput;
}

Local<Object> CommandOutputClass::newCommandOutput(CommandOutput* commandOutput) {
    return (new CommandOutputClass(commandOutput))->getScriptObject();
}

Local<Value> CommandOutputClass::success(const Arguments& args) {
    if (!mCommandOutput) return Local<Value>();
    if (args.size() == 0) {
        mCommandOutput->success();
    } else if (args.size() == 1) {
        CheckArgType(args[0], ValueKind::kString);
        mCommandOutput->success(args[0].asString().toString());
    } else if (args.size() == 2) {
        //         CheckArgType(args[0], ValueKind::kString)
        //         CheckArgType(args[1], ValueKind::kArray)
        //
        //         mCommandOutput->success(
        //             args[0].asString().toString(),
        //
        //         );
    }
    return Local<Value>();
}

Local<Value> CommandOutputClass::error(const Arguments& args) {
    if (!mCommandOutput) return Local<Value>();
    if (args.size() == 1) {
        CheckArgType(args[0], ValueKind::kString);
        mCommandOutput->success(args[0].asString().toString());
    } else if (args.size() == 2) {
        //         CheckArgType(args[0], ValueKind::kString)
        //         CheckArgType(args[1], ValueKind::kArray)
        //
        //         mCommandOutput->error(
        //             args[0].asString().toString(),
        //
        //         );
    }
    return Local<Value>();
};

// MCAPI void addMessage(
//     ::std::string const&                           msgId,
//     ::std::vector<::CommandOutputParameter> const& params,
//     ::CommandOutputMessageType                     type
// ); // TODO: Class
//  Local<Value> addMessage(const Arguments& args);

Local<Value> CommandOutputClass::addToResultList(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!mCommandOutput) return Local<Value>();
        if (IsInstanceOf<ActorClass>(args[1])) {
            auto engine = EngineScope::currentEngine();
            auto actor  = engine->getNativeInstance<ActorClass>(args[1]);
            mCommandOutput->addToResultList(args[0].asString().toString(), *actor->mActor);
        } else {
            CheckArgType(args[1], ValueKind::kString);
            mCommandOutput->addToResultList(args[0].asString().toString(), args[1].asString().toString());
        }
    }
    CatchNotReturn;
    return Local<Value>();
};

Local<Value> CommandOutputClass::empty() {
    if (!mCommandOutput) return Local<Value>();
    return Boolean::newBoolean(mCommandOutput->empty());
};

// Local<Value> forceOutput(const Arguments& args); // TODO: Class

// Local<Value> getData(const Arguments& args); // TODO: Class

// Local<Value> getMessages(); // TODO: Class

// Local<Value> getType(); // TODO: Class

// MCAPI void load(
//     ::CommandOutputType                       type,
//     int                                       successCount,
//     ::std::vector<::CommandOutputMessage>&&   messages,
//     ::std::unique_ptr<::CommandPropertyBag>&& data
// ); //TODO: Class
// Local<Value> load(const Arguments& args);

Local<Value> CommandOutputClass::setHasPlayerText(const Arguments& args) {
    if (!mCommandOutput) return Local<Value>();
    mCommandOutput->setHasPlayerText();
    return Local<Value>();
};

Local<Value> CommandOutputClass::wantsData() {
    if (!mCommandOutput) return Local<Value>();
    return Boolean::newBoolean(mCommandOutput->wantsData());
};
