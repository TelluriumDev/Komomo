#pragma once

#include "API/Actor/Actor.h"
#include "API/Container/Container.h"
#include "API/Enum/EnumBuilder.h"
#include "API/Event/Event.h"
#include "API/Form/CustomForm.h"
#include "API/Form/SimpleForm.h"
#include "API/ItemStack/ItemStack.h"
#include "API/Player/Player.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    EnumAPI::RegisterEnum(engine);

    engine->registerNativeClass<PlayerClass>(playerClassBuilder);
    engine->registerNativeClass<EventClass>(eventClassBuilder);
    engine->registerNativeClass<SimpleFormClass>(simpleFormClassBuilder);
    engine->registerNativeClass<CustomFormClass>(customFormClassBuilder);
    engine->registerNativeClass<ContainerClass>(containerClassBuilder);
    engine->registerNativeClass<ItemStackClass>(itemStackClassBuilder);
    engine->registerNativeClass<ActorClass>(actorClassBuilder);
}


} // namespace Komomo
