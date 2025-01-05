#include "API/Enum/EnumBuilder.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"

#include <mc/world/actor/ActorDamageCause.h>

#include <string>
#include <unordered_map>


#define REGISTER_ENUM_MACRO(ENUM, NAME)                                                                                \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        enumMap[NAME][key] = static_cast<int>(value);                                                                  \
    }

namespace Komomo::EnumAPI {

void RegisterEnum(ScriptEngine* engine) {
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> enumMap;

    REGISTER_ENUM_MACRO(ActorDamageCause, "ActorDamageCause")

    engine->set("Enums", ConvertToScriptX(enumMap));
}

#undef REGISTER_ENUM_MACRO

} // namespace Komomo::EnumAPI