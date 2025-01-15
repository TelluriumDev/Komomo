#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

class Mob;

class MobClass : public ScriptClass {
public:
    Mob* mMob;

public:
    MobClass(Mob* mob);

public:
    static Local<Object> newMob(Mob* mob);

public: /* Member */
public: /* Method */
};

extern ClassDefine<MobClass> mobClassBuilder;