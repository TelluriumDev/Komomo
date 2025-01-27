#include "API/Player/ServerPlayer.h"


ClassDefine<ServerPlayerClass> serverplayerClassBuilder =
    defineClass<ServerPlayerClass>("ServerPlayer").constructor(nullptr).build();


Local<Object> ServerPlayerClass::newServerPlayer(ServerPlayer* serverplayer) {
    return (new ServerPlayerClass(serverplayer))->getScriptObject();
}