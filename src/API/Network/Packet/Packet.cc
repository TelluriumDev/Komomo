#include "API/Network/Packet/Packet.h"

ClassDefine<PacketClass> packetClassBuilder = defineClass<PacketClass>("Packet")
                                                  .constructor(nullptr)

                                                  .build();

PacketClass::PacketClass(Packet* packet) : ScriptClass(ConstructFromCpp<PacketClass>{}) { this->mPacket = packet; }

Local<Object> PacketClass::newPacket(Packet* packet) { return (new PacketClass(packet))->getScriptObject(); }
