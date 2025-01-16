#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep


class EntityContext;

class EntityContextClass : public ScriptClass {
public:
    EntityContext* mEntityContext;

public:
    EntityContextClass(EntityContext* entityContext);

public:
    static Local<Object> newEntityContext(EntityContext* entityContext);

public: /* Member */
public: /* Method */
};

extern ClassDefine<EntityContextClass> entityContextClassBuilder;