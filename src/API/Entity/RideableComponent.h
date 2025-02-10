#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

class RideableComponent;

class RideableComponentClass : public ScriptClass {
public:
    RideableComponent* mRideableComponent;

public:
    RideableComponentClass(RideableComponent* rideableComponent);

public:
    static Local<Object> newRideableComponent(RideableComponent* rideableComponent);

public: /* Member */
public: /* Method */
};

extern ClassDefine<RideableComponentClass> rideableComponentClassBuilder;