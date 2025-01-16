#include "API/Entity/EntityContext.h"


ClassDefine<EntityContextClass> entityContextClassBuilder = defineClass<EntityContextClass>("EntityContext")
                                                                .constructor(nullptr)

                                                                .build();

EntityContextClass::EntityContextClass(EntityContext* entityContext)
: ScriptClass(ConstructFromCpp<EntityContextClass>{}) {
    this->mEntityContext = entityContext;
}

Local<Object> EntityContextClass::newEntityContext(EntityContext* entityContext) {
    return (new EntityContextClass(entityContext))->getScriptObject();
}
