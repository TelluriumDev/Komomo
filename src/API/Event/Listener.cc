#include "API/Event/Listener.h"
#include "ll/api/event/ListenerBase.h"

ClassDefine<ListenerClass> listenerClassBuilder = defineClass<ListenerClass>("Listener")
                                                           //    .constructor(&ListenerClass::newListener)
                                                           .constructor(nullptr)

                                                           .build();

ListenerClass::ListenerClass(ll::event::ListenerPtr* listener) : ScriptClass(ConstructFromCpp<ListenerClass>{}) {
    this->listener = listener;
}

Local<Object> ListenerClass::newListenPtr(ll::event::ListenerPtr* listener) {
    return (new ListenerClass(listener))->getScriptObject();
}
