#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


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