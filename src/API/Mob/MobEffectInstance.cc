#include "API/Mob/MobEffectInstance.h"


ClassDefine<MobEffectInstanceClass> mobEffectInstanceClassBuilder =
    defineClass<MobEffectInstanceClass>("MobEffectInstance")
        .constructor(nullptr)

        .build();

MobEffectInstanceClass::MobEffectInstanceClass(MobEffectInstance* mobEffectInstance)
: ScriptClass(ConstructFromCpp<MobEffectInstanceClass>{}) {
    this->mMobEffectInstance = mobEffectInstance;
}

Local<Object> MobEffectInstanceClass::newMobEffectInstance(MobEffectInstance* mobEffectInstance) {
    return (new MobEffectInstanceClass(mobEffectInstance))->getScriptObject();
}
