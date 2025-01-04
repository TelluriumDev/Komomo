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
#include "API/Form/SimpleForm.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    engine->registerNativeClass<PlayerClass>(PlayerClassBuilder);
    engine->registerNativeClass<EventClass>(EventClassBuilder);
    engine->registerNativeClass<SimpleFormClass>(simpleFormClassBuilder);
}


} // namespace Komomo
