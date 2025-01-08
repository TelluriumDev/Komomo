#include "API/Enum/EnumBuilder.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"

#include <ll/api/event/ListenerBase.h>
#include <ll/api/io/LogLevel.h>


#include <mc/world/actor/ActionEvent.h>
#include <mc/world/actor/ActorCategory.h>
#include <mc/world/actor/ActorDamageCause.h>
#include <mc/world/actor/ActorDataIDs.h>
#include <mc/world/actor/ActorDefinitionEventType.h>
#include <mc/world/actor/ActorDefinitionGroup.h>
#include <mc/world/actor/ActorDefinitionParseStatus.h>
#include <mc/world/actor/ActorEvent.h>
#include <mc/world/actor/ActorFilterGroup.h>
#include <mc/world/actor/ActorFlags.h>
#include <mc/world/actor/ActorInitializationMethod.h>
#include <mc/world/actor/ActorLinkType.h>
#include <mc/world/actor/ActorLocation.h>
#include <mc/world/actor/ActorTargetFilter.h>
#include <mc/world/actor/ActorTerrainInterlockData.h>
#include <mc/world/actor/ActorType.h>
#include <mc/world/actor/ActorTypeNamespaceRules.h>
#include <mc/world/actor/ArmorMaterialType.h>
#include <mc/world/actor/ArmorTextureType.h>
#include <mc/world/actor/DataItemType.h>
#include <mc/world/actor/DefinitionEventType.h>
#include <mc/world/actor/HorseInventoryEnum.h>
#include <mc/world/actor/KeyOrNameResult.h>
#include <mc/world/actor/MobSpawnMethod.h>
#include <mc/world/actor/PaletteColor.h>
#include <mc/world/actor/ParticleType.h>
#include <mc/world/actor/RenderContextType.h>
#include <mc/world/actor/RenderParam.h>
#include <mc/world/actor/SerializedAbilitiesData.h>
#include <mc/world/actor/SkeletalHierarchyIndex.h>
#include <mc/world/actor/SpawnRuleEnum.h>
#include <mc/world/actor/TravelType.h>
#include <mc/world/actor/TypeExecutingEvent.h>

#include <mc/world/actor/player/AbilitiesIndex.h>
#include <mc/world/actor/player/AbilitiesLayer.h>
#include <mc/world/actor/player/Ability.h>
#include <mc/world/actor/player/BedSleepingResult.h>
#include <mc/world/actor/player/LoadingState.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/actor/player/PlayerSpawnFallbackType.h>
#include <mc/world/actor/player/PlayerUISlot.h>
#include <mc/world/actor/player/SkinAdjustments.h>
#include <mc/world/actor/player/TrustedSkinFlag.h>

#include <mc/network/packet/ModalFormCancelReason.h>

#include <string>
#include <unordered_map>


#define REGISTER_ENUM_MACRO(NAMESPACE, ENUM, NAME)                                                                     \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        NAMESPACE[NAME][key] = static_cast<int>(value);                                                                \
    }

namespace Komomo::EnumAPI {

void RegisterEnum(ScriptEngine* engine) {
    // Actor
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> ActorEnum;
    // REGISTER_ENUM_MACRO(ActorEnum, ActionEvent::<unnamed>, "ActionEvent")
    REGISTER_ENUM_MACRO(ActorEnum, ActionEvent::ActionState, "ActionState");
    REGISTER_ENUM_MACRO(ActorEnum, ActorDamageCause, "ActorDamageCause");
    REGISTER_ENUM_MACRO(ActorEnum, ActorCategory, "ActorCategory");
    REGISTER_ENUM_MACRO(ActorEnum, ActorDataIDs, "ActorDataIDs");
    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionEventType, "ActorDefinitionEventType");
    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionGroup::LoadStatus, "LoadStatus");
    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionParseStatus, "ActorDefinitionParseStatus");
    REGISTER_ENUM_MACRO(ActorEnum, ActorEvent, "ActorEvent");
    REGISTER_ENUM_MACRO(ActorEnum, ActorFilterGroup::Processing, "Processing");
    REGISTER_ENUM_MACRO(ActorEnum, ActorFlags, "ActorFlags");
    REGISTER_ENUM_MACRO(ActorEnum, ActorInitializationMethod, "ActorInitialzationMethod");
    REGISTER_ENUM_MACRO(ActorEnum, ActorLinkType, "ActorLinkType");
    REGISTER_ENUM_MACRO(ActorEnum, ActorLocation, "ActorLocation");
    REGISTER_ENUM_MACRO(ActorEnum, ActorTargetFilter::ConditionType, "ConditionType");
    REGISTER_ENUM_MACRO(ActorEnum, ActorTerrainInterlockData::VisibilityState, "VisibilityState");
    REGISTER_ENUM_MACRO(ActorEnum, ActorType, "ActorType");
    REGISTER_ENUM_MACRO(ActorEnum, ActorTypeNamespaceRules, "ActorTypeNamespaceRules");
    REGISTER_ENUM_MACRO(ActorEnum, ArmorMaterialType, "ArmorMaterialType");
    REGISTER_ENUM_MACRO(ActorEnum, ArmorTextureType, "ArmorTextureType");
    REGISTER_ENUM_MACRO(ActorEnum, DataItemType, "DataItemType");
    REGISTER_ENUM_MACRO(ActorEnum, DefinitionEventType, "DefinitionEventType");
    REGISTER_ENUM_MACRO(ActorEnum, HorseInventoryEnum, "HorseInventoryEnum");
    REGISTER_ENUM_MACRO(ActorEnum, KeyOrNameResult::ResultType, "ResultType");
    REGISTER_ENUM_MACRO(ActorEnum, MobSpawnMethod, "MobSpawnMethod");
    REGISTER_ENUM_MACRO(ActorEnum, PaletteColor, "PaletteColor");
    REGISTER_ENUM_MACRO(ActorEnum, ParticleType, "ParticleType");
    REGISTER_ENUM_MACRO(ActorEnum, RenderContextType, "RenderContextType");
    REGISTER_ENUM_MACRO(ActorEnum, RenderParam, "RenderParam");
    REGISTER_ENUM_MACRO(ActorEnum, SerializedAbilitiesData::SerializedAbilitiesLayer, "SerializedAbilitiesLayer");
    REGISTER_ENUM_MACRO(ActorEnum, SkeletalHierarchyIndex, "SkeletalHierarchyIndex");
    REGISTER_ENUM_MACRO(ActorEnum, SpawnRuleEnum, "SpawnRuleEnum");
    REGISTER_ENUM_MACRO(ActorEnum, TravelType, "TravelType");
    REGISTER_ENUM_MACRO(ActorEnum, TypeExecutingEvent, "TypeExecutingEvent");
    engine->set("ActorEnum", ConvertToScriptX(ActorEnum));

    // Player
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> PlayerEnum;
    REGISTER_ENUM_MACRO(PlayerEnum, AbilitiesIndex, "AbilitiesIndex");
    REGISTER_ENUM_MACRO(PlayerEnum, AbilitiesLayer, "AbilitiesLayer");
    REGISTER_ENUM_MACRO(PlayerEnum, Ability::Type, "Type");
    REGISTER_ENUM_MACRO(PlayerEnum, Ability::Options, "Options");
    REGISTER_ENUM_MACRO(PlayerEnum, BedSleepingResult, "BedSleepingResult");
    REGISTER_ENUM_MACRO(PlayerEnum, LoadingState, "LoadingState");
    REGISTER_ENUM_MACRO(PlayerEnum, Player::SpawnPositionState, "SpawnPositionState");
    REGISTER_ENUM_MACRO(PlayerEnum, PlayerSpawnFallbackType, "PlayerSpawnFallbackType");
    REGISTER_ENUM_MACRO(PlayerEnum, PlayerUISlot, "PlayerUISlot");
    REGISTER_ENUM_MACRO(PlayerEnum, SkinAdjustments::AnimBits, "AnimBits");
    REGISTER_ENUM_MACRO(PlayerEnum, TrustedSkinFlag, "TrustedSkinFlagS");
    engine->set("PlayerEnum", ConvertToScriptX(PlayerEnum));

    // Form
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> FormEnum;
    REGISTER_ENUM_MACRO(FormEnum, ModalFormCancelReason, "ModalFormCancelResult");
    engine->set("FormEnum", ConvertToScriptX(FormEnum));

    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> EventEnum;
    REGISTER_ENUM_MACRO(EventEnum, ll::event::EventPriority, "EventPriority");
    engine->set("EventEnum", ConvertToScriptX(EventEnum));

    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> LoggerEnum;
    REGISTER_ENUM_MACRO(LoggerEnum, ll::io::LogLevel, "LogLevel");
    engine->set("LoggerEnum", ConvertToScriptX(LoggerEnum));
}

#undef REGISTER_ENUM_MACRO

} // namespace Komomo::EnumAPI