#include "API/Enum/EnumBuilder.h"
#include "API/Enum/EnumInclude.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"


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

    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> CommonEnum;
    REGISTER_ENUM_MACRO(CommonEnum, CompactionStatus, "CompactionStatus");
    REGISTER_ENUM_MACRO(CommonEnum, FacingID, "FacingID");
    REGISTER_ENUM_MACRO(CommonEnum, GameUserType, "GameUserType");
    REGISTER_ENUM_MACRO(CommonEnum, GameVersion::Octet, "Octet");
    REGISTER_ENUM_MACRO(CommonEnum, SubClientId, "SubClientId");
    REGISTER_ENUM_MACRO(CommonEnum, XforgeGameVersion::Octet, "Octet");
    REGISTER_ENUM_MACRO(CommonEnum, Editor::WorldType, "WorldType");
    REGISTER_ENUM_MACRO(CommonEnum, Facing::Axis, "Axis");
    REGISTER_ENUM_MACRO(CommonEnum, Facing::Name, "Name");
    REGISTER_ENUM_MACRO(CommonEnum, Facing::Rotation, "Rotation");
    REGISTER_ENUM_MACRO(CommonEnum, TitleInfo::TitleId, "TitleId");
    engine->set("CommonEnum", ConvertToScriptX(CommonEnum));

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

    // auto generated ItemEnum
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> ItemEnum;
    REGISTER_ENUM_MACRO(ItemEnum, ArmorSlot, "ArmorSlot");
    REGISTER_ENUM_MACRO(ItemEnum, BannerPatternItem::Type, "Type");
    REGISTER_ENUM_MACRO(ItemEnum, BucketFillType, "BucketFillType");
    REGISTER_ENUM_MACRO(ItemEnum, CameraItemComponentLegacy::UseAction, "UseAction");
    REGISTER_ENUM_MACRO(ItemEnum, CoalItem::Type, "Type");
    REGISTER_ENUM_MACRO(ItemEnum, CompoundContainerType, "CompoundContainerType");
    REGISTER_ENUM_MACRO(ItemEnum, CompoundType, "CompoundType");
    REGISTER_ENUM_MACRO(ItemEnum, CreativeItemCategory, "CreativeItemCategory");
    REGISTER_ENUM_MACRO(ItemEnum, FertilizerType, "FertilizerType");
    REGISTER_ENUM_MACRO(ItemEnum, FireworkChargeItem::Shape, "Shape");
    REGISTER_ENUM_MACRO(ItemEnum, FoodItemComponentLegacy::OnUseAction, "OnUseAction");
    REGISTER_ENUM_MACRO(ItemEnum, HandSlot, "HandSlot");
    REGISTER_ENUM_MACRO(ItemEnum, HorseArmorItem::Tier, "Tier");
    REGISTER_ENUM_MACRO(ItemEnum, HumanoidArmorItem::Tier, "Tier");
    REGISTER_ENUM_MACRO(ItemEnum, InHandUpdateType, "InHandUpdateType");
    REGISTER_ENUM_MACRO(ItemEnum, ItemAcquisitionMethod, "ItemAcquisitionMethod");
    REGISTER_ENUM_MACRO(ItemEnum, ItemColor, "ItemColor");
    REGISTER_ENUM_MACRO(ItemEnum, ItemCommandVisibility, "ItemCommandVisibility");
    REGISTER_ENUM_MACRO(ItemEnum, ItemContextType, "ItemContextType");
    REGISTER_ENUM_MACRO(ItemEnum, ItemDescriptor::InternalType, "InternalType");
    REGISTER_ENUM_MACRO(ItemEnum, ItemIconInfoType, "ItemIconInfoType");
    REGISTER_ENUM_MACRO(ItemEnum, ItemLockMode, "ItemLockMode");
    REGISTER_ENUM_MACRO(ItemEnum, ItemUseMethod, "ItemUseMethod");
    REGISTER_ENUM_MACRO(ItemEnum, MapType, "MapType");
    REGISTER_ENUM_MACRO(ItemEnum, MedicineType, "MedicineType");
    REGISTER_ENUM_MACRO(ItemEnum, NotifyItemUsedOnEvent, "NotifyItemUsedOnEvent");
    REGISTER_ENUM_MACRO(ItemEnum, PageContent::PageType, "PageType");
    REGISTER_ENUM_MACRO(ItemEnum, Rarity, "Rarity");
    REGISTER_ENUM_MACRO(ItemEnum, SaveContext::SaveUseCase, "SaveUseCase");
    REGISTER_ENUM_MACRO(ItemEnum, SaveContext::SaveOperation, "SaveOperation");
    REGISTER_ENUM_MACRO(ItemEnum, SlotWithDropChance, "SlotWithDropChance");
    REGISTER_ENUM_MACRO(ItemEnum, SmithingTemplateItem::UpgradeType, "UpgradeType");
    REGISTER_ENUM_MACRO(ItemEnum, SuspiciousStewItem::SuspiciousStewType, "SuspiciousStewType");
    REGISTER_ENUM_MACRO(ItemEnum, Potion::PotionType, "PotionType");
    REGISTER_ENUM_MACRO(ItemEnum, Potion::PotionVariant, "PotionVariant");
    REGISTER_ENUM_MACRO(ItemEnum, OnUseOrder, "OnUseOrder");
    REGISTER_ENUM_MACRO(ItemEnum, RenderOffsetsItemComponent::Hand, "Hand");
    REGISTER_ENUM_MACRO(ItemEnum, RenderOffsetsItemComponent::Perspective, "Perspective");
    REGISTER_ENUM_MACRO(ItemEnum, UseTimeDepletedOrder, "UseTimeDepletedOrder");
    REGISTER_ENUM_MACRO(ItemEnum, RecipeUnlockingRequirement::UnlockingContext, "UnlockingContext");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Type, "Type");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Frequency, "Frequency");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Slot, "Slot");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Activation, "Activation");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::CompatibilityID, "CompatibilityID");
    REGISTER_ENUM_MACRO(ItemEnum, Enchant::VillagerTrading, "VillagerTrading");
    REGISTER_ENUM_MACRO(ItemEnum, EnchantResultType, "EnchantResultType");
    REGISTER_ENUM_MACRO(ItemEnum, EquipmentFilter, "EquipmentFilter");
    REGISTER_ENUM_MACRO(ItemEnum, ItemVersion, "ItemVersion");
    engine->set("ItemEnum", ConvertToScriptX(ItemEnum));

    // auto generated InventoryEnum
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> InventoryEnum;
    REGISTER_ENUM_MACRO(InventoryEnum, ActorContainerType, "ActorContainerType");
    REGISTER_ENUM_MACRO(InventoryEnum, InventoryLayout, "InventoryLayout");
    REGISTER_ENUM_MACRO(InventoryEnum, InventoryLeftTabIndex, "InventoryLeftTabIndex");
    REGISTER_ENUM_MACRO(InventoryEnum, InventoryRightTabIndex, "InventoryRightTabIndex");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackNetManagerServer::TextFilterState, "TextFilterState");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackNetResult, "ItemStackNetResult");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionHandler::RemoveType, "RemoveType");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionMineBlock::PreValidationStatus, "PreValidationStatus");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionType, "ItemStackRequestActionType");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestScreen, "ItemStackRequestScreen");
    REGISTER_ENUM_MACRO(InventoryEnum, SparseContainerClient::PushSlotPredictionResult, "PushSlotPredictionResult");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenActionResultData::Type, "Type");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenAutoplaceBehaviour, "ContainerScreenAutoplaceBehaviour");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenRequestActionType, "ContainerScreenRequestActionType");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenTransferBehaviour, "ContainerScreenTransferBehaviour");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationCaller, "ContainerValidationCaller");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationCommitObject::Type, "Type");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationOperationType, "ContainerValidationOperationType");
    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationOutcome, "ContainerValidationOutcome");
    REGISTER_ENUM_MACRO(InventoryEnum, SparseContainerBackingSetType, "SparseContainerBackingSetType");
    REGISTER_ENUM_MACRO(InventoryEnum, ComplexInventoryTransaction::Type, "Type");
    REGISTER_ENUM_MACRO(InventoryEnum, InventorySource::InventorySourceFlags, "InventorySourceFlags");
    REGISTER_ENUM_MACRO(InventoryEnum, InventorySourceType, "InventorySourceType");
    REGISTER_ENUM_MACRO(InventoryEnum, InventoryTransactionError, "InventoryTransactionError");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemReleaseInventoryTransaction::ActionType, "ActionType");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::ActionType, "ActionType");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::TriggerType, "TriggerType");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::PredictedResult, "PredictedResult");
    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseOnActorInventoryTransaction::ActionType, "ActionType");
    engine->set("InventoryEnum", ConvertToScriptX(InventoryEnum));

    // Form
    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> FormEnum;
    REGISTER_ENUM_MACRO(FormEnum, ModalFormCancelReason, "ModalFormCancelResult");
    engine->set("FormEnum", ConvertToScriptX(FormEnum));

    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> EventEnum = []() {
        std::unordered_map<std::string, std::unordered_map<std::string_view, int>> map;
        REGISTER_ENUM_MACRO(EventEnum, ll::event::EventPriority, "EventPriority");
        map["EventPriority"]["Highest"] = 0;
        map["EventPriority"]["High"]    = 100;
        map["EventPriority"]["Normal"]  = 200;
        map["EventPriority"]["Low"]     = 300;
        map["EventPriority"]["Lowest"]  = 400;
        return map;
    }();

    engine->set("EventEnum", ConvertToScriptX(EventEnum));

    static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> LoggerEnum;
    REGISTER_ENUM_MACRO(LoggerEnum, ll::io::LogLevel, "LogLevel");
    engine->set("LoggerEnum", ConvertToScriptX(LoggerEnum));
}

#undef REGISTER_ENUM_MACRO

} // namespace Komomo::EnumAPI