#include "API/Network/Packet/UpdateTradePacket.h"


ClassDefine<UpdateTradePacketClass> updateTradePacketClassBuilder =
    defineClass<UpdateTradePacketClass>("UpdateTradePacket")
        .constructor(nullptr)

        .build();

UpdateTradePacketClass::UpdateTradePacketClass(UpdateTradePacket* updateTradePacket)
: ScriptClass(ConstructFromCpp<UpdateTradePacketClass>{}) {
    this->mUpdateTradePacket = updateTradePacket;
}

Local<Object> UpdateTradePacketClass::newUpdateTradePacket(UpdateTradePacket* updateTradePacket) {
    return (new UpdateTradePacketClass(updateTradePacket))->getScriptObject();
}
