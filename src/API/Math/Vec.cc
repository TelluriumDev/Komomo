#include "API/Math/Vec.h"

ClassDefine<VecClass> vecClassBuilder = defineClass<VecClass>("Vec")
                                            .constructor(nullptr)

                                            .function("newVec3", &VecClass::newVec3)
                                            .function("newVec2", &VecClass::newVec2)

                                            .build();

VecClass::VecClass() : ScriptClass(ConstructFromCpp<VecClass>{}) {}

Local<Object> VecClass::newVec3(float x, float y, float z) { return Vec3Class::newVec3Class(Vec3(x, y, z)); }

Local<Object> VecClass::newVec2(float x, float y) { return Vec2Class::newVec2Class(Vec2(x, y)); }
