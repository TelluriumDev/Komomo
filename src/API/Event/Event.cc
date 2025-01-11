#include "API/Event/Event.h"
#include "API/APIHelper.h"
#include "API/Event/Listener.h"
#include "API/Player/Player.h"
#include "Event.h"
#include "Utils/Convert.h"
#include "ll/api/event/ListenerBase.h"

#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/server/ServerStartedEvent.h>
#include <ll/api/utils/HashUtils.h>

using namespace Komomo;

ClassDefine<EventBusClass> eventBusClassBuilder = defineClass<EventBusClass>("EventBus")
                                                      .nameSpace("ll.event")
                                                      .constructor(nullptr)

                                                      .function("emplaceListener", &EventBusClass::emplaceListener)
                                                      .function("removeListener", &EventBusClass::removeListener)


                                                      .build();

std::unordered_map<std::string, std::vector<ll::event::ListenerPtr>> listeners;

EventBusClass::EventBusClass() : ScriptClass(ConstructFromCpp<EventBusClass>{}) {};

Local<Value> EventBusClass::emplaceListener(const Arguments& args) {
    CheckArgsCountReturn(args, 2, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[1], ValueKind::kFunction, Boolean::newBoolean(false));

    using ll::event::EventBus;
    using ll::hash_utils::doHash;

    try {
        std::string            eventName = args[0].asString().toString();
        auto                   priority  = ll::event::EventPriority::Normal;
        ll::event::ListenerPtr listener  = nullptr;
        if (args.size() >= 3) {
            CheckArgTypeReturn(args[2], ValueKind::kNumber, Boolean::newBoolean(false));
            priority = ConvertFromScriptX<ll::event::EventPriority>(args[2]);
        }
        switch (doHash(eventName)) {
        case doHash("onServerStarted"): {
            try {
                listener = EventBus::getInstance().emplaceListener<ll::event::ServerStartedEvent>(
                    [&args,
                     engine{EngineScope::currentEngine()},
                     func{Global<Function>(args[1].asFunction())}](ll::event::ServerStartedEvent& event) {
                        EngineScope scope(engine);
                        try {
                            func.get().call({});
                        }
                        CatchNotReturn
                    },
                    priority
                );
                listeners[ENGINE_DATA()->mMod->getName()].push_back(listener);
                return ListenerClass::newListenPtr(&listener);
            }
            CatchNotReturn;
            break;
        }
        case doHash("onPlayerJoin"): {
            try {
                listener = EventBus::getInstance().emplaceListener<ll::event::PlayerJoinEvent>(
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
                    // Komomo::getKomomoModManager().getMod(ENGINE_DATA()->mMod->getName())
                );
                listeners[ENGINE_DATA()->mMod->getName()].push_back(listener);
                return ListenerClass::newListenPtr(&listener);
            }
            CatchNotReturn;
            break;
        }
        }
    }
    Catch;
    return Local<Value>();
}

Local<Value> EventBusClass::removeListener(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    using ll::event::EventBus;
    try {
        if (IsInstanceOf<ListenerClass>(args[0])) {
            auto engine        = EngineScope::currentEngine();
            auto listenerClass = engine->getNativeInstance<ListenerClass>(args[0]);
            if (listenerClass) {
                return Boolean::newBoolean(EventBus::getInstance().removeListener(*listenerClass->listener));
            }
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
