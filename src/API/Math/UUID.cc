#include "API/Math/UUID.h"

ClassDefine<UUIDClass> uuidClassBuilder = defineClass<UUIDClass>("UUID").constructor(nullptr).build();

UUIDClass::UUIDClass(mce::UUID* uuid) : ScriptClass(ConstructFromCpp<UUIDClass>{}) {
    this->mUUID= uuid;
 }

Local<Object> UUIDClass::newUUID( mce::UUID* uuid) { return (new UUIDClass(uuid))->getScriptObject(); }