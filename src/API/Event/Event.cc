#include "API/Event/Event.h"
#include "API/APIHelper.h"
#include "API/Player/Player.h"
#include "Event.h"
#include "Manager/EngineData.h"
#include "Utils/Using.h"
#include "ll/api/event/EventBus.h"

#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/server/ServerStartedEvent.h>
#include <utility>

using namespace Komomo;

ClassDefine<EventClass> EventClassBuilder = defineClass<EventClass>("Event")

                                                .function("emplaceListener", &EventClass::emplaceListener)
                                                .function("removeListener", &EventClass::removeListener)

                                                .build();


std::unordered_map<EngineID, std::vector<EventData>> map;

// 使用枚举代替魔法值
enum class EventList : int { onServerStarted = 0, onPlayerJoin };

EventClass::EventClass() : ScriptClass(ConstructFromCpp<EventClass>{}) {};


void EnableListener(EngineID engineId, EventId eventId) {
    auto& eventBus = ll::event::EventBus::getInstance();
    switch ((EventList)eventId) {
    case EventList::onServerStarted: {
        ll::event::ListenerPtr eventPtr = eventBus.emplaceListener<ll::event::ServerStartedEvent>(
            [engineId, eventId, &eventPtr](const ll::event::ServerStartedEvent& event) {
                if (eventPtr) CallBackNoCancelEvent(engineId, eventId, eventPtr);
                return Local<Value>();
            }
        );
        break;
    }
    case EventList::onPlayerJoin: {
        ll::event::ListenerPtr eventPtr = eventBus.emplaceListener<ll::event::PlayerJoinEvent>(
            [engineId, eventId, &eventPtr](const ll::event::PlayerJoinEvent& event) {
                CallBackNoCancelEvent(engineId, eventId, eventPtr, PlayerClass::newPlayer(&event.self()));
                return Local<Value>();
            }
        );
        break;
    }
    }
}

bool addEventListener(const std::string& eventName, ScriptEngine* engine, const Local<Function>& func) {
    auto      event_enum = magic_enum::enum_cast<EventList>(eventName);
    auto      eventId    = int(event_enum.value());
    EventData data{eventId, Global<Function>(func)};
    auto      enginedata = GET_ENGINE_DATA(engine);
    map[enginedata->mID].push_back(data);
    EnableListener(enginedata->mID, eventId);
    return true;
}

bool removeEventListener(const std::string& eventName, ScriptEngine* engine, const Local<Function>& func) {
    auto event_enum = magic_enum::enum_cast<EventList>(eventName);
    auto eventId    = int(event_enum.value());
    auto enginedata = GET_ENGINE_DATA(engine);
    for (auto it = map[enginedata->mID].begin(); it != map[enginedata->mID].end(); ++it) {
        if (it->id == eventId && it->callback.get() == func) {
            ll::event::EventBus::getInstance().removeListener(std::move(it->listener));
            map[enginedata->mID].erase(it);
            return true;
        }
    }
    return false;
}

void removeEngineAllEventListener(EngineID engineId) {
    if (map.find(engineId) == map.end()) return;
    for (auto& data : map[engineId]) {
        ll::event::EventBus::getInstance().removeListener(std::move(data.listener));
    }
}

void removeAllEventListener() { map.clear(); }


Local<Value> EventClass::emplaceListener(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kFunction);
    try {
        return Boolean::newBoolean(
            addEventListener(args[0].asString().toString(), EngineScope::currentEngine(), args[1].asFunction())
        );
    }
    Catch;
}

Local<Value> EventClass::removeListener(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kFunction);
    try {
        return Boolean::newBoolean(
            removeEventListener(args[0].asString().toString(), EngineScope::currentEngine(), args[1].asFunction())
        );
    }
    Catch;
}
