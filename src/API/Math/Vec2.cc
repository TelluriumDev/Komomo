#include "API/Math/Vec2.h"
#include "mc/deps/core/math/Vec2.h"


ClassDefine<Vec2Class> vec2ClassBuilder = defineClass<Vec2Class>("Vec2")
                                              .constructor(nullptr)


                                              .build();


Vec2Class::Vec2Class(Vec2 vec2) : ScriptClass(ConstructFromCpp<Vec2Class>{}) { this->mVec2 = vec2; }

Local<Object> Vec2Class::newVec2Class(Vec2 vec2) { return (new Vec2Class(vec2))->getScriptObject(); }