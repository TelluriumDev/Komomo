#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/effect/MobEffectInstance.h>

class MobEffectInstance;

class MobEffectInstanceClass : public ScriptClass {
public:
  MobEffectInstance* mMobEffectInstance;

public:
  MobEffectInstanceClass(MobEffectInstance* mobEffectInstance);

public:
  static Local<Object> newMobEffectInstance(MobEffectInstance* mobEffectInstance);

public: /* Member */
public: /* Method */
};

extern ClassDefine<MobEffectInstanceClass> mobEffectInstanceClassBuilder;