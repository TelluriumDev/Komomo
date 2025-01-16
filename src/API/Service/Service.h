#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include <ll/api/service/Service.h>


class ServiceClass : public ScriptClass {
public:
    ll::service::Service* mService;

public:
    ServiceClass(ll::service::Service* service);

public:
    static Local<Object> newService(ll::service::Service* service);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ServiceClass> serviceClassBuilder;