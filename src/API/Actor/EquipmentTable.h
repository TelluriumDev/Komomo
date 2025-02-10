#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/EquipmentTable.h>

class EquipmentTableClass : public ScriptClass {
public:
  EquipmentTable* mEquipmentTable;

public:
  EquipmentTableClass(EquipmentTable* equipmentTable);

public:
  static Local<Object> newEquipmentTable(EquipmentTable* equipmentTable);

public: /* Member */
public: /* Method */
};

extern ClassDefine<EquipmentTableClass> equipmentTableClassBuilder;