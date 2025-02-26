#include "API/Enum/EnumBuilder.h"
#include "API/Enum/EnumInclude.h"


#include <string>
#include <unordered_map>


#define REGISTER_ENUM_MACRO(NAMESPACE, ENUM, NAME)                                                                     \
    for (auto [value, key] : magic_enum::enum_entries<ENUM>()) {                                                       \
        NAMESPACE[NAME][key] = static_cast<int>(value);                                                                \
    }

namespace Komomo::EnumAPI {

    void RegisterEnum(ScriptEngine *engine) {
        // Actor
        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> ActorEnum;
//     REGISTER_ENUM_MACRO(ActorEnum, ActionEvent::<unnamed>, "ActionEvent")
//    REGISTER_ENUM_MACRO(ActorEnum, ActionEvent::ActionState, "ActionState");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorDamageCause, "ActorDamageCause");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorCategory, "ActorCategory");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorDataIDs, "ActorDataIDs");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionEventType, "ActorDefinitionEventType");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionGroup::LoadStatus, "LoadStatus");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorDefinitionParseStatus, "ActorDefinitionParseStatus");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorEvent, "ActorEvent");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorFilterGroup::Processing, "Processing");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorFlags, "ActorFlags");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorInitializationMethod, "ActorInitialzationMethod");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorLinkType, "ActorLinkType");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorLocation, "ActorLocation");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorTargetFilter::ConditionType, "ConditionType");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorTerrainInterlockData::VisibilityState, "VisibilityState");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorType, "ActorType");
//    REGISTER_ENUM_MACRO(ActorEnum, ActorTypeNamespaceRules, "ActorTypeNamespaceRules");
//    REGISTER_ENUM_MACRO(ActorEnum, ArmorMaterialType, "ArmorMaterialType");
//    REGISTER_ENUM_MACRO(ActorEnum, ArmorTextureType, "ArmorTextureType");
//    REGISTER_ENUM_MACRO(ActorEnum, DataItemType, "DataItemType");
//    REGISTER_ENUM_MACRO(ActorEnum, DefinitionEventType, "DefinitionEventType");
//    REGISTER_ENUM_MACRO(ActorEnum, HorseInventoryEnum, "HorseInventoryEnum");
//    REGISTER_ENUM_MACRO(ActorEnum, KeyOrNameResult::ResultType, "ResultType");
//    REGISTER_ENUM_MACRO(ActorEnum, MobSpawnMethod, "MobSpawnMethod");
//    REGISTER_ENUM_MACRO(ActorEnum, PaletteColor, "PaletteColor");
//    REGISTER_ENUM_MACRO(ActorEnum, ParticleType, "ParticleType");
//    REGISTER_ENUM_MACRO(ActorEnum, RenderContextType, "RenderContextType");
//    REGISTER_ENUM_MACRO(ActorEnum, RenderParam, "RenderParam");
//    REGISTER_ENUM_MACRO(ActorEnum, SerializedAbilitiesData::SerializedAbilitiesLayer, "SerializedAbilitiesLayer");
//    REGISTER_ENUM_MACRO(ActorEnum, SkeletalHierarchyIndex, "SkeletalHierarchyIndex");
//    REGISTER_ENUM_MACRO(ActorEnum, SpawnRuleEnum, "SpawnRuleEnum");
//    REGISTER_ENUM_MACRO(ActorEnum, TravelType, "TravelType");
//    REGISTER_ENUM_MACRO(ActorEnum, TypeExecutingEvent, "TypeExecutingEvent");
        engine->set("ActorEnum", ConvertToScriptX(ActorEnum));

        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> CommandEnum;
//    REGISTER_ENUM_MACRO(CommandEnum, AllowListCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, BlockStateCommandParam::Type, "Type");
//    REGISTER_ENUM_MACRO(CommandEnum, ChangeSettingCommand::Setting, "Setting");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandAsyncFlag, "CommandAsyncFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandBlockNameResult::Result, "Result");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandCheatFlag, "CommandCheatFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandCompareOperator, "CommandCompareOperator");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandEditorFlag, "CommandEditorFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandExecuteFlag, "CommandExecuteFlag");
        REGISTER_ENUM_MACRO(CommandEnum, CommandFlagValue, "CommandFlagValue");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandLexer::TokenType, "TokenType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandOperator, "CommandOperator");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandOriginType, "CommandOriginType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandOutputMessageType, "CommandOutputMessageType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandOutputParameter::NoCountType, "NoCountType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandOutputType, "CommandOutputType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandParameterDataType, "CommandParameterDataType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandParameterOption, "CommandParameterOption");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandPermissionLevel, "CommandPermissionLevel");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandRationalRange::BoundType, "BoundType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandRationalRange::ValueType, "ValueType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandSelectionOrder, "CommandSelectionOrder");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandSelectionType, "CommandSelectionType");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandStatus, "CommandStatus");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandSyncFlag, "CommandSyncFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandTypeFlag, "CommandTypeFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandUsageFlag, "CommandUsageFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CommandVisibilityFlag, "CommandVisibilityFlag");
//    REGISTER_ENUM_MACRO(CommandEnum, CurrentCmdVersion, "CurrentCmdVersion");
//    REGISTER_ENUM_MACRO(CommandEnum, PlayerPermissionLevel, "PlayerPermissionLevel");
//    REGISTER_ENUM_MACRO(CommandEnum, SaveCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, SaveCommand::State, "State");
//    REGISTER_ENUM_MACRO(CommandEnum, SemanticConstraint, "SemanticConstraint");
//    REGISTER_ENUM_MACRO(CommandEnum, ProjectCommand::Subcommand, "Subcommand");
//    REGISTER_ENUM_MACRO(CommandEnum, ProjectCommand::ExportSubcommandTypes, "ExportSubcommandTypes");
//    REGISTER_ENUM_MACRO(CommandEnum, ProjectCommand::TaskState, "TaskState");
//    REGISTER_ENUM_MACRO(CommandEnum, AgentCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, AgentCommand::FacingResult, "FacingResult");
//    REGISTER_ENUM_MACRO(CommandEnum, CodeBuilderActorInfoCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, CodeBuilderCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, CodeBuilderCommand::CommandKeyword, "CommandKeyword");
//    REGISTER_ENUM_MACRO(CommandEnum, CodeBuilderCommand::SubscriptionType, "SubscriptionType");
//    REGISTER_ENUM_MACRO(CommandEnum, CodeBuilderCommand::CodeBuilderRuntimeAction, "CodeBuilderRuntimeAction");
//    REGISTER_ENUM_MACRO(CommandEnum, DialogueCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, LessonActionType, "LessonActionType");
//    REGISTER_ENUM_MACRO(CommandEnum, ResourceUriCommand::ActionType, "ActionType");
//    REGISTER_ENUM_MACRO(CommandEnum, AgentCommands::SubCommand, "SubCommand");
//    REGISTER_ENUM_MACRO(CommandEnum, FunctionQueueOrder, "FunctionQueueOrder");
//    REGISTER_ENUM_MACRO(CommandEnum, FunctionState, "FunctionState");
//    REGISTER_ENUM_MACRO(CommandEnum, ScriptDebugCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, ScriptDebugCommand::DebuggerAction, "DebuggerAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ScriptDebugCommand::ProfilerAction, "ProfilerAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ScriptDebugCommand::WatchdogAction, "WatchdogAction");
//    REGISTER_ENUM_MACRO(CommandEnum, BossbarCommand::BossbarAction, "BossbarAction");
//    REGISTER_ENUM_MACRO(CommandEnum, BossbarCommand::BossbarGetOption, "BossbarGetOption");
//    REGISTER_ENUM_MACRO(CommandEnum, BossbarCommand::BossbarSetOption, "BossbarSetOption");
//    REGISTER_ENUM_MACRO(CommandEnum, CameraAimAssistCommand::TargetMode, "TargetMode");
//    REGISTER_ENUM_MACRO(CommandEnum, CameraAimAssistCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, CameraCommand::CameraCommandOption, "CameraCommandOption");
//    REGISTER_ENUM_MACRO(CommandEnum, CloneCommand::MaskMode, "MaskMode");
//    REGISTER_ENUM_MACRO(CommandEnum, CloneCommand::CloneMode, "CloneMode");
//    REGISTER_ENUM_MACRO(CommandEnum, DamageCommand::DamageOrigin, "DamageOrigin");
//    REGISTER_ENUM_MACRO(CommandEnum, EffectCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, EventCommand::EventAction, "EventAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ExecuteCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, FillCommand::FillMode, "FillMode");
//    REGISTER_ENUM_MACRO(CommandEnum, FogCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, GameTestCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, HudOptions, "HudOptions");
//    REGISTER_ENUM_MACRO(CommandEnum, InputPermissionCommand::CommandActionType, "CommandActionType");
//    REGISTER_ENUM_MACRO(CommandEnum, InputPermissionCommand::CommandValueType, "CommandValueType");
//    REGISTER_ENUM_MACRO(CommandEnum, ListDCommand::DetailMode, "DetailMode");
//    REGISTER_ENUM_MACRO(CommandEnum, LocateSubcommand, "LocateSubcommand");
//    REGISTER_ENUM_MACRO(CommandEnum, LootCommand::Target, "Target");
//    REGISTER_ENUM_MACRO(CommandEnum, LootCommand::TargetIdentifier, "TargetIdentifier");
//    REGISTER_ENUM_MACRO(CommandEnum, LootCommand::Source, "Source");
//    REGISTER_ENUM_MACRO(CommandEnum, MusicCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, NewExecuteCommand::ExecuteChainedSubcommand::Subcommand, "Subcommand");
//    REGISTER_ENUM_MACRO(
//        CommandEnum,
//        NewExecuteCommand::ExecuteChainedSubcommand::ConditionSubcommand,
//        "ConditionSubcommand"
//    );
//    REGISTER_ENUM_MACRO(CommandEnum, NewExecuteCommand::ExecuteChainedSubcommand::ScanMode, "ScanMode");
//    REGISTER_ENUM_MACRO(CommandEnum, NewExecuteCommand::ExecuteChainedSubcommand::ScoreRangeMode, "ScoreRangeMode");
//    REGISTER_ENUM_MACRO(CommandEnum, PermissionCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(
//        CommandEnum,
//        PermissionCommand::AvailableCommandPermissionPresets,
//        "AvailableCommandPermissionPresets"
//    );
//    REGISTER_ENUM_MACRO(CommandEnum, PlaceCommand::PlaceAction, "PlaceAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ReloadCommand::ReloadAction, "ReloadAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ReplaceItemCommand::ReplaceMode, "ReplaceMode");
//    REGISTER_ENUM_MACRO(CommandEnum, ReplaceItemCommand::TargetType, "TargetType");
//    REGISTER_ENUM_MACRO(CommandEnum, RideCommand::VehicleAction, "VehicleAction");
//    REGISTER_ENUM_MACRO(CommandEnum, RideCommand::TeleportRules, "TeleportRules");
//    REGISTER_ENUM_MACRO(CommandEnum, RideCommand::VehicleFillType, "VehicleFillType");
//    REGISTER_ENUM_MACRO(CommandEnum, RideCommand::RideRules, "RideRules");
//    REGISTER_ENUM_MACRO(CommandEnum, ScheduleCommand::ScheduleAction, "ScheduleAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ScheduleCommand::RequestAction, "RequestAction");
//    REGISTER_ENUM_MACRO(CommandEnum, ScheduleCommand::DelayMode, "DelayMode");
//    REGISTER_ENUM_MACRO(CommandEnum, ScheduleCommand::ClearType, "ClearType");
//    REGISTER_ENUM_MACRO(CommandEnum, ScoreboardCommand::Category, "Category");
//    REGISTER_ENUM_MACRO(CommandEnum, ScoreboardCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, SetBlockCommand::SetBlockMode, "SetBlockMode");
//    REGISTER_ENUM_MACRO(CommandEnum, StructureActionType, "StructureActionType");
//    REGISTER_ENUM_MACRO(CommandEnum, TagCommand::Action, "Action");
//    REGISTER_ENUM_MACRO(CommandEnum, TeleportAnalysis, "TeleportAnalysis");
//    REGISTER_ENUM_MACRO(CommandEnum, TestForBlocksCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, TickingAreaCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, TickingAreaCommand::AddAreaType, "AddAreaType");
//    REGISTER_ENUM_MACRO(CommandEnum, TickingAreaCommand::TargetDimensions, "TargetDimensions");
//    REGISTER_ENUM_MACRO(CommandEnum, TimeCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, TimeCommand::Query, "Query");
//    REGISTER_ENUM_MACRO(CommandEnum, TimeCommand::TimeSpec, "TimeSpec");
//    REGISTER_ENUM_MACRO(CommandEnum, TitleCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, TitleRawCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, UnlockRecipeCommand::RecipeAction, "RecipeAction");
//    REGISTER_ENUM_MACRO(CommandEnum, VolumeAreaCommand::Mode, "Mode");
//    REGISTER_ENUM_MACRO(CommandEnum, VolumeAreaCommand::TargetDimensions, "TargetDimensions");
//    REGISTER_ENUM_MACRO(CommandEnum, WeatherCommand::WeatherType, "WeatherType");
//    REGISTER_ENUM_MACRO(CommandEnum, WeatherCommand::WeatherRequest, "WeatherRequest");
        REGISTER_ENUM_MACRO(CommandEnum, ll::command::ParamKind::Kind, "ParamKindKind");
        engine->set("CommandEnum", ConvertToScriptX(CommandEnum));

        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> CommonEnum;
        // REGISTER_ENUM_MACRO(CommonEnum, CompactionStatus, "CompactionStatus");
        // REGISTER_ENUM_MACRO(CommonEnum, FacingID, "FacingID");
        // REGISTER_ENUM_MACRO(CommonEnum, GameUserType, "GameUserType");
        // REGISTER_ENUM_MACRO(CommonEnum, GameVersion::Octet, "Octet");
        // REGISTER_ENUM_MACRO(CommonEnum, SubClientId, "SubClientId");
        // REGISTER_ENUM_MACRO(CommonEnum, XforgeGameVersion::Octet, "Octet");
        // REGISTER_ENUM_MACRO(CommonEnum, Editor::WorldType, "WorldType");
        // REGISTER_ENUM_MACRO(CommonEnum, Facing::Axis, "Axis");
        // REGISTER_ENUM_MACRO(CommonEnum, Facing::Name, "Name");
        // REGISTER_ENUM_MACRO(CommonEnum, Facing::Rotation, "Rotation");
        // REGISTER_ENUM_MACRO(CommonEnum, TitleInfo::TitleId, "TitleId");
        engine->set("CommonEnum", ConvertToScriptX(CommonEnum));

        // Block
        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> BlockEnum;
//    REGISTER_ENUM_MACRO(BlockEnum, BlockActorType, "BlockActorType");
//    REGISTER_ENUM_MACRO(BlockEnum, BlockSupportType, "BlockSupportType");
//    REGISTER_ENUM_MACRO(BlockEnum, BlockTintType, "BlockTintType");
//    REGISTER_ENUM_MACRO(BlockEnum, BlockProperty, "BlockProperty");
//    REGISTER_ENUM_MACRO(BlockEnum, BlockRenderLayer, "BlockRenderLayer");
//    REGISTER_ENUM_MACRO(BlockEnum, MaterialType, "MaterialType");
        engine->set("BlockEnum", ConvertToScriptX(BlockEnum));

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
//    REGISTER_ENUM_MACRO(ItemEnum, ArmorSlot, "ArmorSlot");
//    REGISTER_ENUM_MACRO(ItemEnum, BannerPatternItem::Type, "Type");
//    REGISTER_ENUM_MACRO(ItemEnum, BucketFillType, "BucketFillType");
//    REGISTER_ENUM_MACRO(ItemEnum, CameraItemComponentLegacy::UseAction, "UseAction");
//    REGISTER_ENUM_MACRO(ItemEnum, CoalItem::Type, "Type");
//    REGISTER_ENUM_MACRO(ItemEnum, CompoundContainerType, "CompoundContainerType");
//    REGISTER_ENUM_MACRO(ItemEnum, CompoundType, "CompoundType");
//    REGISTER_ENUM_MACRO(ItemEnum, CreativeItemCategory, "CreativeItemCategory");
//    REGISTER_ENUM_MACRO(ItemEnum, FertilizerType, "FertilizerType");
//    REGISTER_ENUM_MACRO(ItemEnum, FireworkChargeItem::Shape, "Shape");
//    REGISTER_ENUM_MACRO(ItemEnum, FoodItemComponentLegacy::OnUseAction, "OnUseAction");
//    REGISTER_ENUM_MACRO(ItemEnum, HandSlot, "HandSlot");
//    REGISTER_ENUM_MACRO(ItemEnum, HorseArmorItem::Tier, "Tier");
//    REGISTER_ENUM_MACRO(ItemEnum, HumanoidArmorItem::Tier, "Tier");
//    REGISTER_ENUM_MACRO(ItemEnum, InHandUpdateType, "InHandUpdateType");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemAcquisitionMethod, "ItemAcquisitionMethod");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemColor, "ItemColor");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemCommandVisibility, "ItemCommandVisibility");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemContextType, "ItemContextType");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemDescriptor::InternalType, "InternalType");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemIconInfoType, "ItemIconInfoType");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemLockMode, "ItemLockMode");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemUseMethod, "ItemUseMethod");
//    REGISTER_ENUM_MACRO(ItemEnum, MapType, "MapType");
//    REGISTER_ENUM_MACRO(ItemEnum, MedicineType, "MedicineType");
//    REGISTER_ENUM_MACRO(ItemEnum, NotifyItemUsedOnEvent, "NotifyItemUsedOnEvent");
//    REGISTER_ENUM_MACRO(ItemEnum, PageContent::PageType, "PageType");
//    REGISTER_ENUM_MACRO(ItemEnum, Rarity, "Rarity");
//    REGISTER_ENUM_MACRO(ItemEnum, SaveContext::SaveUseCase, "SaveUseCase");
//    REGISTER_ENUM_MACRO(ItemEnum, SaveContext::SaveOperation, "SaveOperation");
//    REGISTER_ENUM_MACRO(ItemEnum, SlotWithDropChance, "SlotWithDropChance");
//    REGISTER_ENUM_MACRO(ItemEnum, SmithingTemplateItem::UpgradeType, "UpgradeType");
//    REGISTER_ENUM_MACRO(ItemEnum, SuspiciousStewItem::SuspiciousStewType, "SuspiciousStewType");
//    REGISTER_ENUM_MACRO(ItemEnum, Potion::PotionType, "PotionType");
//    REGISTER_ENUM_MACRO(ItemEnum, Potion::PotionVariant, "PotionVariant");
//    REGISTER_ENUM_MACRO(ItemEnum, OnUseOrder, "OnUseOrder");
//    REGISTER_ENUM_MACRO(ItemEnum, RenderOffsetsItemComponent::Hand, "Hand");
//    REGISTER_ENUM_MACRO(ItemEnum, RenderOffsetsItemComponent::Perspective, "Perspective");
//    REGISTER_ENUM_MACRO(ItemEnum, UseTimeDepletedOrder, "UseTimeDepletedOrder");
//    REGISTER_ENUM_MACRO(ItemEnum, RecipeUnlockingRequirement::UnlockingContext, "UnlockingContext");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Type, "Type");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Frequency, "Frequency");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Slot, "Slot");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::Activation, "Activation");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::CompatibilityID, "CompatibilityID");
//    REGISTER_ENUM_MACRO(ItemEnum, Enchant::VillagerTrading, "VillagerTrading");
//    REGISTER_ENUM_MACRO(ItemEnum, EnchantResultType, "EnchantResultType");
//    REGISTER_ENUM_MACRO(ItemEnum, EquipmentFilter, "EquipmentFilter");
//    REGISTER_ENUM_MACRO(ItemEnum, ItemVersion, "ItemVersion");
        engine->set("ItemEnum", ConvertToScriptX(ItemEnum));

        // auto generated InventoryEnum
        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> InventoryEnum;
//    REGISTER_ENUM_MACRO(InventoryEnum, ActorContainerType, "ActorContainerType");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventoryLayout, "InventoryLayout");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventoryLeftTabIndex, "InventoryLeftTabIndex");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventoryRightTabIndex, "InventoryRightTabIndex");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackNetManagerServer::TextFilterState, "TextFilterState");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackNetResult, "ItemStackNetResult");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionHandler::RemoveType, "RemoveType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionMineBlock::PreValidationStatus, "PreValidationStatus");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestActionType, "ItemStackRequestActionType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemStackRequestScreen, "ItemStackRequestScreen");
//    REGISTER_ENUM_MACRO(InventoryEnum, SparseContainerClient::PushSlotPredictionResult, "PushSlotPredictionResult");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenActionResultData::Type, "Type");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenAutoplaceBehaviour, "ContainerScreenAutoplaceBehaviour");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenRequestActionType, "ContainerScreenRequestActionType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerScreenTransferBehaviour, "ContainerScreenTransferBehaviour");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationCaller, "ContainerValidationCaller");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationCommitObject::Type, "Type");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationOperationType, "ContainerValidationOperationType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ContainerValidationOutcome, "ContainerValidationOutcome");
//    REGISTER_ENUM_MACRO(InventoryEnum, SparseContainerBackingSetType, "SparseContainerBackingSetType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ComplexInventoryTransaction::Type, "Type");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventorySource::InventorySourceFlags, "InventorySourceFlags");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventorySourceType, "InventorySourceType");
//    REGISTER_ENUM_MACRO(InventoryEnum, InventoryTransactionError, "InventoryTransactionError");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemReleaseInventoryTransaction::ActionType, "ActionType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::ActionType, "ActionType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::TriggerType, "TriggerType");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseInventoryTransaction::PredictedResult, "PredictedResult");
//    REGISTER_ENUM_MACRO(InventoryEnum, ItemUseOnActorInventoryTransaction::ActionType, "ActionType");
        engine->set("InventoryEnum", ConvertToScriptX(InventoryEnum));

        // Form
        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> FormEnum;
        REGISTER_ENUM_MACRO(FormEnum, ModalFormCancelReason, "ModalFormCancelResult");
        engine->set("FormEnum", ConvertToScriptX(FormEnum));

        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> EventEnum = []() {
            std::unordered_map<std::string, std::unordered_map<std::string_view, int>> map;
            REGISTER_ENUM_MACRO(EventEnum, ll::event::EventPriority, "EventPriority");
            map["EventPriority"]["Highest"] = 0;
            map["EventPriority"]["High"] = 100;
            map["EventPriority"]["Normal"] = 200;
            map["EventPriority"]["Low"] = 300;
            map["EventPriority"]["Lowest"] = 400;
            return map;
        }();

        engine->set("EventEnum", ConvertToScriptX(EventEnum));

        static std::unordered_map<std::string, std::unordered_map<std::string_view, int>> LoggerEnum;
        REGISTER_ENUM_MACRO(LoggerEnum, ll::io::LogLevel, "LogLevel");
        engine->set("LoggerEnum", ConvertToScriptX(LoggerEnum));
    }

#undef REGISTER_ENUM_MACRO

} // namespace Komomo::EnumAPI