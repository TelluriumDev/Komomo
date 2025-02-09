#include "API/Network/ChangeDimensionPacket.h"


ClassDefine<ChangeDimensionPacketClass> changeDimensionPacketClassBuilder =
    defineClass<ChangeDimensionPacketClass>("ChangeDimensionPacket")
        .constructor(nullptr)

        .build();

ChangeDimensionPacketClass::ChangeDimensionPacketClass(ChangeDimensionPacket* changeDimensionPacket)
: ScriptClass(ConstructFromCpp<ChangeDimensionPacketClass>{}) {
    this->mChangeDimensionPacket = changeDimensionPacket;
}

Local<Object> ChangeDimensionPacketClass::newChangeDimensionPacket(ChangeDimensionPacket* changeDimensionPacket) {
    return (new ChangeDimensionPacketClass(changeDimensionPacket))->getScriptObject();
}
