#include "API/Level/Level.h"

ClassDefine<LevelClass> levelClassBuilder =
    defineClass<LevelClass>("Level").constructor(nullptr).build();

LevelClass::LevelClass(Level* level) : ScriptClass(ConstructFromCpp<LevelClass>{}) {
    this->mLevel = level;
}

Local<Object> LevelClass::newLevel(Level* level) {
    return (new LevelClass(level))->getScriptObject();
}