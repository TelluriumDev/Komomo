#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>


#include <vector>

extern std::vector<ll::event::ListenerPtr> listeners;


class EventBusClass : public ScriptClass {

public:
    EventBusClass();

public:
    static Local<Value> emplaceListener(const Arguments& args);

    static Local<Value> removeListener(const Arguments& args);

    static void removeAllListeners();
};

extern ClassDefine<EventBusClass> eventBusClassBuilder;