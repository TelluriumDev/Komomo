#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/ServerNetworkHandler.h>

class ServerNetworkHandler;

class ServerNetworkHandlerClass : public ScriptClass {
public:
    ServerNetworkHandler* mServerNetworkHandler;

public:
    ServerNetworkHandlerClass(ServerNetworkHandler* serverNetworkHandler);

public:
    static Local<Object> newServerNetworkHandler(ServerNetworkHandler* serverNetworkHandler);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ServerNetworkHandlerClass> serverNetworkHandlerClassBuilder;