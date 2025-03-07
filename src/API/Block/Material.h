#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/level/material/Material.h>

class MaterialClass : public ScriptClass {
public:
    Material *mMaterial;

public:
    MaterialClass(Material *material);

public:
    static Local<Object> newMaterial(Material *material);

    // public: /* Member */
    //     Local<Value> getBlocksMotion();
    //     Local<Value> getBlocksPrecipitation();
    //     Local<Value> isLiquid();
    //     Local<Value> isSolid();
    //     Local<Value> isSolidBlocking();
    //     Local<Value> isSuperHot();
    //
    // public: /* Method */
    //     Local<Value> isTopSolid(const Arguments& args);
    //     Local<Value> isType(const Arguments& args);

    // static
    static Local<Value> getMaterial(int type);
};

extern ClassDefine<MaterialClass> materialClassBuilder;
