#include "API/Actor/EquipmentTable.h"


ClassDefine<EquipmentTableClass> equipmentTableClassBuilder = defineClass<EquipmentTableClass>("EquipmentTable")
                                                                .constructor(nullptr)

                                                                .build();

EquipmentTableClass::EquipmentTableClass(EquipmentTable* equipmentTable)
: ScriptClass(ConstructFromCpp<EquipmentTableClass>{}) {
    this->mEquipmentTable = equipmentTable;
}

Local<Object> EquipmentTableClass::newEquipmentTable(EquipmentTable* equipmentTable) {
    return (new EquipmentTableClass(equipmentTable))->getScriptObject();
}
