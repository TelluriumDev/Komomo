#pragma once

#include "API/APIHelper.h"       // IWYU pragma: keep
#include "Manager/NodeManager.h" // IWYU pragma: keep
#include "Utils/Using.h"


#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/Listener.h>
#include <ll/api/event/ListenerBase.h>


#include <unordered_map>
#include <vector>

#define EventId int

struct EventData {
    EventData(EventId id, const Global<Function>& callback) : id(id), callback(callback) {};
    EventId                id;
    Global<Function>       callback;
    ll::event::ListenerPtr listener;
};

// {引擎ID : [监听器] }}
extern std::unordered_map<EngineID, std::vector<EventData>> map;

class EventClass : public ScriptClass {

public:
    EventClass();
    static Local<Value> emplaceListener(const Arguments& args);
    static Local<Value> removeListener(const Arguments& args);
};

extern ClassDefine<EventClass> EventClassBuilder;

#define CallBackNoCancelEvent(EngineID, EventID, EventPtr, ...)                                                        \
    for (auto& data : map[EngineID]) {                                                                                 \
        if (data.id == EventID) {                                                         \
            script::EngineScope engineScope(*NodeManager::getInstance().getEngine(EngineID));                          \
            try {                                                                                                      \
                data.callback.get().call({}, __VA_ARGS__);                                                             \
                data.listener    = std::move(EventPtr);                                                                \
            }                                                                                                          \
            Catch;                                                                                                     \
        }                                                                                                              \
    }
