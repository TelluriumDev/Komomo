#include "API/Player/LayeredAbilities.h"


ClassDefine<LayeredAbilitiesClass> layeredAbilitiesClassBuilder = defineClass<LayeredAbilitiesClass>("LayeredAbilities")
                                                                      .constructor(nullptr)

                                                                      .build();

LayeredAbilitiesClass::LayeredAbilitiesClass(LayeredAbilities* layeredAbilities)
: ScriptClass(ConstructFromCpp<LayeredAbilitiesClass>{}) {
    this->mLayeredAbilities = layeredAbilities;
}

Local<Object> LayeredAbilitiesClass::newLayeredAbilities(LayeredAbilities* layeredAbilities) {
    return (new LayeredAbilitiesClass(layeredAbilities))->getScriptObject();
}
