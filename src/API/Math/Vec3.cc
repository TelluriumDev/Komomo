#include "API/Math/Vec3.h"


ClassDefine<Vec3Class> vec3ClassBuilder = defineClass<Vec3Class>("Vec3")
                                              .constructor(nullptr)

                                              .build();

Vec3Class::Vec3Class(Vec3 vec3) : ScriptClass(ConstructFromCpp<Vec3Class>{}) { this->mVec3 = vec3; }

Local<Object> Vec3Class::newVec3Class(Vec3 vec3) { return (new Vec3Class(vec3))->getScriptObject(); }
