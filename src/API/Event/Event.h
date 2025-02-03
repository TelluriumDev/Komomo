#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

extern std::unordered_map<std::string, std::vector<ll::event::ListenerPtr>> listeners;


class EventBusClass : public ScriptClass {

private:
    static std::unordered_map<
        std::string,
        std::function<ll::event::ListenerPtr(const Arguments&, ScriptEngine*, ll::event::EventPriority)>>
        callBackMap;

public:
    EventBusClass();

public:
    static Local<Value> emplaceListener(const Arguments& args);

    static Local<Value> removeListener(const Arguments& args);

    static void removeModAllListeners(std::string modName);

    static Local<Value> removeMyModListener();

    static void removeAllListeners();

    KMMAPI static void addCallback(
        std::string                                                                                      event,
        std::function<ll::event::ListenerPtr(const Arguments&, ScriptEngine*, ll::event::EventPriority)> callBack
    );

    static void registerCallback();
};

extern ClassDefine<EventBusClass> eventBusClassBuilder;