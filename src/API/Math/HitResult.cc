#include "API/Math/HitResult.h"

ClassDefine<HitResultClass> hitResultClassBuilder =
    defineClass<HitResultClass>("HitResult").constructor(nullptr).build();

HitResultClass::HitResultClass(HitResult* hitResult) : ScriptClass(ConstructFromCpp<HitResultClass>{}) {
    this->mHitResult = hitResult;
}

Local<Object> HitResultClass::newHitResult(HitResult* hitResult) {
    return (new HitResultClass(hitResult))->getScriptObject();
}