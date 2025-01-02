#include "API/Player/Player.h"
#include "API/APIHelper.h"
#include "Entry.h"

#include <ll/api/service/PlayerInfo.h>

using namespace Komomo;

ClassDefine<PlayerClass> PlayerClassBuilder = defineClass<PlayerClass>("Player")
                                                  .constructor(nullptr)

                                                  .instanceFunction("getXuid", &PlayerClass::getXuid)

                                                  .build();


PlayerClass::PlayerClass(Player* player) : ScriptClass(ConstructFromCpp<PlayerClass>{}) { this->mPlayer = player; };

Local<Object> PlayerClass::newPlayer(Player* player) { return (new PlayerClass(player))->getScriptObject(); }

// Local<const Value> PlayerClass::getRealName() {
//     return
// }

Local<Value> PlayerClass::getXuid() {
    try {
        if (!mPlayer) return Local<Value>();
        std::string xuid;
        try {
            xuid = mPlayer->getXuid();
        } catch (...) {
            Komomo::getSelfModInstance().getLogger().debug("Fail in getXuid!");
            xuid = ll::service::PlayerInfo::getInstance().fromName(mPlayer->getRealName())->xuid;
        }
        return String::newString(xuid);
    }
    Catch;
}