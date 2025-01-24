#include "API/Math/Vec2.h"
#include "mc/deps/core/math/Vec2.h"


ClassDefine<Vec2Class> vec2ClassBuilder = defineClass<Vec2Class>("Vec2")
                                              .constructor(nullptr)


                                              .build();

Vec2Class::Vec2Class(float x, float y) : ScriptClass(ConstructFromCpp<Vec2Class>{}) {
    this->x     = x;
    this->y     = y;
    this->mVec2 = Vec2(x, y);
}

Local<Object> Vec2Class::newVec2(float x, float y) { return (new Vec2Class(x, y))->getScriptObject(); }
