#pragma once

#include "API/Enum/EnumBuilder.h"
#include "API/Event/Event.h"
#include "API/Form/SimpleForm.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"



namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    EnumAPI::RegisterEnum(engine);

    engine->registerNativeClass<PlayerClass>(PlayerClassBuilder);
    engine->registerNativeClass<EventClass>(EventClassBuilder);
    engine->registerNativeClass<SimpleFormClass>(simpleFormClassBuilder);
}


} // namespace Komomo
