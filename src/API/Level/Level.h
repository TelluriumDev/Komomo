#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include "mc/world/level/Level.h"

class Level;

class LevelClass : public ScriptClass {
public:
    Level* mLevel;

public:
    LevelClass(Level* level);

public:
    static Local<Object> newLevel(Level* level);

public: /* Member */
public: /* Method */
};

extern ClassDefine<LevelClass> levelClassBuilder;