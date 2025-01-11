#include "API/Player/LayeredAbilities.h"


ClassDefine<LayeredAbilitiesClass> layeredabilitiesClassBuilder = defineClass<LayeredAbilitiesClass>("LayeredAbilities")
                                                                      .constructor(nullptr)

                                                                      .build();

LayeredAbilitiesClass::LayeredAbilitiesClass(LayeredAbilities* layeredabilities)
: ScriptClass(ConstructFromCpp<LayeredAbilitiesClass>{}) {
    this->mLayeredAbilities = layeredabilities;
}

Local<Object> LayeredAbilitiesClass::newLayeredAbilities(LayeredAbilities* layeredabilities) {
    return (new LayeredAbilitiesClass(layeredabilities))->getScriptObject();
}
