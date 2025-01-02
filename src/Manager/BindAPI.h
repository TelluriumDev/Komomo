#pragma once
// #include "API/CommandSenderAPI.h"
// #include "API/EnumAPI.h"
// #include "API/JSEAPI.h"
// #include "API/LoggerAPI.h"
// #include "API/FileAPI.h"
// #include "API/PermissibleAPI.h"
// #include "API/PluginAPI.h"
// #include "API/PluginDescriptionAPI.h"
#include "API/Event/Event.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    //     // enum class
    //     EnumAPI::RegisterEnum(engine);
    //
    //     // static class
    //     engine->registerNativeClass(JSEAPI::builder);
    //
    //     // instance class
    engine->registerNativeClass<PlayerClass>(PlayerClassBuilder);
    engine->registerNativeClass<EventClass>(EventClassBuilder);
    //     engine->registerNativeClass<LoggerAPI>(LoggerAPI::builder);
    //     engine->registerNativeClass<PluginDescriptionAPI>(PluginDescriptionAPI::builder);
    //     engine->registerNativeClass<PermissibleAPI>(PermissibleAPI::builder);
    //     engine->registerNativeClass<CommandSenderAPI>(CommandSenderAPI::builder);
}


} // namespace Komomo
