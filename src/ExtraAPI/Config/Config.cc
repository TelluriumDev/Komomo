#include "ExtraAPI/Config/Config.h"

#include <ll/api/io/FileUtils.h>

#include <fstream>

ClassDefine<ConfigClass> configClassBuilder = defineClass<ConfigClass>("Config")
                                                  .constructor(nullptr)

                                                  .function("newConfig", &ConfigClass::newConfig)
                                                  .instanceFunction("get", &ConfigClass::get)
                                                  .instanceFunction("set", &ConfigClass::set)
                                                  .instanceFunction("del", &ConfigClass::del)
                                                  .instanceFunction("reload", &ConfigClass::reloadConfig)
                                                  .instanceFunction("getVersion", &ConfigClass::getVersion)

                                                  .build();

ConfigClass::ConfigClass(std::string path) : ScriptClass(ConstructFromCpp<ConfigClass>{}) {
    this->mConfigPath = path;
    mConfig           = {
        {"version", 0}
    };
    flush();
}

ConfigClass::ConfigClass(std::string configPath, ordered_json config) : ScriptClass(ConstructFromCpp<ConfigClass>{}) {
    this->mConfigPath = configPath;
    if (checkHasVerion(config)) this->mConfig = config;
    else {
        config["version"] = 0;
        this->mConfig     = config;
    }
    flush();
}


bool ConfigClass::checkHasVerion(ordered_json config) { return config.contains("version"); }

bool ConfigClass::flush() {
    std::fstream configFile(mConfigPath);
    if (configFile.is_open()) {
        configFile << mConfig;
        configFile.close();
        return true;
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
            config[args[0].asString().toString()] = ordered_json::parse(ConvertFromScriptX<std::string>(args[1]));
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
        return ConvertToScriptX(mConfig.at(args[0].asString().toString()));
    } catch (const std::out_of_range& e) {
        PrintScriptError("Key not found in config: " + args[0].asString().toString());
        return Local<Value>();
    }
}

Local<Value> ConfigClass::set(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (args.size() == 1) {
            return (new ConfigClass(this->mConfigPath, mConfig[args[0].asString().toString()]))->getScriptObject();
        } else if (args.size() == 2) {
            mConfig[args[0].asString().toString()] = ordered_json::parse(ConvertFromScriptX<std::string>(args[1]));
            flush();
        }
    } catch (const std::out_of_range& e) {
        PrintScriptError("Key not found in config: " + args[0].asString().toString());
        return Local<Value>();
    }
    return Local<Value>();
}

Local<Value> ConfigClass::del(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        mConfig.erase(args[0].asString().toString());
        flush();
    } catch (const std::out_of_range& e) {
        PrintScriptError("Key not found in config: " + args[0].asString().toString());
        return Local<Value>();
    }
    return Local<Value>();
}

Local<Value> ConfigClass::reloadConfig(const Arguments& args) { return Boolean::newBoolean(reload()); }

Local<Value> ConfigClass::getVersion(const Arguments& args) { return ConvertToScriptX(mConfig["version"]); }