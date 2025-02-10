#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/player/PlayerMovementSettings.h>

class PlayerMovementSettingsClass : public ScriptClass {
public:
    PlayerMovementSettings* mPlayerMovementSettings;

public:
    PlayerMovementSettingsClass(PlayerMovementSettings* playerMovementSettings);

public:
    static Local<Object> newPlayerMovementSettings(PlayerMovementSettings* playerMovementSettings);

public: /* Member */
public: /* Method */
};

extern ClassDefine<PlayerMovementSettingsClass> playerMovementSettingsClassBuilder;