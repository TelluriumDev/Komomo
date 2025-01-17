#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

class Explosion;

class ExplosionClass : public ScriptClass {
public:
    Explosion* mExplosion;

public:
    ExplosionClass(Explosion* explosion);

public:
    static Local<Object> newExplosion(Explosion* explosion);

public: /* Member */
public: /* Method */
};

extern ClassDefine<ExplosionClass> explosionClassBuilder;