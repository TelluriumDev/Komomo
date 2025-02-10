#include "API/Entity/RideableComponent.h"


ClassDefine<RideableComponentClass> rideableComponentClassBuilder = defineClass<RideableComponentClass>("RideableComponent")
                                                                .constructor(nullptr)

                                                                .build();

RideableComponentClass::RideableComponentClass(RideableComponent* rideableComponent)
: ScriptClass(ConstructFromCpp<RideableComponentClass>{}) {
    this->mRideableComponent = rideableComponent;
}

Local<Object> RideableComponentClass::newRideableComponent(RideableComponent* rideableComponent) {
    return (new RideableComponentClass(rideableComponent))->getScriptObject();
}
