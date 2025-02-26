#include "API/Command/MCRESULT.h"


ClassDefine<MCRESULTClass> MCRESULTClassBuilder = defineClass<MCRESULTClass>("MCRESULT").constructor(nullptr).build();

MCRESULTClass::MCRESULTClass(MCRESULT* MCRESULT) : ScriptClass(ConstructFromCpp<MCRESULTClass>{}) {
    this->mMCRESULT = MCRESULT;
}

Local<Object> MCRESULTClass::newMCRESULT(MCRESULT* MCRESULT) {
    return (new MCRESULTClass(MCRESULT))->getScriptObject();
}