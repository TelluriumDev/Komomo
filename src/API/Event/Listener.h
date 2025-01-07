#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "ll/api/event/ListenerBase.h"

#include <ll/api/event/Listener.h>

class ListenerClass : public ScriptClass {
public:
    ll::event::ListenerPtr* listener = nullptr;

public:
    ListenerClass(ll::event::ListenerPtr* listener);

public:
    // static ListenerClass* newListener(const Arguments& args);

    static Local<Object> newListenPtr(ll::event::ListenerPtr* listener);
};

extern ClassDefine<ListenerClass> listenerClassBuilder;