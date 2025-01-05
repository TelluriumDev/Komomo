#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/Container.h>

class ContainerClass : public ScriptClass {
public:
    Container* mContainer;

public:
    ContainerClass(Container* container);

public:
    static Local<Object> newContainer(Container* container);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ContainerClass> containerClassBuilder;