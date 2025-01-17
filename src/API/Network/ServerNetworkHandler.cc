#include "API/Network/ServerNetworkHandler.h"


ClassDefine<ServerNetworkHandlerClass> serverNetworkHandlerClassBuilder =
    defineClass<ServerNetworkHandlerClass>("ServerNetworkHandler")
        .constructor(nullptr)

        .build();

ServerNetworkHandlerClass::ServerNetworkHandlerClass(ServerNetworkHandler* serverNetworkHandler)
: ScriptClass(ConstructFromCpp<ServerNetworkHandlerClass>{}) {
    this->mServerNetworkHandler = serverNetworkHandler;
}

Local<Object> ServerNetworkHandlerClass::newServerNetworkHandler(ServerNetworkHandler* serverNetworkHandler) {
    return (new ServerNetworkHandlerClass(serverNetworkHandler))->getScriptObject();
}
