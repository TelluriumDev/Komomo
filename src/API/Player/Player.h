#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/player/Player.h>

class Player;

class PlayerClass : public ScriptClass {
private:
    Player* mPlayer;

public:
    PlayerClass(Player* player);

public:
    static Local<Object> newPlayer(Player* player);

public:
    // Local<const Value> getRealName();
    Local<Value> getXuid();
};

extern ClassDefine<PlayerClass> PlayerClassBuilder;