#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "Utils/Using.h"

#include <mc/server/commands/CommandOutput.h>


class CommandOutput;

class CommandOutputClass : public ScriptClass {
private:
    CommandOutput* mCommandOutput;

public:
    CommandOutputClass(CommandOutput* commandOutput);

public:
    static Local<Object> newCommandOutput(CommandOutput* commandOutput);


public: /* Method */
    Local<Value> success(const Arguments& args);

    Local<Value> error(const Arguments& args);

    // MCAPI void addMessage(
    //     ::std::string const&                           msgId,
    //     ::std::vector<::CommandOutputParameter> const& params,
    //     ::CommandOutputMessageType                     type
    // ); // TODO: Class
    //  Local<Value> addMessage(const Arguments& args);

    Local<Value> addToResultList(const Arguments& args);

    Local<Value> empty();

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

    Local<Value> setHasPlayerText(const Arguments& args);

    Local<Value> wantsData();

};


extern ClassDefine<CommandOutputClass> commandOutputClassBuilder;