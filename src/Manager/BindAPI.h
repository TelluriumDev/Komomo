#pragma once

#include "API/Actor/Actor.h"
#include "API/Actor/ActorDamageSource.h"
#include "API/Actor/ActorDefinitionIdentifier.h"
#include "API/Actor/ActorUniqueID.h"
#include "API/Actor/Agent.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Command/Command.h"
#include "API/Command/CommandContext.h"
#include "API/Command/CommandOrigin.h"
#include "API/Command/CommandOutput.h"
#include "API/Command/MinecraftCommands.h"
#include "API/Container/Container.h"
#include "API/Enum/EnumBuilder.h"
#include "API/Event/Event.h"
#include "API/Event/Listener.h"
#include "API/Form/CustomForm.h"
#include "API/Form/Form.h"
#include "API/Form/ModalForm.h"
#include "API/Form/SimpleForm.h"
#include "API/Item/Item.h"
#include "API/Item/ItemActor.h"
#include "API/Item/ItemStack.h"
#include "API/Level/Level.h"
#include "API/Logger/Logger.h"
#include "API/Math/Vec3.h"
#include "API/Mob/Mob.h"
#include "API/Mod/Mod.h"
#include "API/Player/Gamemode.h"
#include "API/Player/LayeredAbilities.h"
#include "API/Player/Player.h"
#include "API/Player/SimulatedPlayer.h"
#include "API/Service/Service.h"

#include "ExtraAPI/Config/Config.h"
#include "ExtraAPI/KeyValueDb/KeyValueDB.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    EnumAPI::RegisterEnum(engine);

    engine->registerNativeClass<ModClass>(modClassBuilder);

    engine->registerNativeClass<PlayerClass>(playerClassBuilder);
    engine->registerNativeClass<GameModeClass>(gameModeClassBuilder);
    engine->registerNativeClass<LayeredAbilitiesClass>(layeredAbilitiesClassBuilder);
    engine->registerNativeClass<SimulatedPlayerClass>(simulatedPlayerClassBuilder);

    engine->registerNativeClass<EventBusClass>(eventBusClassBuilder);
    engine->registerNativeClass<ListenerClass>(listenerClassBuilder);

    engine->registerNativeClass<FormClass>(formClassBuilder);
    engine->registerNativeClass<SimpleFormClass>(simpleFormClassBuilder);
    engine->registerNativeClass<CustomFormClass>(customFormClassBuilder);
    engine->registerNativeClass<ModalFormClass>(modalFormClassBuilder);

    engine->registerNativeClass<ContainerClass>(containerClassBuilder);

    engine->registerNativeClass<ItemClass>(itemClassBuilder);
    engine->registerNativeClass<ItemStackClass>(itemStackClassBuilder);
    engine->registerNativeClass<ItemActorClass>(itemActorClassBuilder);

    engine->registerNativeClass<ActorClass>(actorClassBuilder);
    engine->registerNativeClass<ActorDefinitionIdentifierClass>(actorDefinitionIdentifierClassBuilder);
    engine->registerNativeClass<ActorUniqueIDClass>(actorUniqueIDClassBuilder);
    engine->registerNativeClass<AgentClass>(agentClassBuilder);
    engine->registerNativeClass<ActorDamageSourceClass>(actorDamageSourceClassBuilder);

    engine->registerNativeClass<BlockClass>(blockClassBuilder);
    engine->registerNativeClass<BlockPosClass>(blockPosClassBuilder);
    engine->registerNativeClass<BlockSourceClass>(blockSourceClassBuilder);

    engine->registerNativeClass<CommandClass>(commandClassBuilder);
    engine->registerNativeClass<CommandOriginClass>(commandOriginClassBuilder);
    engine->registerNativeClass<CommandOutputClass>(commandOutputClassBuilder);
    engine->registerNativeClass<CommandContextClass>(commandContextClassBuilder);
    // engine->registerNativeClass<RuntimeOverloadClass>(runtimeOverloadClassBuilder);
    engine->registerNativeClass<MinecraftCommandsClass>(minecraftCommandsClassBuilder);

    engine->registerNativeClass<LevelClass>(levelClassBuilder);

    engine->registerNativeClass<Vec3Class>(vec3ClassBuilder);

    engine->registerNativeClass<MobClass>(mobClassBuilder);

    engine->registerNativeClass<ServiceClass>(serviceClassBuilder);

    engine->registerNativeClass<LoggerClass>(loggerClassBuilder);

    engine->registerNativeClass<ConfigClass>(configClassBuilder);
    engine->registerNativeClass<KeyValueDBClass>(keyValueDBClassBuilder);
}


} // namespace Komomo
