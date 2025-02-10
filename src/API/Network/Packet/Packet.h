#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/packet/Packet.h>

class Packet;

class PacketClass : public ScriptClass {
public:
    Packet* mPacket;

public:
    PacketClass(Packet* packet);

public:
    static Local<Object> newPacket(Packet* packet);

public: /* Member */
public: /* Method */
};

extern ClassDefine<PacketClass> packetClassBuilder;