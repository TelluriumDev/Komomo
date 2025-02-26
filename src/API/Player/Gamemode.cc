#include "API/Player/GameMode.h"


ClassDefine<GameModeClass> gameModeClassBuilder = defineClass<GameModeClass>("GameMode")
                                                      .constructor(nullptr)

                                                      .build();

GameModeClass::GameModeClass(GameMode* gameMode) : ScriptClass(ConstructFromCpp<GameModeClass>{}) {
    this->mGameMode = gameMode;
}

Local<Object> GameModeClass::newGameMode(GameMode* gameMode) {
    return (new GameModeClass(gameMode))->getScriptObject();
}
