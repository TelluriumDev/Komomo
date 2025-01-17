#include "API/Math/Random.h"

#include <mc/util/Random.h>

ClassDefine<RandomClass> randomClassBuilder = defineClass<RandomClass>("Random").constructor(nullptr).build();

RandomClass::RandomClass(Random* random) : ScriptClass(ConstructFromCpp<RandomClass>{}) { this->mRandom = random; }

Local<Object> RandomClass::newRandom(Random* random) { return (new RandomClass(random))->getScriptObject(); }