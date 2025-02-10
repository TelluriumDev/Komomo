#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/packet/ChangeDimensionPacket.h>

class ChangeDimensionPacket;

class ChangeDimensionPacketClass : public ScriptClass {
public:
    ChangeDimensionPacket* mChangeDimensionPacket;

public:
    ChangeDimensionPacketClass(ChangeDimensionPacket* changeDimensionPacket);

public:
    static Local<Object> newChangeDimensionPacket(ChangeDimensionPacket* changeDimensionPacket);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ChangeDimensionPacketClass> changeDimensionPacketClassBuilder;