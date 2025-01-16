#include "API/Network/ConnectionRequest.h"


ClassDefine<ConnectionRequestClass> connectionRequestClassBuilder =
    defineClass<ConnectionRequestClass>("ConnectionRequest")
        .constructor(nullptr)

        .build();

ConnectionRequestClass::ConnectionRequestClass(ConnectionRequest* connectionRequest)
: ScriptClass(ConstructFromCpp<ConnectionRequestClass>{}) {
    this->mConnectionRequest = connectionRequest;
}

Local<Object> ConnectionRequestClass::newConnectionRequest(ConnectionRequest* connectionRequest) {
    return (new ConnectionRequestClass(connectionRequest))->getScriptObject();
}
