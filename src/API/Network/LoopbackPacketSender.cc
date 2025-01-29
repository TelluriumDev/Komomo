#include "API/Network/LoopbackPacketSender.h"

ClassDefine<LoopbackPacketSenderClass> loopbackPacketSenderClassBuilder =
    defineClass<LoopbackPacketSenderClass>("LoopbackPacketSender")
        .constructor(nullptr)

        .build();

LoopbackPacketSenderClass::LoopbackPacketSenderClass(LoopbackPacketSender* loopbackPacketSender)
: ScriptClass(ConstructFromCpp<LoopbackPacketSenderClass>{}) {
    this->mLoopbackPacketSender = loopbackPacketSender;
}

Local<Object> LoopbackPacketSenderClass::newLoopbackPacketSender(LoopbackPacketSender* loopbackPacketSender) {
    return (new LoopbackPacketSenderClass(loopbackPacketSender))->getScriptObject();
}
