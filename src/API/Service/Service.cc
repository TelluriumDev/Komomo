#include "API/Service/Service.h"

using namespace Komomo;

ClassDefine<ServiceClass> serviceClassBuilder = defineClass<ServiceClass>("Service").constructor(nullptr).build();

ServiceClass::ServiceClass(ll::service::Service* service) : ScriptClass(ConstructFromCpp<ServiceClass>{}) {
    this->mService = service;
}


Local<Object> ServiceClass::newService(ll::service::Service* service) {
    return (new ServiceClass(service))->getScriptObject();
}