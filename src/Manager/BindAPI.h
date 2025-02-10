#pragma once

#include "API/Actor/Actor.h"
#include "API/Actor/ActorDamageSource.h"
#include "API/Actor/ActorDefinitionIdentifier.h"
#include "API/Actor/ActorInteraction.h"
#include "API/Actor/ActorUniqueID.h"
#include "API/Actor/ItemActor.h"
#include "API/Actor/SculkCatalystBlockActor.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Block/BlockState.h"
#include "API/Block/IConstBlockSource.h"
#include "API/Block/Material.h"
#include "API/Command/Command.h"
#include "API/Command/CommandContext.h"
#include "API/Command/CommandFlag.h"
#include "API/Command/CommandOrigin.h"
#include "API/Command/CommandOutput.h"
#include "API/Command/CommandRegistry.h"
#include "API/Command/MinecraftCommands.h"
#include "API/Command/MCRESULT.h"
#include "API/Container/Container.h"
#include "API/Dimension/AutomaticID.h"
#include "API/Dimension/ChangeDimensionRequest.h"
#include "API/Dimension/Dimension.h"
#include "API/Dimension/DimensionType.h"
#include "API/Entity/EntityContext.h"
#include "API/Enum/EnumBuilder.h"
#include "API/Event/Event.h"
#include "API/Event/Listener.h"
#include "API/Form/CustomForm.h"
#include "API/Form/Form.h"
#include "API/Form/ModalForm.h"
#include "API/Form/SimpleForm.h"
#include "API/Item/Item.h"
#include "API/Item/ItemStack.h"
#include "API/Item/ItemStackBase.h"
#include "API/Item/ItemStackRequestActionTransferBase.h"
#include "API/Level/Level.h"
#include "API/Level/Explosion.h"
#include "API/Logger/Logger.h"
#include "API/Math/AABB.h"
#include "API/Math/HitResult.h"
#include "API/Math/Random.h"
#include "API/Math/UUID.h"
#include "API/Math/Vec.h"
#include "API/Math/Vec2.h"
#include "API/Math/Vec3.h"
#include "API/Mob/Agent.h"
#include "API/Mob/Mob.h"
#include "API/Mob/MobEffectInstance.h"
#include "API/Mod/Mod.h"
#include "API/Network/ConnectionRequest.h"
#include "API/Network/LoopbackPacketSender.h"
#include "API/Network/NetworkIdentifier.h"
#include "API/Network/ServerNetworkHandler.h"
#include "API/Network/Packet/ChangeDimensionPacket.h"
#include "API/Network/Packet/Packet.h"
#include "API/Network/Packet/UpdateEquipPacket.h"
#include "API/Network/Packet/UpdateTradePacket.h"
#include "API/Player/Gamemode.h"
#include "API/Player/LayeredAbilities.h"
#include "API/Player/Player.h"
#include "API/Player/PlayerMovementSettings.h"
#include "API/Player/ServerPlayer.h"
#include "API/Player/SimulatedPlayer.h"
#include "API/Service/Service.h"

#include "ExtraAPI/Config/Config.h"
#include "ExtraAPI/KeyValueDb/KeyValueDB.h"
#include "ExtraAPI/NetWork/WebSocket.h"
#include "Utils/Using.h"


namespace Komomo {

inline void BindAPI(ScriptEngine* engine) {

    EnumAPI::RegisterEnum(engine);

    engine->registerNativeClass<ModClass>(modClassBuilder);

    engine->registerNativeClass<PlayerClass>(playerClassBuilder);
    engine->registerNativeClass<GameModeClass>(gameModeClassBuilder);
    engine->registerNativeClass<LayeredAbilitiesClass>(layeredAbilitiesClassBuilder);
    engine->registerNativeClass<PlayerMovementSettingsClass>(playerMovementSettingsClassBuilder);
    // engine->registerNativeClass<ServerPlayerClass>(serverplayerClassBuilder);
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
    engine->registerNativeClass<ItemStackBaseClass>(itemStackBaseClassBuilder);
    engine->registerNativeClass<ItemStackRequestActionTransferBaseClass>(itemStackRequestActionTransferBaseClassBuilder);

    engine->registerNativeClass<ActorClass>(actorClassBuilder);
    engine->registerNativeClass<ActorDefinitionIdentifierClass>(actorDefinitionIdentifierClassBuilder);
    engine->registerNativeClass<ActorInteractionClass>(actorInteractionClassBuilder);
    engine->registerNativeClass<ActorUniqueIDClass>(actorUniqueIDClassBuilder);
    engine->registerNativeClass<AgentClass>(agentClassBuilder);
    engine->registerNativeClass<ActorDamageSourceClass>(actorDamageSourceClassBuilder);
    engine->registerNativeClass<SculkCatalystBlockActorClass>(sculkCatalystBlockActorClassBuilder);

    engine->registerNativeClass<BlockClass>(blockClassBuilder);
    engine->registerNativeClass<BlockPosClass>(blockPosClassBuilder);
    engine->registerNativeClass<BlockSourceClass>(blockSourceClassBuilder);
    engine->registerNativeClass<BlockStateClass>(blockStateClassBuilder);
    engine->registerNativeClass<IConstBlockSourceClass>(iConstBlockSourceClassBuilder);
    engine->registerNativeClass<MaterialClass>(materialClassBuilder);

    engine->registerNativeClass<CommandClass>(commandClassBuilder);
    engine->registerNativeClass<CommandFlagClass>(commandFlagClassBuilder);
    engine->registerNativeClass<CommandOriginClass>(commandOriginClassBuilder);
    engine->registerNativeClass<CommandOutputClass>(commandOutputClassBuilder);
    engine->registerNativeClass<CommandContextClass>(commandContextClassBuilder);
    engine->registerNativeClass<CommandRegistryClass>(commandRegistryClassBuilder);
    // engine->registerNativeClass<RuntimeOverloadClass>(runtimeOverloadClassBuilder);
    engine->registerNativeClass<MinecraftCommandsClass>(minecraftCommandsClassBuilder);
    engine->registerNativeClass<MCRESULTClass>(MCRESULTClassBuilder);

    //engine->registerNativeClass<AutomaticIDClass>(automaticIDClassBuilder);
    engine->registerNativeClass<ChangeDimensionRequestClass>(changeDimensionRequestClassBuilder);
    engine->registerNativeClass<DimensionClass>(dimensionClassBuilder);
    engine->registerNativeClass<DimensionTypeClass>(dimensionTypeClassBuilder);

    engine->registerNativeClass<EntityContextClass>(entityContextClassBuilder);

    engine->registerNativeClass<LevelClass>(levelClassBuilder);
    engine->registerNativeClass<ExplosionClass>(explosionClassBuilder);

    engine->registerNativeClass<AABBClass>(aabbClassBuilder);
    engine->registerNativeClass<HitResultClass>(hitResultClassBuilder);
    engine->registerNativeClass<RandomClass>(randomClassBuilder);
    engine->registerNativeClass<UUIDClass>(uuidClassBuilder);
    engine->registerNativeClass<VecClass>(vecClassBuilder);
    engine->registerNativeClass<Vec2Class>(vec2ClassBuilder);
    engine->registerNativeClass<Vec3Class>(vec3ClassBuilder);

    engine->registerNativeClass<MobClass>(mobClassBuilder);
    engine->registerNativeClass<MobEffectInstanceClass>(mobEffectInstanceClassBuilder);

    engine->registerNativeClass<ConnectionRequestClass>(connectionRequestClassBuilder);
    engine->registerNativeClass<LoopbackPacketSenderClass>(loopbackPacketSenderClassBuilder);
    engine->registerNativeClass<NetworkIdentifierClass>(networkIdentifierClassBuilder);
    engine->registerNativeClass<ServerNetworkHandlerClass>(serverNetworkHandlerClassBuilder);
    engine->registerNativeClass<ChangeDimensionPacketClass>(changeDimensionPacketClassBuilder);
    engine->registerNativeClass<PacketClass>(packetClassBuilder);
    engine->registerNativeClass<UpdateEquipPacketClass>(updateEquipPacketClassBuilder);
    engine->registerNativeClass<UpdateTradePacketClass>(updateTradePacketClassBuilder);

    engine->registerNativeClass<ServiceClass>(serviceClassBuilder);

    engine->registerNativeClass<LoggerClass>(loggerClassBuilder);

    engine->registerNativeClass<ConfigClass>(configClassBuilder);
    engine->registerNativeClass<KeyValueDBClass>(keyValueDBClassBuilder);
    // engine->registerNativeClass<WebSocketClass>(webSocketClassBuilder);
}


} // namespace Komomo

