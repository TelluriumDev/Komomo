#include "ExtraAPI/Config/Config.h"
#include "API/APIHelper.h"
#include "Converter/Convert.h"
#include "nlohmann/json_fwd.hpp"

#include <cstddef>
#include <ll/api/io/FileUtils.h>

#include <fstream>
#include <string>
//
ClassDefine<ConfigClass> configClassBuilder = defineClass<ConfigClass>("Config")
                                                  .constructor(nullptr)

                                                  .function("newConfig", &ConfigClass::newConfig)
                                                  .instanceFunction("get", &ConfigClass::get)
                                                  .instanceFunction("set", &ConfigClass::set)
                                                  .instanceFunction("del", &ConfigClass::del)
                                                  .instanceFunction("has", &ConfigClass::has)
                                                  .instanceFunction("init", &ConfigClass::init)
                                                  .instanceFunction("reload", &ConfigClass::reloadConfig)
                                                  .instanceFunction("getVersion", &ConfigClass::getVersion)
                                                  .build();

ConfigClass::ConfigClass(std::string path) : ScriptClass(ConstructFromCpp<ConfigClass>{}) {
    this->mConfigPath = path;
    if (!fs::exists(path)) {
        mConfig = {
            {"version", 0}
        };
    } else {
        std::ifstream configFile(path);
        configFile >> mConfig;
    }
    flush();
}

ConfigClass::ConfigClass(std::string configPath, ordered_json config) : ScriptClass(ConstructFromCpp<ConfigClass>{}) {
    this->mConfigPath = configPath;
    if (checkHasVersion(config)) this->mConfig = config;
    else {
        config["version"] = 0;
        this->mConfig     = config;
    }
    flush();
}

bool ConfigClass::checkHasVersion(ordered_json config) { return config.contains("version"); }

bool ConfigClass::flush() {
    std::fstream configFile(mConfigPath);
    if (configFile.is_open()) {
        configFile << mConfig;
        configFile.close();
        return true;
    } else {
        ll::file_utils::writeFile(ll::string_utils::str2u8str(mConfigPath), mConfig.dump(4));
    }
    return false;
}

bool ConfigClass::reload() {
    auto jsonTexts = ll::file_utils::readFile(ll::string_utils::str2u8str(mConfigPath));
    if (!jsonTexts) return false;
    try {
        mConfig = ordered_json::parse(*jsonTexts, nullptr, true, true);
    } catch (...) {
        Entry::getInstance().getSelf().getLogger().error("Failed to parse JSON config file: " + mConfigPath);
        return false;
    }
    return true;
}

Local<Object> ConfigClass::newConfig(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Object::newObject());
    CheckArgTypeReturn(args[0], ValueKind::kString, Object::newObject());

    try {
        if (args.size() == 1) {
            return (new ConfigClass(args[0].asString().toString()))->getScriptObject();
        } else if (args.size() == 2) {
            ordered_json config;
            config[args[0].asString().toString()] = ConvertFromScriptX<ordered_json>(args[1]);
            return (new ConfigClass(args[0].asString().toString(), config))->getScriptObject();
        }
    }
    CatchNotReturn;
    return Object::newObject();
}

Local<Value> ConfigClass::get(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        return ConvertToScriptX(mConfig[args[0].asString().toString()]);
    }
    CatchNotReturn;
    return Local<Value>{};
}

Local<Value> ConfigClass::set(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kArray);

    std::vector<std::string> keys = {};
    for (size_t i = 0; i < args[0].asArray().size(); i++) {
        CheckArgType(args[0].asArray().get(i), ValueKind::kString);
        keys.push_back(args[0].asArray().get(i).asString().toString());
    }
    try {
        setNestedValue(mConfig, keys, ConvertFromScriptX<ordered_json>(args[1]));
        flush();
    }
    CatchNotReturn;
    return Local<Value>{};
}

Local<Value> ConfigClass::init(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kArray);

    std::vector<std::string> keys = {};
    for (size_t i = 0; i < args[0].asArray().size(); i++) {
        CheckArgType(args[0].asArray().get(i), ValueKind::kString);
        keys.push_back(args[0].asArray().get(i).asString().toString());
    }

    try {
        if (hasNestedValue(mConfig, keys)) {
            return ConvertToScriptX(mConfig[args[0].asString().toString()]);
        } else {
            setNestedValue(mConfig, keys, ConvertFromScriptX<ordered_json>(args[1]));
            flush();
        }
    }
    CatchNotReturn;
    return Local<Value>{};
}

Local<Value> ConfigClass::has(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kArray, Boolean::newBoolean(false));

    std::vector<std::string> keys = {};
    for (size_t i = 0; i < args[0].asArray().size(); i++) {
        CheckArgType(args[0].asArray().get(i), ValueKind::kString);
        keys.push_back(args[0].asArray().get(i).asString().toString());
    }

    try {
        return Boolean::newBoolean(hasNestedValue(mConfig, keys));
    } catch (const std::out_of_range& e) {
        PrintScriptError("Error in has config: " + std::string(e.what()));
        return Local<Value>();
    }
}

Local<Value> ConfigClass::del(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kArray);

    std::vector<std::string> keys = {};
    for (size_t i = 0; i < args[0].asArray().size(); i++) {
        CheckArgType(args[0].asArray().get(i), ValueKind::kString);
        keys.push_back(args[0].asArray().get(i).asString().toString());
    }
    try {
        delNestedValue(mConfig, keys);
        flush();
    } catch (const std::out_of_range& e) {
        PrintScriptError(e.what());
        return Local<Value>();
    }
    return Local<Value>();
}

Local<Value> ConfigClass::reloadConfig(const Arguments& args) { return Boolean::newBoolean(reload()); }

Local<Value> ConfigClass::getVersion(const Arguments& args) { return ConvertToScriptX(mConfig["version"]); }