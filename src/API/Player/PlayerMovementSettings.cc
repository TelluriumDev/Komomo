#include "API/Player/PlayerMovementSettings.h"


ClassDefine<PlayerMovementSettingsClass> playerMovementSettingsClassBuilder = defineClass<PlayerMovementSettingsClass>("PlayerMovementSettings")
                                                                      .constructor(nullptr)

                                                                      .build();

PlayerMovementSettingsClass::PlayerMovementSettingsClass(PlayerMovementSettings* playerMovementSettings)
: ScriptClass(ConstructFromCpp<PlayerMovementSettingsClass>{}) {
    this->mPlayerMovementSettings = playerMovementSettings;
}

Local<Object> PlayerMovementSettingsClass::newPlayerMovementSettings(PlayerMovementSettings* playerMovementSettings) {
    return (new PlayerMovementSettingsClass(playerMovementSettings))->getScriptObject();
}
