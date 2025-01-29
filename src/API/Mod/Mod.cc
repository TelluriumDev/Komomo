#include "API/Mod/Mod.h"
#include "API/Logger/Logger.h"

#include <filesystem>

using namespace Komomo;

ClassDefine<ModClass> modClassBuilder = defineClass<ModClass>("Mod")
                                            .constructor(nullptr)

                                            .function("getName", &ModClass::getName)
                                            .function("getType", &ModClass::getType)
                                            .function("getModDir", &ModClass::getModDir)
                                            .function("getDataDir", &ModClass::getDataDir)
                                            .function("getConfigDir", &ModClass::getConfigDir)
                                            .function("getLangDir", &ModClass::getLangDir)
                                            .function("getLogger", &ModClass::getLogger)
                                            .function("getRootDir", &ModClass::getRootDir)
                                            .function("getModRootDir", &ModClass::getModRootDir)

                                            .build();

ModClass::ModClass() : ScriptClass(ConstructFromCpp<ModClass>{}) {}

std::shared_ptr<ll::mod::Mod> ModClass::getMod() { return ENGINE_DATA()->mMod; };


// LLNDAPI std::string const& getName() const;
Local<Value> ModClass::getName() { return String::newString(ENGINE_DATA()->mMod->getName()); };

// LLNDAPI std::string const& getType() const;
Local<Value> ModClass::getType() { return String::newString(ENGINE_DATA()->mMod->getType()); };

// LLNDAPI std::filesystem::path const& getModDir() const;
Local<Value> ModClass::getModDir() { return String::newString(ENGINE_DATA()->mMod->getModDir().string()); };

// LLNDAPI std::filesystem::path const& getDataDir() const;
Local<Value> ModClass::getDataDir() { return String::newString(ENGINE_DATA()->mMod->getDataDir().string()); };

// LLNDAPI std::filesystem::path const& getConfigDir() const;
Local<Value> ModClass::getConfigDir() { return String::newString(ENGINE_DATA()->mMod->getConfigDir().string()); };

// LLNDAPI std::filesystem::path const& getLangDir() const;
Local<Value> ModClass::getLangDir() { return String::newString(ENGINE_DATA()->mMod->getLangDir().string()); };

// LLNDAPI ll::io::Logger& getLogger() const;
Local<Value> ModClass::getLogger() { return LoggerClass::newLoggerClass(ENGINE_DATA()->mMod->getLogger().getTitle()); };

Local<Value> ModClass::getRootDir() { return String::newString(fs::current_path().string()); }

Local<Value> ModClass::getModRootDir() { return String::newString(ll::mod::getModsRoot().string()); }