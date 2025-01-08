#pragma once

#include "API/Actor/Actor.h"
#include "API/Container/Container.h"
#include "API/Enum/EnumBuilder.h"
#include "API/Event/Event.h"
#include "API/Event/Listener.h"
#include "API/Form/CustomForm.h"
#include "API/Form/SimpleForm.h"
#include "API/ItemStack/ItemStack.h"
#include "API/Logger/Logger.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    EnumAPI::RegisterEnum(engine);

    engine->registerNativeClass<PlayerClass>(playerClassBuilder);
    engine->registerNativeClass<EventBusClass>(eventBusClassBuilder);
    engine->registerNativeClass<ListenerClass>(listenerClassBuilder);
    engine->registerNativeClass<SimpleFormClass>(simpleFormClassBuilder);
    engine->registerNativeClass<CustomFormClass>(customFormClassBuilder);
    engine->registerNativeClass<ContainerClass>(containerClassBuilder);
    engine->registerNativeClass<ItemStackClass>(itemStackClassBuilder);
    engine->registerNativeClass<ActorClass>(actorClassBuilder);
    engine->registerNativeClass<LoggerClass>(loggerClassBuilder);
}


} // namespace Komomo
