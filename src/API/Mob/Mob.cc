#include "API/Mob/Mob.h"

ClassDefine<MobClass> mobClassBuilder = defineClass<MobClass>("Mob").constructor(nullptr).build();

Local<Object> MobClass::newMobClass(Mob *mob) { return (new MobClass(mob))->getScriptObject(); }