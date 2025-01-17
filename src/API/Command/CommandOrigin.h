#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


#include <mc/server/commands/CommandOrigin.h>

class CommandOriginClass : public ScriptClass {
private:
    CommandOrigin* mCommandOrigin;

public:
    CommandOriginClass(CommandOrigin* commandOrigin);

public:
    static Local<Object> newCommandOrigin(CommandOrigin* commandOrigin);

public:
    Local<Value> getRequestId();

    Local<Value> getName();

    Local<Value> getBlockPosition();

    Local<Value> getWorldPosition();

    // Local<Value> getRotation();

    Local<Value> getLevel();

    Local<Value> getDimension();

    Local<Value> getEntity();

    Local<Value> getPermissionsLevel();

    //     // vIndex: 9
    //     virtual ::CommandPermissionLevel getPermissionsLevel() const = 0;
    //
    //     // vIndex: 10
    //     virtual ::std::unique_ptr<::CommandOrigin> clone() const = 0;
    //
    //     // vIndex: 11
    //     virtual ::std::optional<::BlockPos> getCursorHitBlockPos() const;
    //
    //     // vIndex: 12
    //     virtual ::std::optional<::Vec3> getCursorHitPos() const;

    Local<Value> hasChatPerms();

    Local<Value> hasTellPerms();

    Local<Value> canUseAbility(const Arguments& args);

    Local<Value> isWorldBuilder();

    Local<Value> canUseCommandsWithoutCheatsEnabled();

    Local<Value> isSelectorExpansionAllowed();

    Local<Value> getSourceId();

    // Local<Value> getSourceSubId(); // TODO

    Local<Value> getOutputReceiver();

    // Local<Value> getIdentity(); // TODO

    // Local<Value> getOriginType(); // TODO

    // Local<Value> toCommandOriginData(); // TODO

    // Local<Value> getUUID(); // TODO

    Local<Value> handleCommandOutputCallback(const Arguments& args);

    Local<Value> updateValues();

    // Local<Value> getExecutePosition(const Arguments& args);

    Local<Value> isValid();

    Local<Value> requiresValidLevel();

    // Local<Value> _setUUID(const Arguments& args); // TODO

    Local<Value> sUnknownSource();
};

extern ClassDefine<CommandOriginClass> commandOriginClassBuilder;