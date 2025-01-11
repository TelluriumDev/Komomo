#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/player/LayeredAbilities.h>

class LayeredAbilitiesClass : public ScriptClass {
public:
    LayeredAbilities* mLayeredAbilities;

public:
    LayeredAbilitiesClass(LayeredAbilities* layeredabilities);

public:
    static Local<Object> newLayeredAbilities(LayeredAbilities* layeredabilities);

public: /* Member */
public: /* Method */
};

extern ClassDefine<LayeredAbilitiesClass> layeredabilitiesClassBuilder;