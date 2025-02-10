#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/packet/UpdateEquipPacket.h>

class UpdateEquipPacket;

class UpdateEquipPacketClass : public ScriptClass {
public:
    UpdateEquipPacket* mUpdateEquipPacket;

public:
    UpdateEquipPacketClass(UpdateEquipPacket* updateEquipPacket);

public:
    static Local<Object> newUpdateEquipPacket(UpdateEquipPacket* updateEquipPacket);

public: /* Member */
public: /* Method */
};

extern ClassDefine<UpdateEquipPacketClass> updateEquipPacketClassBuilder;