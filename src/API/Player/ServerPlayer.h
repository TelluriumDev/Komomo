#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "API/Player/Player.h"

#include <mc/server/ServerPlayer.h>

class ServerPlayerClass : public PlayerClass {
public:
    ServerPlayer* mServerPlayer;

public:
    template <typename T>
    explicit ServerPlayerClass(ServerPlayer* serverPlayer, ScriptClass::ConstructFromCpp<T> tag)
    : PlayerClass(serverPlayer, tag) {
        this->mServerPlayer = serverPlayer;
    };

    explicit ServerPlayerClass(ServerPlayer* serverPlayer)
    : PlayerClass(serverPlayer, ConstructFromCpp<ServerPlayerClass>{}) {
        this->mServerPlayer = serverPlayer;
    };

public:
    static Local<Object> newServerPlayer(ServerPlayer* serverPlayer);
};