#include "API/Math/Vec3.h"


ClassDefine<Vec3Class> vec3ClassBuilder = defineClass<Vec3Class>("Vec3")
                                              .constructor(nullptr)

                                              .build();

Vec3Class::Vec3Class(float x, float y, float z) : ScriptClass(ConstructFromCpp<Vec3Class>{}) {
    this->x     = x;
    this->y     = y;
    this->z     = z;
    this->mVec3 = Vec3(x, y, z);
}

Local<Object> Vec3Class::newVec3(float x, float y, float z) { return (new Vec3Class(x, y, z))->getScriptObject(); }

