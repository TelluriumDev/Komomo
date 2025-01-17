#include "API/Level/Explosion.h"

#include <mc/world/level/Explosion.h>

ClassDefine<ExplosionClass> explosionClassBuilder = defineClass<ExplosionClass>("Explosion").constructor(nullptr).build();

ExplosionClass::ExplosionClass(Explosion* explosion) : ScriptClass(ConstructFromCpp<ExplosionClass>{}) { this->mExplosion = explosion; }

Local<Object> ExplosionClass::newExplosion(Explosion* explosion) { return (new ExplosionClass(explosion))->getScriptObject(); }