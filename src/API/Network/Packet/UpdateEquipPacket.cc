#include "API/Network/Packet/UpdateEquipPacket.h"


ClassDefine<UpdateEquipPacketClass> updateEquipPacketClassBuilder =
    defineClass<UpdateEquipPacketClass>("UpdateEquipPacket")
        .constructor(nullptr)

        .build();

UpdateEquipPacketClass::UpdateEquipPacketClass(UpdateEquipPacket* updateEquipPacket)
: ScriptClass(ConstructFromCpp<UpdateEquipPacketClass>{}) {
    this->mUpdateEquipPacket = updateEquipPacket;
}

Local<Object> UpdateEquipPacketClass::newUpdateEquipPacket(UpdateEquipPacket* updateEquipPacket) {
    return (new UpdateEquipPacketClass(updateEquipPacket))->getScriptObject();
}
