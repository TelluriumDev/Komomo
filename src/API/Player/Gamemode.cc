#include "API/Player/GameMode.h"


ClassDefine<GameModeClass> gamemodeClassBuilder = defineClass<GameModeClass>("GameMode")
                                                        .constructor(nullptr)

                                                        .build();

GameModeClass::GameModeClass(GameMode* gamemode) : ScriptClass(ConstructFromCpp<GameModeClass>{}) {
    this->mGameMode = gamemode;
}

Local<Object> GameModeClass::newGameMode(GameMode* gamemode) {
    return (new GameModeClass(gamemode))->getScriptObject();
}
