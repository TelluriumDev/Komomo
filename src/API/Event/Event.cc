#include "API/APIHelper.h"
#include "API/Actor/Actor.h"
#include "API/Actor/ActorDamageSource.h"
#include "API/Actor/ActorDefinitionIdentifier.h"
#include "API/Actor/SculkCatalystBlockActor.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Command/CommandContext.h"
#include "API/Command/CommandFlag.h"
#include "API/Command/MCRESULT.h"
#include "API/Command/MinecraftCommands.h"

// TODO: ila not implemented
// #include "API/Command/CommandRegistry.h"
#include "API/Actor/ItemActor.h"
#include "API/Dimension/ChangeDimensionRequest.h"
#include "API/Dimension/Dimension.h"
#include "API/Dimension/DimensionType.h"
#include "API/Event/Event.h"
#include "API/Event/Listener.h"
#include "API/Item/ItemStack.h"
#include "API/Item/ItemStackRequestActionTransferBase.h"
#include "API/Level/Explosion.h"
#include "API/Level/Level.h"
#include "API/Math/AABB.h"
#include "API/Math/Random.h"
#include "API/Math/UUID.h"
#include "API/Math/Vec3.h"
#include "API/Mob/Mob.h"
#include "API/Network/ConnectionRequest.h"
#include "API/Network/LoopbackPacketSender.h"
#include "API/Network/NetworkIdentifier.h"
#include "API/Network/Packet/Packet.h"
#include "API/Network/ServerNetworkHandler.h"
#include "API/Player/Player.h"
#include "API/Service/Service.h"


#include <ll/api/event/ListenerBase.h>

#include <ll/api/event/server/ServerStartedEvent.h>
#include <ll/api/event/server/ServerStoppingEvent.h>

#include <ll/api/event/player/PlayerAddExperienceEvent.h>
#include <ll/api/event/player/PlayerAttackEvent.h>
#include <ll/api/event/player/PlayerChangePermEvent.h>
#include <ll/api/event/player/PlayerChatEvent.h>
#include <ll/api/event/player/PlayerConnectEvent.h>
#include <ll/api/event/player/PlayerDestroyBlockEvent.h>
#include <ll/api/event/player/PlayerDieEvent.h>
#include <ll/api/event/player/PlayerDisconnectEvent.h>
#include <ll/api/event/player/PlayerInteractBlockEvent.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerJumpEvent.h>
#include <ll/api/event/player/PlayerPickUpItemEvent.h>
#include <ll/api/event/player/PlayerPlaceBlockEvent.h>
#include <ll/api/event/player/PlayerRespawnEvent.h>
#include <ll/api/event/player/PlayerSneakEvent.h>
#include <ll/api/event/player/PlayerSprintEvent.h>
#include <ll/api/event/player/PlayerSwingEvent.h>
#include <ll/api/event/player/PlayerUseItemEvent.h>

#include <ll/api/event/world/BlockChangedEvent.h>
#include <ll/api/event/world/FireSpreadEvent.h>
#include <ll/api/event/world/LevelTickEvent.h>
#include <ll/api/event/world/SpawnMobEvent.h>

#include <ll/api/event/entity/ActorHurtEvent.h>
#include <ll/api/event/entity/MobDieEvent.h>

#include <ll/api/event/command/ExecuteCommandEvent.h>

#include <ll/api/event/service/ServiceEvents.h>

#include <ll/api/utils/HashUtils.h>

// LegacyMoney is deprecated, so we don't include it
// #include "ila/event/legacyMoney/MoneyChangeEvent.h"
// #include "ila/event/minecraft/actor/ActorChangeDimensionEvent.h"
// #include "ila/event/minecraft/actor/ActorGetEffectEvent.h"
// #include "ila/event/minecraft/actor/ActorPickupItemEvent.h"
// #include "ila/event/minecraft/actor/ActorRideEvent.h"
// #include "ila/event/minecraft/actor/ActorTickEvent.h"
// #include "ila/event/minecraft/actor/ActorTriggerPressurePlateEvent.h"
// #include "ila/event/minecraft/actor/ArmorStandSwapItemEvent.h"
// #include "ila/event/minecraft/actor/DeathMessageEvent.h"
// #include "ila/event/minecraft/actor/DragonRespawnEvent.h"
// #include "ila/event/minecraft/actor/MobHurtEffectEvent.h"
// #include "ila/event/minecraft/actor/ProjectileCreateEvent.h"
//
// #include "ila/event/minecraft/level/LevelTickEvent.h"
// #include "ila/event/minecraft/level/SculkCatalystAbsorbExperienceEvent.h"
// #include "ila/event/minecraft/level/WeatherUpdateEvent.h"
//
// #include "ila/event/minecraft/player/PlayerAttackBlockEvent.h"
// // Warning: maybe typo? (PlayerChangGameTypeEvent -> PlayerChangeGameTypeEvent)
// //                      (PlayerChangPermissionsEvent -> PlayerChangePermissionsEvent)
// #include "ila/event/minecraft/player/PlayerChangGameTypeEvent.h"
// #include "ila/event/minecraft/player/PlayerChangPermissionsEvent.h"
// #include "ila/event/minecraft/player/PlayerChangeDimensionEvent.h"
// #include "ila/event/minecraft/player/PlayerDropItemEvent.h"
// // Seems have problems, so we don't include it
// // #include "ila/event/minecraft/player/PlayerEditSignEvent.h"
// #include "ila/event/minecraft/player/PlayerInteractEntityEvent.h"
// #include "ila/event/minecraft/player/PlayerOpenContainerEvent.h"
// #include "ila/event/minecraft/player/PlayerOperatedItemFrameEvent.h"
// #include "ila/event/minecraft/player/PlayerRequestItemActionEvent.h"

#include "ila/event/minecraft/server/ClientLoginEvent.h"
#include "ila/event/minecraft/server/RegisterCmdEvent.h"
#include "ila/event/minecraft/server/SendPacketEvent.h"
#include "ila/event/minecraft/server/ServerPongEvent.h"

// #include "ila/event/minecraft/world/BlockTickEvent.h"
// #include "ila/event/minecraft/world/DragonEggBlockTeleportEvent.h"
#include "ila/event/minecraft/world/ExplosionEvent.h"
// #include "ila/event/minecraft/world/FarmDecayEvent.h"
// #include "ila/event/minecraft/world/LiquidTryFlowEvent.h"
// #include "ila/event/minecraft/world/MossGrowthEvent.h"
#include "ila/event/minecraft/world/PistonPushEvent.h"
#include "ila/event/minecraft/world/RedstoneUpdateEvent.h"
#include "ila/event/minecraft/world/SculkBlockGrowthEvent.h"
// #include "ila/event/minecraft/world/SculkSpreadEvent.h"
#include "ila/event/minecraft/world/SpawnItemActorEvent.h"
#include "ila/event/minecraft/world/SpawnWanderingTraderEvent.h"
#include "ila/event/minecraft/world/WitherDestroyEvent.h"

#include <string>

ClassDefine<EventBusClass> eventBusClassBuilder =
        defineClass<EventBusClass>("EventBus")
        .constructor(nullptr)

        .function("emplaceListener", &EventBusClass::emplaceListener)
        .function("removeListener", &EventBusClass::removeListener)
        .function("removeMyModListener", &EventBusClass::removeMyModListener)


        .build();

std::unordered_map<
    std::string,
    std::function<ll::event::ListenerPtr(const Arguments &, ScriptEngine *, ll::event::EventPriority)> >
EventBusClass::callBackMap = {};

std::unordered_map<std::string, std::vector<ll::event::ListenerPtr> > listeners;


EventBusClass::EventBusClass() : ScriptClass(ConstructFromCpp<EventBusClass>{}) {
};


Local<Value> EventBusClass::emplaceListener(const Arguments &args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kFunction, Boolean::newBoolean(false));

    using ll::event::EventBus;
    using ll::hash_utils::doHash;

    try {
        std::string eventName = args[0].asString().toString();
        auto priority = ll::event::EventPriority::Normal;
        // ll::event::ListenerPtr listener  = nullptr;
        if (args.size() >= 3) {
            CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
            priority = ll::event::EventPriority(args[2].asNumber().toInt32());
        }
        if (callBackMap.empty()) registerCallback();
        auto it = callBackMap.find(eventName);
        if (it != callBackMap.end()) {
            auto listener = it->second(args, EngineScope::currentEngine(), priority);
            listeners[ENGINE_DATA()->mMod->getName()].push_back(listener);
            return ListenerClass::newListenPtr(listener);
        } else {
            PrintException(
                fmt::format("Event :{} not found", eventName),
                "EventBusClass::emplaceListener",
                ENGINE_DATA()->mMod->getName(),
                "emplaceListener"
            );
            return Object::newObject();
        }
    }
    Catch;
}

Local<Value> EventBusClass::removeListener(const Arguments &args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    using ll::event::EventBus;
    try {
        if (IsInstanceOf<ListenerClass>(args[0])) {
            auto engine = EngineScope::currentEngine();
            auto listenerClass = engine->getNativeInstance<ListenerClass>(args[0]);
            if (listenerClass) {
                return Boolean::newBoolean(EventBus::getInstance().removeListener(listenerClass->listener));
            }
            return Boolean::newBoolean(false);
        } else {
            return Boolean::newBoolean(false);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
}

void EventBusClass::removeModAllListeners(std::string modName) {
    using ll::event::EventBus;
    for (auto &listener: listeners[modName]) {
        EventBus::getInstance().removeListener(listener);
    }
    listeners.erase(modName);
}

Local<Value> EventBusClass::removeMyModListener() {
    using ll::event::EventBus;
    auto modName = ENGINE_DATA()->mMod->getName();
    for (auto &listener: listeners[modName]) {
        EventBus::getInstance().removeListener(listener);
    }
    listeners.erase(modName);
    return Local<Value>();
}

void EventBusClass::removeAllListeners() {
    using ll::event::EventBus;
    for (auto &listener: listeners) {
        for (auto &l: listener.second) {
            EventBus::getInstance().removeListener(l);
        }
    }
    listeners.clear();
}

KMMAPI void EventBusClass::addCallback(
    std::string event,
    std::function<ll::event::ListenerPtr(const Arguments &, ScriptEngine *, ll::event::EventPriority)> callBack
) {
    callBackMap.emplace(event, callBack);
}

void EventBusClass::registerCallback() {
    using ll::event::EventBus;
    try {
        addCallback(
            "ServerStartedEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServerStartedEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ServerStartedEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({});
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "ServerStoppingEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServerStoppingEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ServerStoppingEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({});
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerAddExperienceEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerAddExperienceEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerAddExperienceEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                Number::newNumber(event.experience())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerAttackEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerAttackEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerAttackEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ActorClass::newActor(&event.target()),
                                ConvertToScriptX(event.cause())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerChangePermEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerChangePermEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerChangePermEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ConvertToScriptX(event.newPerm())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerChatEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerChatEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerChatEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                String::newString(event.message())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerConnectEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerConnectEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerConnectEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                NetworkIdentifierClass::newNetworkIdentifier(
                                    const_cast<NetworkIdentifier *>(&event.networkIdentifier())
                                ),
                                ConnectionRequestClass::newConnectionRequest(
                                    const_cast<ConnectionRequest *>(&event.connectionRequest())
                                ),
                                PlayerClass::newPlayer(&event.self())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerDestroyBlockEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDestroyBlockEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDestroyBlockEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPosClass(event.pos())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerDieEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDieEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDieEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ActorDamageSourceClass::newActorDamageSource(
                                    const_cast<ActorDamageSource *>(&event.source())
                                )
                            );
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerDisconnectEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDisconnectEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDisconnectEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerInteractBlockEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerInteractBlockEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerInteractBlockEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ItemStackClass::newItemStack(&event.item()),
                                BlockPosClass::newBlockPosClass(event.blockPos()),
                                ConvertToScriptX(event.face()),
                                Vec3Class::newVec3Class(event.clickPos()),
                                BlockClass::newBlock(const_cast<Block *>(&event.block().get()))
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerJoinEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerJoinEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerJoinEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call({}, PlayerClass::newPlayer(&event.self()));
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerJumpEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerJumpEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerJumpEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerPickUpItemEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPickUpItemEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPickUpItemEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ItemActorClass::newItemActor(&event.itemActor()),
                                Number::newNumber(event.orgCount()),
                                Number::newNumber(event.favoredSlot())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerPlacingBlockEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPlacingBlockEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPlacingBlockEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPosClass(event.pos()),
                                ConvertToScriptX(event.face())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerPlacedBlockEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPlacedBlockEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPlacedBlockEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto pos = event.pos();
                            func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPosClass(pos),
                                BlockClass::newBlock(const_cast<Block *>(&event.placedBlock()))
                            );
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerRespawnEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerRespawnEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerRespawnEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerSneakingEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSneakingEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSneakingEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerSneakedEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSneakedEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSneakedEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerSprintingEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSprintingEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSprintingEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerSprintedEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSprintedEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSprintedEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerSwingEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSwingEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSwingEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, PlayerClass::newPlayer(&event.self()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "PlayerUseItemEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerUseItemEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::PlayerUseItemEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ItemStackClass::newItemStack(&event.item())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "BlockChangedEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::BlockChangedEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::BlockChangedEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource *>(&event.blockSource())),
                                Number::newNumber(event.layer()),
                                BlockClass::newBlock(const_cast<Block *>(&event.previousBlock())),
                                BlockClass::newBlock(const_cast<Block *>(&event.newBlock())),
                                BlockPosClass::newBlockPosClass(event.pos())
                            );
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "FireSpreadEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::FireSpreadEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::FireSpreadEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource *>(&event.blockSource())),
                                BlockPosClass::newBlockPosClass(event.pos())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "LevelTickEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::LevelTickEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::LevelTickEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, LevelClass::newLevel(const_cast<Level *>(&event.level())));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "SpawningMobEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::SpawningMobEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::SpawningMobEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource *>(&event.blockSource())),
                                ActorDefinitionIdentifierClass::newActorDefinitionIdentifier(
                                    const_cast<ActorDefinitionIdentifier *>(&event.identifier())
                                ),
                                ActorClass::newActor(&event.spawner().value()),
                                Vec3Class::newVec3Class(event.pos()),
                                Boolean::newBoolean(event.naturalSpawn()),
                                Boolean::newBoolean(event.surface()),
                                Boolean::newBoolean(event.fromSpawner())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "SpawnedMobEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::SpawnedMobEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::SpawnedMobEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                MobClass::newMobClass(&event.mob().value()),
                                BlockSourceClass::newBlockSource(const_cast<BlockSource *>(&event.blockSource())),
                                ActorDefinitionIdentifierClass::newActorDefinitionIdentifier(
                                    const_cast<ActorDefinitionIdentifier *>(&event.identifier())
                                ),
                                ActorClass::newActor(&event.spawner().value()),
                                Vec3Class::newVec3Class(event.pos()),
                                Boolean::newBoolean(event.naturalSpawn()),
                                Boolean::newBoolean(event.surface()),
                                Boolean::newBoolean(event.fromSpawner())
                            );
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "ActorHurtEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ActorHurtEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ActorHurtEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                ActorClass::newActor(&event.self()),
                                ActorDamageSourceClass::newActorDamageSource(
                                    const_cast<ActorDamageSource *>(&event.source())
                                ),
                                Number::newNumber(event.damage()),
                                Boolean::newBoolean(event.knock()),
                                Boolean::newBoolean(event.ignite())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback("MobDieEvent", [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
            return EventBus::getInstance().emplaceListener<ll::event::MobDieEvent>(
                [&args,
                    engine{EngineScope::currentEngine()},
                    func{Global<Function>(args[1].asFunction())}](ll::event::MobDieEvent &event) {
                    EngineScope scope(engine);
                    try {
                        func.get().call(
                            {},
                            MobClass::newMobClass(&event.self()),
                            ActorDamageSourceClass::newActorDamageSource(
                                const_cast<ActorDamageSource *>(&event.source())
                            )
                        );
                    }
                    CatchNotReturn;
                },
                priority
            );
        });
        addCallback(
            "ExecutingCommandEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ExecutingCommandEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ExecutingCommandEvent &event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                MinecraftCommandsClass::newMinecraftCommands(&event.minecraftCommands()),
                                CommandContextClass::newCommandContext(&event.commandContext()),
                                Boolean::newBoolean(event.suppressOutput())
                            );
                            if (result.isBoolean()) {
                                if (result.asBoolean().value() == false) event.cancel();
                            }
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "ExecutedCommandEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ExecutedCommandEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ExecutedCommandEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                MCRESULTClass::newMCRESULT(&event.result()),
                                MinecraftCommandsClass::newMinecraftCommands(&event.minecraftCommands()),
                                CommandContextClass::newCommandContext(
                                    const_cast<CommandContext *>(&event.commandContext())
                                ),
                                Boolean::newBoolean(event.suppressOutput())

                            );
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "ServiceRegisterEvent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServiceRegisterEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ServiceRegisterEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, ServiceClass::newService(event.service().get()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "ServiceUnregisterevent",
            [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServiceUnregisterEvent>(
                    [&args,
                        engine{EngineScope::currentEngine()},
                        func{Global<Function>(args[1].asFunction())}](ll::event::ServiceUnregisterEvent &event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, ServiceClass::newService(event.service().get()));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );

        // Extra Events
        // FUCK YOU Xianyubb

        // ActorChangeDimensionAfterEvent: {
        //   [Cancelable] ActorChangeDimensionBeforeEvent,
        //   ActorChangeDimensionAfterEvent
        // }
        // addCallback(
        //     "ActorChangeDimensionBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorChangeDimensionBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorChangeDimensionBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         DimensionTypeClass::newDimensionType(
        //                             const_cast<DimensionType*>(&event.getFromDimensionId())
        //                         ),
        //                         DimensionTypeClass::newDimensionType(
        //                             const_cast<DimensionType*>(&event.getToDimensionId())
        //                         )
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorChangeDimensionAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorChangeDimensionAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorChangeDimensionAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         DimensionTypeClass::newDimensionType(
        //                             const_cast<DimensionType*>(&event.getFromDimensionId())
        //                         ),
        //                         Vec3Class::newVec3Class(event.getFromPos()),
        //                         DimensionTypeClass::newDimensionType(
        //                             const_cast<DimensionType*>(&event.getToDimensionId())
        //                         )
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ActorGetEffectEvent: {
        // //   [Cancelable] ActorGetEffectBeforeEvent,
        // //   ActorGetEffectAfterEvent
        // // }
        // addCallback(
        //     "ActorGetEffectBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorGetEffectBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorGetEffectBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self())
        //
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorGetEffectAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorGetEffectAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorGetEffectAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call({}, ActorClass::newActor(&event.self()));
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ActorPickupItemEvent: {
        // //   [Cancelable] ActorPickupItemBeforeEvent,
        // //   ActorPickupItemAfterEvent
        // // }
        // addCallback(
        //     "ActorPickupItemBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorPickupItemBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorPickupItemBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         MobClass::newMobClass(&event.self()),
        //                         ItemActorClass::newItemActor(&event.getItemActor())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (!result.asBoolean().value()) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorPickupItemAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorPickupItemAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorPickupItemAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         MobClass::newMobClass(&event.self()),
        //                         ItemActorClass::newItemActor(const_cast<ItemActor*>(&event.getItemActor()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ActorRideEvent: {
        // //   [Cancelable] ActorRideBeforeEvent,
        // //   ActorRideAfterEvent
        // // }
        // addCallback(
        //     "ActorRideBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorRideBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorRideBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         ActorClass::newActor(&event.getTarget())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorRideAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorRideAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorRideAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         ActorClass::newActor(const_cast<Actor*>(&event.getTarget()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ActorTickEvent: {
        // //   [Cancelable] ActorTickBeforeEvent,
        // //   ActorTickAfterEvent
        // // }
        // addCallback(
        //     "ActorTickBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorTickBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorTickBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call({}, ActorClass::newActor(&event.self()));
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorTickAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorTickAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ActorTickAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call({}, ActorClass::newActor(&event.self()));
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ActorTriggerPressurePlateEvent: {
        // //   [Cancelable] ActorTriggerPressurePlateBeforeEvent,
        // //   ActorTriggerPressurePlateAfterEvent
        // // }
        // addCallback(
        //     "ActorTriggerPressurePlateBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorTriggerPressurePlateBeforeEvent>(
        //             [&args, engine{EngineScope::currentEngine()}, func{Global<Function>(args[1].asFunction())}](
        //                 ila::mc::ActorTriggerPressurePlateBeforeEvent& event
        //             ) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getPos())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ActorTriggerPressurePlateAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ActorTriggerPressurePlateAfterEvent>(
        //             [&args, engine{EngineScope::currentEngine()}, func{Global<Function>(args[1].asFunction())}](
        //                 ila::mc::ActorTriggerPressurePlateAfterEvent& event
        //             ) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getPos())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ArmorStandSwapItemEvent: {
        // //   [Cancelable] ArmorStandSwapItemBeforeEvent,
        // //   ArmorStandSwapItemAfterEvent
        // // }
        // addCallback(
        //     "ArmorStandSwapItemBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ArmorStandSwapItemBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ArmorStandSwapItemBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         PlayerClass::newPlayer(&event.getPlayer()),
        //                         ConvertToScriptX(event.getSlot())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ArmorStandSwapItemAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ArmorStandSwapItemAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ArmorStandSwapItemAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         PlayerClass::newPlayer(const_cast<Player*>(&event.getPlayer())),
        //                         ConvertToScriptX(event.getSlot())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // DeathMessageEvent: {
        // //   [Cancelable] DeathMessageBeforeEvent,
        // //   DeathMessageAfterEvent
        // // }
        // addCallback(
        //     "DeathMessageBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::DeathMessageBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::DeathMessageBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto resArray = Array::newArray();
        //
        //                     for (auto a : event.getResult().second) {
        //                         resArray.add(String::newString(a));
        //                     }
        //
        //                     auto resObject = Object::newObject({});
        //                     resObject.set(String::newString(event.getResult().first), resArray);
        //                     auto result = func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         ActorDamageSourceClass::newActorDamageSource(
        //                             const_cast<ActorDamageSource*>(&event.getDamageSource())
        //                         ),
        //                         resObject
        //                     );
        //
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "DeathMessageAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::DeathMessageAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::DeathMessageAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto resArray = Array::newArray();
        //
        //                     for (auto a : event.getResult().second) {
        //                         resArray.add(String::newString(a));
        //                     }
        //
        //                     auto resObject = Object::newObject({});
        //                     resObject.set(String::newString(event.getResult().first), resArray);
        //                     func.get().call(
        //                         {},
        //                         ActorClass::newActor(&event.self()),
        //                         ActorDamageSourceClass::newActorDamageSource(
        //                             const_cast<ActorDamageSource*>(&event.getDamageSource())
        //                         ),
        //                         resObject
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // DragonRespawnEvent: {
        // //   [Cancelable] DragonRespawnBeforeEvent,
        // //   DragonRespawnAfterEvent
        // // }
        // addCallback(
        //     "DragonRespawnBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::DragonRespawnBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::DragonRespawnBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call({});
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "DragonRespawnAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::DragonRespawnAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::DragonRespawnAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call({});
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // MobHurtEffectEvent: {
        // //   [Cancelable] MobHurtEffectBeforeEvent,
        // //   MobHurtEffectAfterEvent
        // // }
        // addCallback(
        //     "MobHurtEffectBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::MobHurtEffectBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::MobHurtEffectBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         MobClass::newMobClass(&event.self()),
        //                         ActorClass::newActor(&event.getSource().get()),
        //                         Number::newNumber(event.getValue()),
        //                         ConvertToScriptX(event.getCause())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "MobHurtEffectAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::MobHurtEffectAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::MobHurtEffectAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         MobClass::newMobClass(&event.self()),
        //                         ActorClass::newActor(const_cast<Actor*>(&event.getSource().get())),
        //                         Number::newNumber(event.getValue()),
        //                         ConvertToScriptX(event.getCause())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // ProjectileCreateEvent: {
        // //   [Cancelable] ProjectileCreateBeforeEvent,
        // //   ProjectileCreateAfterEvent
        // // }
        // addCallback(
        //     "ProjectileCreateBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ProjectileCreateBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ProjectileCreateBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call({}, ActorClass::newActor(&event.self()));
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "ProjectileCreateAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::ProjectileCreateAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::ProjectileCreateAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call({}, ActorClass::newActor(&event.self()));
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // LevelTickEvent: {
        // //   [Cancelable] LevelTickBeforeEvent,
        // //   LevelTickAfterEvent
        // // }
        // addCallback(
        //     "LevelTickBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::LevelTickBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::LevelTickBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call({}, LevelClass::newLevel(&event.level()));
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "LevelTickAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::LevelTickAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::LevelTickAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call({}, LevelClass::newLevel(&event.level()));
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // SculkCatalystAbsorbExperienceEvent: {
        // //   [Cancelable] SculkCatalystAbsorbExperienceBeforeEvent,
        // //   SculkCatalystAbsorbExperienceAfterEvent
        // // }
        // addCallback(
        //     "SculkCatalystAbsorbExperienceBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::SculkCatalystAbsorbExperienceBeforeEvent>(
        //             [&args, engine{EngineScope::currentEngine()}, func{Global<Function>(args[1].asFunction())}](
        //                 ila::mc::SculkCatalystAbsorbExperienceBeforeEvent& event
        //             ) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         LevelClass::newLevel(&event.level()),
        //                         SculkCatalystBlockActorClass::newSculkCatalystBlockActor(&event.getBlockActor()),
        //                         ActorClass::newActor(&event.getActor())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "SculkCatalystAbsorbExperienceAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::SculkCatalystAbsorbExperienceAfterEvent>(
        //             [&args, engine{EngineScope::currentEngine()}, func{Global<Function>(args[1].asFunction())}](
        //                 ila::mc::SculkCatalystAbsorbExperienceAfterEvent& event
        //             ) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         LevelClass::newLevel(&event.level()),
        //                         SculkCatalystBlockActorClass::newSculkCatalystBlockActor(
        //                             const_cast<SculkCatalystBlockActor*>(&event.getBlockActor())
        //                         ),
        //                         ActorClass::newActor(const_cast<Actor*>(&event.getActor()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // WeatherUpdateEvent: {
        // //   [Cancelable] WeatherUpdateBeforeEvent,
        // //   WeatherUpdateAfterEvent
        // // }
        // addCallback(
        //     "WeatherUpdateBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::WeatherUpdateBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::WeatherUpdateBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         LevelClass::newLevel(&event.level()),
        //                         Number::newNumber(event.getRainLevel()),
        //                         Number::newNumber(event.getRainTime()),
        //                         Number::newNumber(event.getLightningLevel()),
        //                         Number::newNumber(event.getLightningTime())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "WeatherUpdateAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::WeatherUpdateAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::WeatherUpdateAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         LevelClass::newLevel(&event.level()),
        //                         Number::newNumber(event.getRainLevel()),
        //                         Number::newNumber(event.getRainTime()),
        //                         Number::newNumber(event.getLightningLevel()),
        //                         Number::newNumber(event.getLightningTime())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerAttackBlockEvent: {
        // //   [Cancelable] PlayerAttackBlockBeforeEvent,
        // //   PlayerAttackBlockAfterEvent
        // // }
        // addCallback(
        //     "PlayerAttackBlockBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerAttackBlockBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerAttackBlockBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getPos())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerAttackBlockAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerAttackBlockAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerAttackBlockAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getPos())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerChangGameTypeEvent: {
        // //   [Cancelable] PlayerChangGameTypeBeforeEvent,
        // //   PlayerChangGameTypeAfterEvent
        // // }
        // addCallback(
        //     "PlayerChangGameTypeBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangGameTypeBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangGameTypeBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ConvertToScriptX(event.getOldGameType()),
        //                         ConvertToScriptX(event.getNewGameType())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerChangGameTypeAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangGameTypeAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangGameTypeAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ConvertToScriptX(event.getOldGameType()),
        //                         ConvertToScriptX(event.getNewGameType())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerChangPermissionsEvent: {
        // //   [Cancelable] PlayerChangPermissionsBeforeEvent,
        // //   PlayerChangPermissionsAfterEvent
        // // }
        // addCallback(
        //     "PlayerChangPermissionsBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangPermissionsBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangPermissionsBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ConvertToScriptX(event.getOldPermissions()),
        //                         ConvertToScriptX(event.getNewPermissions())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerChangPermissionsAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangPermissionsAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangPermissionsAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ConvertToScriptX(event.getOldPermissions()),
        //                         ConvertToScriptX(event.getNewPermissions())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerChangeDimensionEvent: {
        // //   PlayerChangeDimensionBeforeEvent,
        // //   PlayerChangeDimensionAfterEvent
        // // }
        // addCallback(
        //     "PlayerChangeDimensionBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangeDimensionBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangeDimensionBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ChangeDimensionRequestClass::newChangeDimensionRequest(
        //                             const_cast<ChangeDimensionRequest*>(&event.getChangeDimensionRequest())
        //                         ),
        //                         DimensionClass::newDimension(const_cast<Dimension*>(&event.getDimension()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerChangeDimensionAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerChangeDimensionAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerChangeDimensionAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ChangeDimensionRequestClass::newChangeDimensionRequest(
        //                             const_cast<ChangeDimensionRequest*>(&event.getChangeDimensionRequest())
        //                         ),
        //                         DimensionClass::newDimension(const_cast<Dimension*>(&event.getDimension()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerDropItemEvent: {
        // //   [Cancelable] PlayerDropItemBeforeEvent,
        // //   PlayerDropItemAfterEvent
        // // }
        // addCallback(
        //     "PlayerDropItemBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerDropItemBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerDropItemBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ItemStackClass::newItemStack(const_cast<ItemStack*>(&event.getItem()))
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerDropItemAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerDropItemAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerDropItemAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ItemStackClass::newItemStack(const_cast<ItemStack*>(&event.getItem()))
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerInteractEntityEvent: {
        // //   [Cancelable] PlayerInteractEntityBeforeEvent,
        // //   PlayerInteractEntityAfterEvent
        // // }
        // addCallback(
        //     "PlayerInteractEntityBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerInteractEntityBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerInteractEntityBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ActorClass::newActor(&event.getTarget()),
        //                         Vec3Class::newVec3Class(event.getPos())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerInteractEntityAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerInteractEntityAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerInteractEntityAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ActorClass::newActor(const_cast<Actor*>(&event.getTarget())),
        //                         Vec3Class::newVec3Class(event.getPos())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerOperatedItemFrameEvent: {
        // //   [Cancelable] PlayerOperatedItemFrameBeforeEvent,
        // //   PlayerOperatedItemFrameAfterEvent
        // // }
        // addCallback(
        //     "PlayerOperatedItemFrameBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerOperatedItemFrameBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerOperatedItemFrameBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getBlockPos()),
        //                         ConvertToScriptX(event.getType())
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerOperatedItemFrameAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerOperatedItemFrameAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerOperatedItemFrameAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         BlockPosClass::newBlockPosClass(event.getBlockPos()),
        //                         ConvertToScriptX(event.getType())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        //
        // // PlayerRequestItemActionEvent: {
        // //   [Cancelable] PlayerRequestItemActionBeforeEvent,
        // //   PlayerRequestItemActionAfterEvent
        // // }
        // addCallback(
        //     "PlayerRequestItemActionBeforeEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerRequestItemActionBeforeEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerRequestItemActionBeforeEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     auto result = func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ItemStackRequestActionTransferBaseClass::newItemStackRequestActionTransferBase(
        //                             const_cast<ItemStackRequestActionTransferBase*>(&event.getRequestAction())
        //                         )
        //                     );
        //                     if (result.isBoolean()) {
        //                         if (result.asBoolean().value() == false) event.cancel();
        //                     }
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );
        // addCallback(
        //     "PlayerRequestItemActionAfterEvent",
        //     [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
        //         return EventBus::getInstance().emplaceListener<ila::mc::PlayerRequestItemActionAfterEvent>(
        //             [&args,
        //              engine{EngineScope::currentEngine()},
        //              func{Global<Function>(args[1].asFunction())}](ila::mc::PlayerRequestItemActionAfterEvent& event) {
        //                 EngineScope scope(engine);
        //                 try {
        //                     func.get().call(
        //                         {},
        //                         PlayerClass::newPlayer(&event.self()),
        //                         ItemStackRequestActionTransferBaseClass::newItemStackRequestActionTransferBase(
        //                             const_cast<ItemStackRequestActionTransferBase*>(&event.getRequestAction())
        //                         ),
        //                         ConvertToScriptX(event.getResult())
        //                     );
        //                 }
        //                 CatchNotReturn;
        //             },
        //             priority
        //         );
        //     }
        // );

        // ClientLoginEvent: {
        //   [Cancelable] ClientLoginBeforeEvent,
        //   ClientLoginAfterEvent
        // }
//         addCallback(
//             "ClientLoginBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ClientLoginBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ClientLoginBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 ServerNetworkHandlerClass::newServerNetworkHandler(
//                                     const_cast<ServerNetworkHandler *>(&event.getServerNetworkHandler())
//                                 ),
//                                 NetworkIdentifierClass::newNetworkIdentifier(
//                                     const_cast<NetworkIdentifier *>(&event.getNetworkIdentifier())
//                                 )
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         }
//                         CatchNotReturn;
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "ClientLoginAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ClientLoginAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ClientLoginAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 ServerNetworkHandlerClass::newServerNetworkHandler(
//                                     const_cast<ServerNetworkHandler *>(&event.getServerNetworkHandler())
//                                 ),
//                                 NetworkIdentifierClass::newNetworkIdentifier(
//                                     const_cast<NetworkIdentifier *>(&event.getNetworkIdentifier())
//                                 ),
//                                 UUIDClass::newUUID(const_cast<mce::UUID *>(&event.getUuid())),
//                                 String::newString(event.getServerAuthXuid()),
//                                 String::newString(event.getClientAuthXuid()),
//                                 String::newString(event.getRealName()),
//                                 String::newString(event.getIpAndPort())
// 
//                             );
//                         }
//                         CatchNotReturn;
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // RegisterCmdEvent: {
//         //  RegisterCmdBeforeEvent,
//         //  RegisterCmdAfterEvent
//         // }
//         addCallback(
//             "RegisterCmdBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::RegisterCmdBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::RegisterCmdBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 // TODO: Waiting ila
//                                 // CommandRegistryClass::newCommandRegistry(&event.getRegistry()),
//                                 String::newString(event.getCommandName()),
//                                 String::newString(event.getDescription()),
//                                 ConvertToScriptX(event.getRequirement()),
//                                 CommandFlagClass::newCommandFlag(&event.getFlag1()),
//                                 CommandFlagClass::newCommandFlag(&event.getFlag2())
//                             );
//                         }
//                         CatchNotReturn;
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "RegisterCmdAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::RegisterCmdAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::RegisterCmdAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 // TODO: Waiting ila
//                                 // CommandRegistryClass::newCommandRegistry(&event.getRegistry()),
//                                 String::newString(event.getCommandName()),
//                                 String::newString(event.getDescription()),
//                                 ConvertToScriptX(event.getRequirement()),
//                                 CommandFlagClass::newCommandFlag(const_cast<CommandFlag *>(&event.getFlag1())),
//                                 CommandFlagClass::newCommandFlag(const_cast<CommandFlag *>(&event.getFlag2()))
//                             );
//                         }
//                         CatchNotReturn;
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // SendPacketEvent: {
//         //   [Cancelable] SendPacketBeforeEvent,
//         //   SendPacketAfterEvent
//         // }
//         addCallback(
//             "SendPacketBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SendPacketBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SendPacketBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 LoopbackPacketSenderClass::newLoopbackPacketSender(
//                                     const_cast<LoopbackPacketSender *>(&event.getPacketSender())
//                                 ),
//                                 PacketClass::newPacket(const_cast<Packet *>(&event.getPacket())),
//                                 Boolean::newBoolean(event.getIsBroadcast()),
//                                 PlayerClass::newPlayer(&event.getPlayer().get())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "SendPacketAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SendPacketAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SendPacketAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 LoopbackPacketSenderClass::newLoopbackPacketSender(
//                                     const_cast<LoopbackPacketSender *>(&event.getPacketSender())
//                                 ),
//                                 PacketClass::newPacket(const_cast<Packet *>(&event.getPacket())),
//                                 Boolean::newBoolean(event.getIsBroadcast()),
//                                 PlayerClass::newPlayer(&event.getPlayer().get())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // ServerPongEvent: {
//         //   [Cancelable] ServerPongBeforeEvent,
//         //   ServerPongAfterEvent
//         // }
//         addCallback(
//             "ServerPongBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ServerPongBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ServerPongBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 String::newString(event.getMotd()),
//                                 Number::newNumber(event.getProtocolVersion()),
//                                 String::newString(event.getNetworkVersion()),
//                                 Number::newNumber(event.getPlayerCount()),
//                                 Number::newNumber(event.getMaxPlayerCount()),
//                                 String::newString(event.getGuid()),
//                                 String::newString(event.getLevelName()),
//                                 ConvertToScriptX(event.getGameMode()),
//                                 Number::newNumber(event.getLocalPort()),
//                                 Number::newNumber(event.getLocalPortV6())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "ServerPongAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ServerPongAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ServerPongAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 String::newString(event.getMotd()),
//                                 Number::newNumber(event.getProtocolVersion()),
//                                 String::newString(event.getNetworkVersion()),
//                                 Number::newNumber(event.getPlayerCount()),
//                                 Number::newNumber(event.getMaxPlayerCount()),
//                                 String::newString(event.getGuid()),
//                                 String::newString(event.getLevelName()),
//                                 ConvertToScriptX(event.getGameMode()),
//                                 Number::newNumber(event.getLocalPort()),
//                                 Number::newNumber(event.getLocalPortV6()),
//                                 ConvertToScriptX(event.getOther())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // BlockTickEvent: {
//         //   [Cancelable] BlockTickBeforeEvent,
//         //   BlockTickAfterEvent
//         // }
//         // addCallback(
//         //     "BlockTickBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::BlockTickBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::BlockTickBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom()))
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "BlockTickAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::BlockTickAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::BlockTickAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom()))
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         //
//         // // DragonEggBlockTeleportEvent: {
//         // //   [Cancelable] DragonEggBlockTeleportBeforeEvent,
//         // //   DragonEggBlockTeleportAfterEvent
//         // // }
//         // addCallback(
//         //     "DragonEggBlockTeleportBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::DragonEggBlockTeleportBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}
//         //             ](ila::mc::DragonEggBlockTeleportBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom())),
//         //                         BlockPosClass::newBlockPosClass(event.getTargetPos())
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "DragonEggBlockTeleportAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::DragonEggBlockTeleportAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}
//         //             ](ila::mc::DragonEggBlockTeleportAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto pos2 = event.getTargetPos();
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom())),
//         //                         BlockPosClass::newBlockPosClass(event.getTargetPos())
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
// 
//         // ExplosionEvent: {
//         //   [Cancelable] ExplosionBeforeEvent,
//         //   ExplosionAfterEvent
//         // }
//         addCallback(
//             "ExplosionBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ExplosionBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ExplosionBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 ExplosionClass::newExplosion(&event.getExplosion())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "ExplosionAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::ExplosionAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::ExplosionAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 ExplosionClass::newExplosion(const_cast<Explosion *>(&event.getExplosion()))
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // FarmDecayEvent: {
//         //   [Cancelable] FarmDecayBeforeEvent,
//         //   FarmDecayAfterEvent
//         // }
//         // addCallback(
//         //     "FarmDecayBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::FarmDecayBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::FarmDecayBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         ActorClass::newActor(*&event.getActor()),
//         //                         Number::newNumber(event.getFallDistance())
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "FarmDecayAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::FarmDecayAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::FarmDecayAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         ActorClass::newActor(*&event.getActor()),
//         //                         Number::newNumber(event.getFallDistance())
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         //
//         // // LiquidTryFlowEvent: {
//         // //   [Cancelable] LiquidTryFlowBeforeEvent,
//         // //   LiquidTryFlowAfterEvent
//         // // }
//         // addCallback(
//         //     "LiquidTryFlowBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::LiquidTryFlowBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::LiquidTryFlowBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         BlockPosClass::newBlockPosClass(event.getFlowFromPos()),
//         //                         Number::newNumber(event.getFlowFromDirection())
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "LiquidTryFlowAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::LiquidTryFlowAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::LiquidTryFlowAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         BlockPosClass::newBlockPosClass(event.getFlowFromPos()),
//         //                         Number::newNumber(event.getFlowFromDirection())
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         //
//         // // MossGrowthEvent: {
//         // //   [Cancelable] MossGrowthBeforeEvent,
//         // //   MossGrowthAfterEvent
//         // // }
//         // addCallback(
//         //     "MossGrowthBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::MossGrowthBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::MossGrowthBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom())),
//         //                         Number::newNumber(event.getXRadius()),
//         //                         Number::newNumber(event.getZRadius())
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "MossGrowthAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::MossGrowthAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::MossGrowthAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto resArray = Array::newArray();
//         //
//         //                     for (auto a: event.getTargetPoss()) {
//         //                         resArray.add(BlockPosClass::newBlockPosClass(a));
//         //                     }
//         //
//         //
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getPos()),
//         //                         RandomClass::newRandom(const_cast<Random *>(&event.getRandom())),
//         //                         Number::newNumber(event.getXRadius()),
//         //                         Number::newNumber(event.getZRadius()),
//         //                         resArray
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
// 
//         // PistonPushEvent: {
//         //   [Cancelable] PistonPushBeforeEvent,
//         //   PistonPushAfterEvent
//         // }
//         addCallback(
//             "PistonPushBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::PistonPushBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::PistonPushBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPushPos()),
//                                 BlockPosClass::newBlockPosClass(event.getPistonPos()),
//                                 Number::newNumber(event.getBranchFacing()),
//                                 Number::newNumber(event.getPistonMoveFacing())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "PistonPushAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::PistonPushAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::PistonPushAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPushPos()),
//                                 BlockPosClass::newBlockPosClass(event.getPistonPos()),
//                                 Number::newNumber(event.getBranchFacing()),
//                                 Number::newNumber(event.getPistonMoveFacing())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // RedstoneUpdateEvent: {
//         //   [Cancelable] RedstoneUpdateBeforeEvent,
//         //   RedstoneUpdateAfterEvent
//         // }
//         addCallback(
//             "RedstoneUpdateBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::RedstoneUpdateBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::RedstoneUpdateBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos()),
//                                 Number::newNumber(event.getStrength()),
//                                 Number::newNumber(event.getIsFirstTime())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "RedstoneUpdateAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::RedstoneUpdateAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::RedstoneUpdateAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos()),
//                                 Number::newNumber(event.getStrength()),
//                                 Number::newNumber(event.getIsFirstTime())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // SculkBlockGrowthEvent: {
//         //   [Cancelable] SculkBlockGrowthBeforeEvent,
//         //   SculkBlockGrowthAfterEvent
//         // }
//         addCallback(
//             "SculkBlockGrowthBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SculkBlockGrowthBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SculkBlockGrowthBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "SculkBlockGrowthAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SculkBlockGrowthAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SculkBlockGrowthAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // SculkSpreadEvent: {
//         //   [Cancelable] SculkSpreadBeforeEvent,
//         //   SculkSpreadAfterEvent
//         // }
//         // addCallback(
//         //     "SculkSpreadBeforeEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::SculkSpreadBeforeEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::SculkSpreadBeforeEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     auto pos2 = event.getTargetPos();
//         //                     auto result = func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getSelfPos()),
//         //                         BlockClass::newBlock(&event.getSelfBlock()),
//         //                         Number::newNumber(event.getSelfFace()),
//         //                         BlockPosClass::newBlockPosClass(event.getTargetPos()),
//         //                         BlockClass::newBlock(&event.getTargetBlock()),
//         //                         Number::newNumber(event.getTargetFace()),
//         //                         Number::newNumber(event.getFacing())
//         //                     );
//         //                     if (result.isBoolean()) {
//         //                         if (result.asBoolean().value() == false) event.cancel();
//         //                     }
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
//         // addCallback(
//         //     "SculkSpreadAfterEvent",
//         //     [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//         //         return EventBus::getInstance().emplaceListener<ila::mc::SculkSpreadAfterEvent>(
//         //             [&args,
//         //                 engine{EngineScope::currentEngine()},
//         //                 func{Global<Function>(args[1].asFunction())}](ila::mc::SculkSpreadAfterEvent &event) {
//         //                 EngineScope scope(engine);
//         //                 try {
//         //                     func.get().call(
//         //                         {},
//         //                         BlockSourceClass::newBlockSource(&event.blockSource()),
//         //                         BlockPosClass::newBlockPosClass(event.getSelfPos()),
//         //                         BlockClass::newBlock(const_cast<Block *>(&event.getSelfBlock())),
//         //                         Number::newNumber(event.getSelfFace()),
//         //                         BlockPosClass::newBlockPosClass(event.getTargetPos()),
//         //                         BlockClass::newBlock(const_cast<Block *>(&event.getTargetBlock())),
//         //                         Number::newNumber(event.getTargetFace()),
//         //                         Number::newNumber(event.getFacing())
//         //                     );
//         //                 } catch (...) {
//         //                 }
//         //             },
//         //             priority
//         //         );
//         //     }
//         // );
// 
//         // SpawnItemActorEvent: {
//         //   [Cancelable] SpawnItemActorBeforeEvent,
//         //   SpawnItemActorAfterEvent
//         // }
//         addCallback(
//             "SpawnItemActorBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SpawnItemActorBeforeEvent>(
//                     [
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SpawnItemActorBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 Vec3Class::newVec3Class(event.getPos()),
//                                 ItemStackClass::newItemStack(&event.getItem()),
//                                 ActorClass::newActor(*&event.getSpawner()),
//                                 Number::newNumber(event.getThrowTime())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "SpawnItemActorAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SpawnItemActorAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SpawnItemActorAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 Vec3Class::newVec3Class(event.getPos()),
//                                 ItemStackClass::newItemStack(const_cast<ItemStack *>(&event.getItem())),
//                                 ActorClass::newActor(*&event.getSpawner()),
//                                 Number::newNumber(event.getThrowTime()),
//                                 ItemActorClass::newItemActor(*&event.getItemActor())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // SpawnWanderingTraderEvent: {
//         //   [Cancelable] SpawnWanderingTraderBeforeEvent,
//         //   SpawnWanderingTraderAfterEvent
//         // }
//         addCallback(
//             "SpawnWanderingTraderBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SpawnWanderingTraderBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SpawnWanderingTraderBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "SpawnWanderingTraderAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::SpawnWanderingTraderAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::SpawnWanderingTraderAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 BlockPosClass::newBlockPosClass(event.getPos())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
// 
//         // WitherDestroyEvent: {
//         //   [Cancelable] WitherDestroyBeforeEvent,
//         //   WitherDestroyAfterEvent
//         // }
//         addCallback(
//             "WitherDestroyBeforeEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::WitherDestroyBeforeEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::WitherDestroyBeforeEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             auto result = func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 LevelClass::newLevel(&event.level()),
//                                 AABBClass::newAABB(&event.getBox()),
//                                 Number::newNumber(event.getRadius())
//                             );
//                             if (result.isBoolean()) {
//                                 if (result.asBoolean().value() == false) event.cancel();
//                             }
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
//         addCallback(
//             "WitherDestroyAfterEvent",
//             [](const Arguments &args, ScriptEngine *engine, ll::event::EventPriority priority) {
//                 return EventBus::getInstance().emplaceListener<ila::mc::WitherDestroyAfterEvent>(
//                     [&args,
//                         engine{EngineScope::currentEngine()},
//                         func{Global<Function>(args[1].asFunction())}](ila::mc::WitherDestroyAfterEvent &event) {
//                         EngineScope scope(engine);
//                         try {
//                             func.get().call(
//                                 {},
//                                 BlockSourceClass::newBlockSource(&event.blockSource()),
//                                 LevelClass::newLevel(&event.level()),
//                                 AABBClass::newAABB(const_cast<AABB *>(&event.getBox())),
//                                 Number::newNumber(event.getRadius())
//                             );
//                         } catch (...) {
//                         }
//                     },
//                     priority
//                 );
//             }
//         );
    } catch (...) {
    }
}
