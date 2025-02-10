#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/packet/UpdateTradePacket.h>

class UpdateTradePacket;

class UpdateTradePacketClass : public ScriptClass {
public:
    UpdateTradePacket* mUpdateTradePacket;

public:
    UpdateTradePacketClass(UpdateTradePacket* updateTradePacket);

public:
    static Local<Object> newUpdateTradePacket(UpdateTradePacket* updateTradePacket);

public: /* Member */
public: /* Method */
};

extern ClassDefine<UpdateTradePacketClass> updateTradePacketClassBuilder;