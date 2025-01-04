#pragma once

#include "Utils/StringUtils.h"
#include "Utils/Using.h"

#include <ll/api/mod/Mod.h>

#include <cstdint>
#include <memory>


#define TRY_PARSE_MACRO(NAME, KEY, TYPE, SCRIPT_TYPE, DEFAULT)                                                         \
    TYPE tryParse##NAME() {                                                                                            \
        try {                                                                                                          \
            if (mRegisterInfo.isEmpty()) return DEFAULT;                                                               \
            auto obj = mRegisterInfo.get();                                                                            \
            if (obj.has(KEY) && !obj.get(KEY).isNull()) {                                                              \
                return ConvertFromScriptX<TYPE>(obj.get(KEY).as##SCRIPT_TYPE());                                       \
            }                                                                                                          \
        } catch (...) {                                                                                                \
            Entry::getInstance()->getLogger().error("Failed to parse " #KEY " from " + mFileName);                     \
        }                                                                                                              \
        return DEFAULT;                                                                                                \
    }

#define CALL_PLUGIN_MACRO(NAME, KEY)                                                                                   \
    void call##NAME() {                                                                                                \
        if (mRegisterInfo.isEmpty()) return;                                                                           \
        auto obj = mRegisterInfo.get();                                                                                \
        if (obj.has(KEY) && obj.get(KEY).isFunction()) {                                                               \
            obj.get(KEY).asFunction().call();                                                                          \
        }                                                                                                              \
    }

namespace Komomo {


struct EngineData {
    uint64_t               mID{uint64_t(-1)};
    string                 mFileName;
    script::Global<Object> mRegisterInfo;

    std::shared_ptr<ll::mod::Mod> mMod{nullptr};

public:
    explicit EngineData(uint64_t engineID) : mID(engineID) {}

public:
    CALL_PLUGIN_MACRO(OnLoad, "onLoad");

    CALL_PLUGIN_MACRO(OnEnable, "onEnable");

    CALL_PLUGIN_MACRO(OnDisable, "onDisable");

public:
    // TRY_PARSE_MACRO(
    //     Name,
    //     "name",
    //     string,
    //     String,
    //     ll::string_utils::toSnakeCase(this->mFileName.substr(0, this->mFileName.find_last_of(".")))
    // );
    // TRY_PARSE_MACRO(Version, "version", string, String, "0.0.0");
    // TRY_PARSE_MACRO(Description, "description", string, String, "");
    // TRY_PARSE_MACRO(Load, "load", endstone::PluginLoadOrder, Number, endstone::PluginLoadOrder::PostWorld);
    // TRY_PARSE_MACRO(Authors, "authors", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(Contributors, "contributors", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(Website, "website", string, String, "");
    // TRY_PARSE_MACRO(Prefix, "prefix", string, String, "");
    // TRY_PARSE_MACRO(Provides, "provides", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(Depend, "depend", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(SoftDepend, "soft_depend", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(LoadBefore, "load_before", std::vector<string>, Array, {});
    // TRY_PARSE_MACRO(
    //     DefaultPermission,
    //     "default_permission",
    //     endstone::PermissionDefault,
    //     Number,
    //     endstone::PermissionDefault::Operator
    // );

public:
    //     void tryParseCommands(JsPluginDescriptionBuilder& jbuilder) {
    //         if (mRegisterInfo.isEmpty()) return;
    //         auto obj = mRegisterInfo.get();
    //         if (!obj.has("commands")) {
    //             return;
    //         }
    //
    //         auto cmds = obj.get("commands").asObject();
    //         auto keys = cmds.getKeyNames();
    //         for (auto& key : keys) {
    //             auto cmdObj  = cmds.get(key).asObject();
    //             auto builder = endstone::detail::CommandBuilder(key);
    //
    //             // 描述
    //             if (cmdObj.has("description")) {
    //                 builder.description(ConvertFromScriptX<string>(cmdObj.get("description")));
    //             }
    //
    //             // 用法
    //             if (cmdObj.has("usages")) {
    //                 auto usages = ConvertFromScriptX<std::vector<string>>(cmdObj.get("usages"));
    //                 for (const auto& usage : usages) {
    //                     builder.usages(usage);
    //                 }
    //             }
    //
    //             // 权限
    //             if (cmdObj.has("permissions")) {
    //                 auto permissions = ConvertFromScriptX<std::vector<string>>(cmdObj.get("permissions"));
    //                 for (const auto& permission : permissions) {
    //                     builder.permissions(permission);
    //                 }
    //             }
    //
    //             jbuilder.commands.emplace(key, std::move(builder));
    //         }
    //     }
    //
    //
    //     void tryParsePermissions(JsPluginDescriptionBuilder& jbuilder) {
    //         if (mRegisterInfo.isEmpty()) return;
    //         auto obj = mRegisterInfo.get();
    //         if (!obj.has("permissions")) {
    //             return;
    //         }
    //
    //         auto perms = obj.get("permissions").asObject();
    //         auto keys  = perms.getKeyNames();
    //         for (auto& key : keys) {
    //             auto permObj = perms.get(key).asObject();
    //             auto builder = endstone::detail::PermissionBuilder(key);
    //
    //             // 设置描述
    //             if (permObj.has("description")) {
    //                 builder.description(ConvertFromScriptX<string>(permObj.get("description")));
    //             }
    //
    //             // 设置默认权限
    //             if (permObj.has("default")) {
    //                 builder.default_(ConvertFromScriptX<endstone::PermissionDefault>(permObj.get("default")));
    //             }
    //
    //             jbuilder.permissions.emplace(key, std::move(builder));
    //         }
    //     }
};


#define ENGINE_DATA() EngineScope::currentEngine()->getData<EngineData>()

#define GET_ENGINE_DATA(engine) engine->getData<EngineData>()

#undef TRY_PARSE_MACRO

#undef CALL_PLUGIN_MACRO

} // namespace Komomo