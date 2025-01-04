#include "API/Container/Container.h"


ClassDefine<ContainerClass> ActorClassBuilder = defineClass<ContainerClass>("Actor")
                                                    .constructor(nullptr)

                                                    .build();

ContainerClass::ContainerClass(Container* container) : ScriptClass(ConstructFromCpp<ContainerClass>{}) {
    this->mContainer = container;
}

Local<Object> ContainerClass::newContainer(Container* container) {
    return (new ContainerClass(container))->getScriptObject();
}

