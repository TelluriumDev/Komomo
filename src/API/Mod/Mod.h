#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/mod/Mod.h>
#include <memory>

class ModClass : public ScriptClass {
public:
    
    ModClass();
public: /* Method */
    // LLNDAPI State getState() const; // TODO
    // LLNDAPI Manifest const& getManifest() const; // TODO
    static inline std::shared_ptr<ll::mod::Mod> getMod();

    // LLNDAPI std::string const& getName() const;
    static Local<Value> getName();

    // LLNDAPI std::string const& getType() const;
    static Local<Value> getType();

    // LLNDAPI std::filesystem::path const& getModDir() const;
    static Local<Value> getModDir();

    // LLNDAPI std::filesystem::path const& getDataDir() const;
    static Local<Value> getDataDir();

    // LLNDAPI std::filesystem::path const& getConfigDir() const;
    static Local<Value> getConfigDir();

    // LLNDAPI std::filesystem::path const& getLangDir() const;
    static Local<Value> getLangDir();

    // LLNDAPI ll::io::Logger& getLogger() const;
    static Local<Value> getLogger();

    static Local<Value> getRootDir();

    static Local<Value> getModRootDir();

    static Local<Value> onLoad(const Arguments &args);

    static Local<Value> onEnable(const Arguments &args);

    static Local<Value> onDisable(const Arguments &args);

    static Local<Value> onUnload(const Arguments &args);

};

extern ClassDefine<ModClass> modClassBuilder;