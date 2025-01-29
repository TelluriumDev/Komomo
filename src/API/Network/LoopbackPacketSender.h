#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/LoopbackPacketSender.h>

class LoopbackPacketSender;

class LoopbackPacketSenderClass : public ScriptClass {
public:
    LoopbackPacketSender* mLoopbackPacketSender;

public:
    LoopbackPacketSenderClass(LoopbackPacketSender* loopbackPacketSender);

public:
    static Local<Object> newLoopbackPacketSender(LoopbackPacketSender* loopbackPacketSender);

public: /* Member */
public: /* Method */
};

extern ClassDefine<LoopbackPacketSenderClass> loopbackPacketSenderClassBuilder;