#include "API/Math/AABB.h"

ClassDefine<AABBClass> aabbClassBuilder = defineClass<AABBClass>("AABB").constructor(nullptr).build();

AABBClass::AABBClass(AABB* aabb) : ScriptClass(ConstructFromCpp<AABBClass>{}) { this->mAABB = aabb; }

Local<Object> AABBClass::newAABB(AABB* aabb) { return (new AABBClass(aabb))->getScriptObject(); }