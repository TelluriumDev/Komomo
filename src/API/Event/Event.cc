#include "API/Event/Event.h"
#include "API/Player/Player.h"
#include "Event.h"
#include "Manager/EngineData.h"
#include "Utils/Using.h"

#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/server/ServerStartedEvent.h>

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
                CallBackNoCancelEvent(engineId, eventId, eventPtr);
            }
        );
        break;
    }
    case EventList::onPlayerJoin: {
        ll::event::ListenerPtr eventPtr = eventBus.emplaceListener<ll::event::PlayerJoinEvent>(
            [engineId, eventId, &eventPtr](const ll::event::PlayerJoinEvent& event) {
                CallBackNoCancelEvent(engineId, eventId, eventPtr, PlayerClass::newPlayer(&event.self()));
            }
        );
        break;
    }
    }
}

bool addEventListener(const std::string& eventName, ScriptEngine* engine, const Local<Function>& func) {
    auto      event_enum = magic_enum::enum_cast<EventList>(eventName);
    auto      eventId    = int(event_enum.value());
    EventData data{eventId, func};
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
            map[enginedata->mID].erase(it);
            return true;
        }
    }
    return false;
}


Local<Value> EventClass::emplaceListener(const Arguments& args) {
    try {
        return Boolean::newBoolean(
            addEventListener(args[0].asString().toString(), EngineScope::currentEngine(), args[1].asFunction())
        );
    }
    Catch;
}

Local<Value> EventClass::removeListener(const Arguments& args) {
    CheckArgsCount(args, 2) try {
        return Boolean::newBoolean(
            removeEventListener(args[0].asString().toString(), EngineScope::currentEngine(), args[1].asFunction())
        );
    }
    Catch;
}
