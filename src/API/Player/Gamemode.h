#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/gamemode/GameMode.h>

class GameModeClass : public ScriptClass {
public:
    GameMode* mGameMode;

public:
    GameModeClass(GameMode* gamemode);

public:
    static Local<Object> newGameMode(GameMode* gamemode);

public: /* Member */
public: /* Method */
};

extern ClassDefine<GameModeClass> gamemodeClassBuilder;