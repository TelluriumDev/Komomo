#include "API/Network/NetworkIdentifier.h"


ClassDefine<NetworkIdentifierClass> networkIdentifierClassBuilder =
    defineClass<NetworkIdentifierClass>("NetworkIdentifier")
        .constructor(nullptr)

        .build();

NetworkIdentifierClass::NetworkIdentifierClass(NetworkIdentifier* networkIdentifier)
: ScriptClass(ConstructFromCpp<NetworkIdentifierClass>{}) {
    this->mNetworkIdentifier = networkIdentifier;
}

Local<Object> NetworkIdentifierClass::newNetworkIdentifier(NetworkIdentifier* networkIdentifier) {
    return (new NetworkIdentifierClass(networkIdentifier))->getScriptObject();
}
