#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class NetworkIdentifier;

class NetworkIdentifierClass : public ScriptClass {
public:
    NetworkIdentifier* mNetworkIdentifier;

public:
    NetworkIdentifierClass(NetworkIdentifier* networkIdentifier);

public:
    static Local<Object> newNetworkIdentifier(NetworkIdentifier* networkIdentifier);

public: /* Member */
public: /* Method */
};

extern ClassDefine<NetworkIdentifierClass> networkIdentifierClassBuilder;