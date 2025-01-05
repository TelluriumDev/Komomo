#include "API/Enum/EnumBuilder.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"


#include <mc/network/packet/ModalFormCancelReason.h>
#include <mc/world/actor/ActorDamageCause.h>


#include <string>
#include <unordered_map>


#define REGISTER_ENUM_MACRO(NAMESPACE, ENUM, NAME)                                                                     \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        NAMESPACE[NAME][key] = static_cast<int>(value);                                                                \
    }

namespace Komomo::EnumAPI {

void RegisterEnum(ScriptEngine* engine) {
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> PlayerEnum;
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> FormEnum;


    REGISTER_ENUM_MACRO(FormEnum, ModalFormCancelReason, "ModalFormCancelReason");

    engine->set("FormEnum", ConvertToScriptX(FormEnum));
    engine->set("PlayerEnum", ConvertToScriptX(PlayerEnum));
}

#undef REGISTER_ENUM_MACRO

} // namespace Komomo::EnumAPI