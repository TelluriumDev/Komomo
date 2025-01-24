#include "API/Math/Vec.h"


ClassDefine<VecClass> vecClassBuilder = defineClass<VecClass>("Vec")
                                            .constructor(nullptr)

                                            .function("newVec3", &VecClass::newVec3)
                                            .function("newVec4", &VecClass::newVec2)

                                            .build();

VecClass::VecClass() : ScriptClass(ConstructFromCpp<VecClass>{}) {}

Local<Object> VecClass::newVec3(float x, float y, float z) { return (new Vec3Class(x, y, z))->getScriptObject(); }

Local<Object> VecClass::newVec2(float x, float y) { return Vec2Class::newVec2(x, y); }
