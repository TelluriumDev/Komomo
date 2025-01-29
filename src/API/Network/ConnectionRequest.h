#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/network/ConnectionRequest.h>

class ConnectionRequest;

class ConnectionRequestClass : public ScriptClass {
public:
    ConnectionRequest* mConnectionRequest;

public:
    ConnectionRequestClass(ConnectionRequest* connectionRequest);

public:
    static Local<Object> newConnectionRequest(ConnectionRequest* connectionRequest);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ConnectionRequestClass> connectionRequestClassBuilder;