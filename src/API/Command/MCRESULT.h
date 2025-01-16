#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

// #include <mc/world/item/MCRESULT.h>

struct MCRESULT;

class MCRESULTClass : public ScriptClass {
public:
    MCRESULT* mMCRESULT;

public:
    MCRESULTClass(MCRESULT* MCRESULT);

public:
    static Local<Object> newMCRESULT(MCRESULT* MCRESULT);

public: /* Member */
public: /* Method */
};

extern ClassDefine<MCRESULTClass> MCRESULTClassBuilder;