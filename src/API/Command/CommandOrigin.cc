#include "API/Command/CommandOrigin.h"
#include "API/Dimension/Dimension.h"
#include "API/Level/Level.h"
#include "API/Math/Vec3.h"
#include "API/Network/NetworkIdentifier.h"
#include "mc/world/actor/player/AbilitiesIndex.h"



#include <mc/world/level/BlockPos.h>

using namespace Komomo;

ClassDefine<CommandOriginClass> commandOriginClassBuilder =
    defineClass<CommandOriginClass>("CommandOrigin")
        .constructor(nullptr)

        .instanceFunction("getRequestId", &CommandOriginClass::getRequestId)
        .instanceFunction("getName", &CommandOriginClass::getName)
        .instanceFunction("getBlockPosition", &CommandOriginClass::getBlockPosition)
        .instanceFunction("getWorldPosition", &CommandOriginClass::getWorldPosition)
        // .instanceFunction("getRotation", &CommandOriginClass::getRotation)
        .instanceFunction("getLevel", &CommandOriginClass::getLevel)
        .instanceFunction("getDimension", &CommandOriginClass::getDimension)
        .instanceFunction("getEntity", &CommandOriginClass::getEntity)
        .instanceFunction("getPermissionsLevel", &CommandOriginClass::getPermissionsLevel)
        .instanceFunction("hasChatPerms", &CommandOriginClass::hasChatPerms)
        .instanceFunction("hasTellPerms", &CommandOriginClass::hasTellPerms)
        .instanceFunction("canUseAbility", &CommandOriginClass::canUseAbility)
        .instanceFunction("isWorldBuilder", &CommandOriginClass::isWorldBuilder)
        .instanceFunction("canUseCommandsWithoutCheatsEnabled", &CommandOriginClass::canUseCommandsWithoutCheatsEnabled)
        .instanceFunction("isSelectorExpansionAllowed", &CommandOriginClass::isSelectorExpansionAllowed)
        .instanceFunction("handleCommandOutputCallback", &CommandOriginClass::handleCommandOutputCallback)
        // .instanceFunction("updateValues", &CommandOriginClass::updateValues)
        .instanceFunction("isValid", &CommandOriginClass::isValid)
        .instanceFunction("sUnknownSource", &CommandOriginClass::sUnknownSource)

        .build();

CommandOriginClass::CommandOriginClass(CommandOrigin const* commandOrigin)
: ScriptClass(ConstructFromCpp<CommandOriginClass>{}) {
    this->mCommandOrigin = commandOrigin;
}

Local<Object> CommandOriginClass::newCommandOrigin(CommandOrigin const* commandOrigin) {
    return (new CommandOriginClass(commandOrigin))->getScriptObject();
}


Local<Value> CommandOriginClass::getRequestId() {
    if (!mCommandOrigin) return Local<Value>();
    return String::newString(mCommandOrigin->getRequestId());
};

Local<Value> CommandOriginClass::getName() {
    if (!mCommandOrigin) return Local<Value>();
    return String::newString(mCommandOrigin->getName());
};

Local<Value> CommandOriginClass::getBlockPosition() {
    if (!mCommandOrigin) return Local<Value>();
    // return BlockPosClass::newBlockPos(&mCommandOrigin->getBlockPosition()); // TODO


    return Local<Value>();
};

Local<Value> CommandOriginClass::getWorldPosition() {
    if (!mCommandOrigin) return Local<Value>();
    return Vec3Class::newVec3(
        mCommandOrigin->getWorldPosition().x,
        mCommandOrigin->getWorldPosition().y,
        mCommandOrigin->getWorldPosition().z
    );
};

// Local<Value> CommandOriginClass::getRotation();

Local<Value> CommandOriginClass::getLevel() { return LevelClass::newLevel(mCommandOrigin->getLevel()); };

Local<Value> CommandOriginClass::getDimension() {
    return DimensionClass::newDimension(mCommandOrigin->getDimension());
};

Local<Value> CommandOriginClass::getEntity() {
    // return EntityClass::newEntity(mCommandOrigin->getEntity());
    return Local<Value>();
};

Local<Value> CommandOriginClass::getPermissionsLevel() {
    return ConvertToScriptX(mCommandOrigin->getPermissionsLevel());
};

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

Local<Value> CommandOriginClass::hasChatPerms() { return Boolean::newBoolean(mCommandOrigin->hasChatPerms()); };

Local<Value> CommandOriginClass::hasTellPerms() { return Boolean::newBoolean(mCommandOrigin->hasTellPerms()); };

Local<Value> CommandOriginClass::canUseAbility(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);
    return Boolean::newBoolean(mCommandOrigin->canUseAbility(AbilitiesIndex(args[0].asNumber().toInt32())));
};

Local<Value> CommandOriginClass::isWorldBuilder() { return Boolean::newBoolean(mCommandOrigin->isWorldBuilder()); };

Local<Value> CommandOriginClass::canUseCommandsWithoutCheatsEnabled() {
    return Boolean::newBoolean(mCommandOrigin->canUseCommandsWithoutCheatsEnabled());
};

Local<Value> CommandOriginClass::isSelectorExpansionAllowed() {
    return Boolean::newBoolean(mCommandOrigin->isSelectorExpansionAllowed());
};

Local<Value> CommandOriginClass::getSourceId() {
    // return NetworkIdentifierClass::newNetworkIdentifier(mCommandOrigin->getSourceId());
    return Local<Value>();
};

// Local<Value> getSourceSubId(); // TODO

Local<Value> CommandOriginClass::getOutputReceiver() {
    // return CommandOutputClass::newCommandOutput(&mCommandOrigin->getOutputReceiver());
    return Local<Value>();
};

// Local<Value> getIdentity(); // TODO

// Local<Value> getOriginType(); // TODO

// Local<Value> toCommandOriginData(); // TODO

// Local<Value> getUUID(); // TODO

Local<Value> CommandOriginClass::handleCommandOutputCallback(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kString);
    mCommandOrigin->handleCommandOutputCallback(args[0].asNumber().toInt32(), args[1].asString().toString());
    return Local<Value>();
};

// Local<Value> CommandOriginClass::updateValues() {
//     mCommandOrigin->();
//     return Local<Value>();
// };

// Local<Value> CommandOriginClass::getExecutePosition(const Arguments& args) {
//     CheckArgsCount(args, 2);
//     return Vec3Class::newVec3(mCommandOrigin->getExecutePosition());
// };

Local<Value> CommandOriginClass::isValid() { return Boolean::newBoolean(mCommandOrigin->isValid()); };

Local<Value> CommandOriginClass::requiresValidLevel() {
    return Boolean::newBoolean(mCommandOrigin->requiresValidLevel());
};

// Local<Value> _setUUID(const Arguments& args); // TODO

Local<Value> CommandOriginClass::sUnknownSource() {
    return NetworkIdentifierClass::newNetworkIdentifier(&mCommandOrigin->sUnknownSource());
};