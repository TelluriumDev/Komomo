#include "API/Container/Container.h"


ClassDefine<ContainerClass> containerClassBuilder = defineClass<ContainerClass>("Container")
                                                        .constructor(nullptr)

                                                        .build();

ContainerClass::ContainerClass(Container* container) : ScriptClass(ConstructFromCpp<ContainerClass>{}) {
    this->mContainer = container;
}

Local<Object> ContainerClass::newContainer(Container* container) {
    return (new ContainerClass(container))->getScriptObject();
}
