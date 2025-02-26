#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/gamemode/GameMode.h>

class GameModeClass : public ScriptClass {
public:
    GameMode* mGameMode;

public:
    GameModeClass(GameMode* gameMode);

public:
    static Local<Object> newGameMode(GameMode* gameMode);

  

public: /* Member */
public: /* Method */
};

extern ClassDefine<GameModeClass> gameModeClassBuilder;

