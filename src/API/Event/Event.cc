#include "API/Event/Event.h"
#include "API/APIHelper.h"
#include "API/Command/MinecraftCommands.h"
#include "API/Event/Listener.h"

#include "API/Actor/Actor.h"
#include "API/Actor/ActorDamageSource.h"
#include "API/Actor/ActorDefinitionIdentifier.h"
#include "API/Block/Block.h"
#include "API/Block/BlockPos.h"
#include "API/Block/BlockSource.h"
#include "API/Command/CommandContext.h"
#include "API/Command/MCRESULT.h"
#include "API/Item/ItemActor.h"
#include "API/Item/ItemStack.h"
#include "API/Level/Level.h"
#include "API/Math/Vec3.h"
#include "API/Mob/Mob.h"
#include "API/Network/ConnectionRequest.h"
#include "API/Network/NetworkIdentifier.h"
#include "API/Player/Player.h"
#include "API/Service/Service.h"
#include "Utils/Convert.h"
#include "ll/api/event/Event.h"


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

// #include <ila/include_all.h>

#include <string>

using namespace Komomo;

ClassDefine<EventBusClass> eventBusClassBuilder = defineClass<EventBusClass>("EventBus")
                                                      .constructor(nullptr)

                                                      .function("emplaceListener", &EventBusClass::emplaceListener)
                                                      .function("removeListener", &EventBusClass::removeListener)


                                                      .build();

std::unordered_map<
    std::string,
    std::function<ll::event::ListenerPtr(const Arguments&, ScriptEngine*, ll::event::EventPriority)>>
    EventBusClass::callBackMap = {};

std::unordered_map<std::string, std::vector<ll::event::ListenerPtr>> listeners;


EventBusClass::EventBusClass() : ScriptClass(ConstructFromCpp<EventBusClass>{}) {};


Local<Value> EventBusClass::emplaceListener(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kFunction, Boolean::newBoolean(false));

    using ll::event::EventBus;
    using ll::hash_utils::doHash;

    try {
        std::string eventName = args[0].asString().toString();
        auto        priority  = ll::event::EventPriority::Normal;
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
        }
        return Local<Value>();
    }
    Catch;
}
Local<Value> EventBusClass::removeListener(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    using ll::event::EventBus;
    try {
        if (IsInstanceOf<ListenerClass>(args[0])) {
            auto engine        = EngineScope::currentEngine();
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
    return Boolean::newBoolean(false);
}

void EventBusClass::removeModAllListeners(std::string modName) {
    using ll::event::EventBus;
    for (auto& listener : listeners[modName]) {
        EventBus::getInstance().removeListener(listener);
    }
    listeners.erase(modName);
}


void EventBusClass::removeAllListeners() {
    using ll::event::EventBus;
    for (auto& listener : listeners) {
        for (auto& l : listener.second) {
            EventBus::getInstance().removeListener(l);
        }
    }
    listeners.clear();
}

KMMAPI void EventBusClass::addCallback(
    std::string                                                                                      event,
    std::function<ll::event::ListenerPtr(const Arguments&, ScriptEngine*, ll::event::EventPriority)> callBack
) {
    callBackMap.emplace(event, callBack);
}

void EventBusClass::registerCallback() {
    using ll::event::EventBus;
    try {
        addCallback(
            "ServerStartedEvent",
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServerStartedEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ServerStartedEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServerStoppingEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ServerStoppingEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerAddExperienceEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerAddExperienceEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerAttackEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerAttackEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerChangePermEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerChangePermEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerChatEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerChatEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerConnectEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerConnectEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                NetworkIdentifierClass::newNetworkIdentifier(
                                    const_cast<NetworkIdentifier*>(&event.networkIdentifier())
                                ),
                                ConnectionRequestClass::newConnectionRequest(
                                    const_cast<ConnectionRequest*>(&event.connectionRequest())
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDestroyBlockEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDestroyBlockEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.pos()))
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDieEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDieEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ActorDamageSourceClass::newActorDamageSource(
                                    const_cast<ActorDamageSource*>(&event.source())
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerDisconnectEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerDisconnectEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerInteractBlockEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerInteractBlockEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                ItemStackClass::newItemStack(&event.item()),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.blockPos())),
                                ConvertToScriptX(event.face()),
                                Vec3Class::newVec3(const_cast<Vec3*>(&event.clickPos())),
                                BlockClass::newBlock(const_cast<Block*>(&event.block().get()))
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerJoinEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerJoinEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerJumpEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerJumpEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPickUpItemEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPickUpItemEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPlacingBlockEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPlacingBlockEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.pos())),
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerPlacedBlockEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerPlacedBlockEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                PlayerClass::newPlayer(&event.self()),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.pos())),
                                BlockClass::newBlock(const_cast<Block*>(&event.placedBlock()))
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerRespawnEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerRespawnEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSneakingEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSneakingEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSneakedEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSneakedEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSprintingEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSprintingEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSprintedEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSprintedEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerSwingEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerSwingEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::PlayerUseItemEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::PlayerUseItemEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::BlockChangedEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::BlockChangedEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource*>(&event.blockSource())),
                                Number::newNumber(event.layer()),
                                BlockClass::newBlock(const_cast<Block*>(&event.previousBlock())),
                                BlockClass::newBlock(const_cast<Block*>(&event.newBlock())),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.pos()))
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::FireSpreadEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::FireSpreadEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource*>(&event.blockSource())),
                                BlockPosClass::newBlockPos(const_cast<BlockPos*>(&event.pos()))
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::LevelTickEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::LevelTickEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({}, LevelClass::newLevel(const_cast<Level*>(&event.level())));
                        }
                        CatchNotReturn;
                    },
                    priority
                );
            }
        );
        addCallback(
            "SpawningMobEvent",
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::SpawningMobEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::SpawningMobEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                BlockSourceClass::newBlockSource(const_cast<BlockSource*>(&event.blockSource())),
                                ActorDefinitionIdentifierClass::newActorDefinitionIdentifier(
                                    const_cast<ActorDefinitionIdentifier*>(&event.identifier())
                                ),
                                ActorClass::newActor(&event.spawner().value()),
                                Vec3Class::newVec3(const_cast<Vec3*>(&event.pos())),
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::SpawnedMobEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::SpawnedMobEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                MobClass::newMob(&event.mob().value()),
                                BlockSourceClass::newBlockSource(const_cast<BlockSource*>(&event.blockSource())),
                                ActorDefinitionIdentifierClass::newActorDefinitionIdentifier(
                                    const_cast<ActorDefinitionIdentifier*>(&event.identifier())
                                ),
                                ActorClass::newActor(&event.spawner().value()),
                                Vec3Class::newVec3(const_cast<Vec3*>(&event.pos())),
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ActorHurtEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ActorHurtEvent& event) {
                        EngineScope scope(engine);
                        try {
                            auto result = func.get().call(
                                {},
                                ActorClass::newActor(&event.self()),
                                ActorDamageSourceClass::newActorDamageSource(
                                    const_cast<ActorDamageSource*>(&event.source())
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
        addCallback("MobDieEvent", [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
            return EventBus::getInstance().emplaceListener<ll::event::MobDieEvent>(
                [&args,
                 engine{EngineScope::currentEngine()},
                 func{Global<Function>(args[1].asFunction())}](ll::event::MobDieEvent& event) {
                    EngineScope scope(engine);
                    try {
                        func.get().call(
                            {},
                            MobClass::newMob(&event.self()),
                            ActorDamageSourceClass::newActorDamageSource(const_cast<ActorDamageSource*>(&event.source())
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ExecutingCommandEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ExecutingCommandEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ExecutedCommandEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ExecutedCommandEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call(
                                {},
                                MCRESULTClass::newMCRESULT(&event.result()),
                                MinecraftCommandsClass::newMinecraftCommands(&event.minecraftCommands()),
                                CommandContextClass::newCommandContext(
                                    const_cast<CommandContext*>(&event.commandContext())
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServiceRegisterEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ServiceRegisterEvent& event) {
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
            [](const Arguments& args, ScriptEngine* engine, ll::event::EventPriority priority) {
                return EventBus::getInstance().emplaceListener<ll::event::ServiceUnregisterEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ServiceUnregisterEvent& event) {
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
    } catch (...) {}
}
