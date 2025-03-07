#include "API/Block/Material.h"

using namespace Komomo;

ClassDefine<MaterialClass> materialClassBuilder =
        defineClass<MaterialClass>("Block")
        .constructor(nullptr)

        // .instanceProperty("blocksMotion", &MaterialClass::getBlocksMotion)
        // .instanceProperty("blocksPrecipitation", &MaterialClass::getBlocksPrecipitation)
        // .instanceProperty("isLiquid", &MaterialClass::isLiquid)
        // .instanceProperty("isSolid", &MaterialClass::isSolid)
        // .instanceProperty("isSolidBlocking", &MaterialClass::isSolidBlocking)
        // .instanceProperty("isSuperHot", &MaterialClass::isSuperHot)
        //
        // .InstanceFunction(isTopSolid, MaterialClass)
        // .InstanceFunction(isType, MaterialClass)

        .function("getMaterial", &MaterialClass::getMaterial)

        .build();

MaterialClass::MaterialClass(Material *material)
    : ScriptClass(ConstructFromCpp<MaterialClass>{}),
      mMaterial(material) {
}

Local<Object> MaterialClass::newMaterial(Material *material) {
    return (new MaterialClass(material))->getScriptObject();
}

#define CallFunction(Type, Function)                                                                                   \
    try {                                                                                                              \
        if (!mMaterial) return Local<Value>();                                                                         \
        return Type::new##Type(mMaterial->Function);                                                                   \
    }                                                                                                                  \
    Catch;

#define CallVoidMethod(Function)                                                                                       \
    try {                                                                                                              \
        if (!mMaterial) return Local<Value>();                                                                         \
        mMaterial->Function;                                                                                           \
        return Boolean::newBoolean(true);                                                                              \
    }                                                                                                                  \
    CatchReturn(Boolean::newBoolean(false));


// Local<Value> MaterialClass::getBlocksMotion() {
//     CallFunction(Boolean, getBlocksMotion());
// }

// Local<Value> MaterialClass::getBlocksPrecipitation() { CallFunction(Boolean, getBlocksPrecipitation()); }
//
// Local<Value> MaterialClass::isLiquid() { CallFunction(Boolean, isLiquid()); }
//
// Local<Value> MaterialClass::isSolid() { CallFunction(Boolean, isSolid()); }
//
// Local<Value> MaterialClass::isSolidBlocking() { CallFunction(Boolean, isSolidBlocking()); }
//
// Local<Value> MaterialClass::isSuperHot() { CallFunction(Boolean, isSuperHot()); }
//
// Local<Value> MaterialClass::isTopSolid(const Arguments &args) {
//     CheckArgsCount(args, 2);
//     CheckArgType(args[0], ValueKind::kBoolean);
//     CheckArgType(args[1], ValueKind::kBoolean);
//     try {
//         if (!mMaterial) return Local<Value>();
//         auto includeWater = args[0].asBoolean().value();
//         auto includeLeaves = args[1].asBoolean().value();
//         return Boolean::newBoolean(mMaterial->isTopSolid(includeWater, includeLeaves));
//     }
//     Catch;
// }
//
// Local<Value> MaterialClass::isType(const Arguments &args) {
//     CheckArgsCount(args, 1);
//     CheckArgType(args[0], ValueKind::kNumber);
//     try {
//         if (!mMaterial) return Local<Value>();
//         return Boolean::newBoolean(mMaterial->isType(ConvertFromScriptX<MaterialType>(args[0])));
//     }
//     Catch;
// }

Local<Value> MaterialClass::getMaterial(int type) {
    auto &material = const_cast<Material &>(Material::getMaterial(static_cast<MaterialType>(type)));
    return MaterialClass::newMaterial(&material);
}
