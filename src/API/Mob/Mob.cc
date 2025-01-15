#include "API/Mob/Mob.h"

ClassDefine<MobClass> mobClassBuilder =
    defineClass<MobClass>("Mob").constructor(nullptr).build();

MobClass::MobClass(Mob* mob) : ScriptClass(ConstructFromCpp<MobClass>{}) {
    this->mMob = mob;
}

Local<Object> MobClass::newMob(Mob* mob) {
    return (new MobClass(mob))->getScriptObject();
}