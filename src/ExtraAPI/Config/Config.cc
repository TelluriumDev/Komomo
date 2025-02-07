#include "ExtraAPI/Config/Config.h"

#include <ll/api/io/FileUtils.h>

#include <fstream>
#include <string>

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

Local<Value> BigInteger_Helper(ordered_json &i) {
    if (i.is_number_integer()) {
        if (i.is_number_unsigned()) {
            auto ui = i.get<uint64_t>();
            if (ui <= LLONG_MAX) return Number::newNumber((int64_t) ui);
            return Number::newNumber((double) ui);
        }
        return Number::newNumber(i.get<int64_t>());
    }
    return Local<Value>();
}

void JsonToValue_Helper(Local<Array> &res, ordered_json &j);

void JsonToValue_Helper(Local<Object> &res, const string &key, ordered_json &j) {
    switch (j.type()) {
        case ordered_json::value_t::string:
            res.set(key, String::newString(j.get<string>()));
            break;
        case ordered_json::value_t::number_integer:
        case ordered_json::value_t::number_unsigned:
            res.set(key, BigInteger_Helper(j));
            break;
        case ordered_json::value_t::number_float:
            res.set(key, Number::newNumber(j.get<double>()));
            break;
        case ordered_json::value_t::boolean:
            res.set(key, Boolean::newBoolean(j.get<bool>()));
            break;
        case ordered_json::value_t::null:
            res.set(key, Local<Value>());
            break;
        case ordered_json::value_t::array: {
            Local<Array> arrToAdd = Array::newArray();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it) JsonToValue_Helper(arrToAdd, *it);
            res.set(key, arrToAdd);
            break;
        }
        case ordered_json::value_t::object: {
            Local<Object> objToAdd = Object::newObject();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it)
                JsonToValue_Helper(objToAdd, it.key(), it.value());
            res.set(key, objToAdd);
            break;
        }
        default:
            res.set(key, Local<Value>());
            break;
    }
}

void JsonToValue_Helper(Local<Array> &res, ordered_json &j) {
    switch (j.type()) {
        case ordered_json::value_t::string:
            res.add(String::newString(j.get<string>()));
            break;
        case ordered_json::value_t::number_integer:
        case ordered_json::value_t::number_unsigned:
            res.add(BigInteger_Helper(j));
            break;
        case ordered_json::value_t::number_float:
            res.add(Number::newNumber(j.get<double>()));
            break;
        case ordered_json::value_t::boolean:
            res.add(Boolean::newBoolean(j.get<bool>()));
            break;
        case ordered_json::value_t::null:
            res.add(Local<Value>());
            break;
        case ordered_json::value_t::array: {
            Local<Array> arrToAdd = Array::newArray();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it) JsonToValue_Helper(arrToAdd, *it);
            res.add(arrToAdd);
            break;
        }
        case ordered_json::value_t::object: {
            Local<Object> objToAdd = Object::newObject();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it)
                JsonToValue_Helper(objToAdd, it.key(), it.value());
            res.add(objToAdd);
            break;
        }
        default:
            res.add(Local<Value>());
            break;
    }
}

Local<Value> JsonToValue(ordered_json j) {
    Local<Value> res;

    switch (j.type()) {
        case ordered_json::value_t::string:
            res = String::newString(j.get<string>());
            break;
        case ordered_json::value_t::number_integer:
        case ordered_json::value_t::number_unsigned:
            res = BigInteger_Helper(j);
            break;
        case ordered_json::value_t::number_float:
            res = Number::newNumber(j.get<double>());
            break;
        case ordered_json::value_t::boolean:
            res = Boolean::newBoolean(j.get<bool>());
            break;
        case ordered_json::value_t::null:
            res = Local<Value>();
            break;
        case ordered_json::value_t::array: {
            Local<Array> resArr = Array::newArray();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it) JsonToValue_Helper(resArr, *it);
            res = resArr;
            break;
        }
        case ordered_json::value_t::object: {
            Local<Object> resObj = Object::newObject();
            for (ordered_json::iterator it = j.begin(); it != j.end(); ++it)
                JsonToValue_Helper(resObj, it.key(), it.value());
            res = resObj;
            break;
        }
        default:
            res = Local<Value>();
            break;
    }

    return res;
}

Local<Value> JsonToValue(std::string jsonStr) {
    try {
        if (jsonStr.empty()) return String::newString("");
        if (jsonStr.front() == '\"' && jsonStr.back() == '\"')
            return String::newString(jsonStr.substr(1, jsonStr.size() - 2));
        auto j = ordered_json::parse(jsonStr, nullptr, true, true);
        return JsonToValue(j);
    } catch (const ordered_json::exception &e) {
        Komomo::Entry::getInstance().getSelf().getLogger().warn(
                "{}{}",
                "JSON parse error",
                ll::string_utils::tou8str(e.what())
        );
        return String::newString(jsonStr);
    }
}


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
        return JsonToValue(mConfig[args[0].asString().toString()]);
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
            // return (new ConfigClass(this->mConfigPath, mConfig[args[0].asString().toString()]))->getScriptObject();
        } else if (args.size() == 2) {
            mConfig[args[0].asString().toString()] = ordered_json::parse(ConvertFromScriptX<std::string>(args[1]));
            flush();
        }
    } catch (const std::out_of_range& e) {
        PrintScriptError("Error in set config");
        return Local<Value>();
    }
    return Local<Value>();
}

Local<Value> ConfigClass::init(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    try {
        if (!has(args).asBoolean().value()) {
            mConfig[args[0].asString().toString()] = ordered_json::parse(ConvertFromScriptX<std::string>(args[1]));
            flush();
        } else {
            return JsonToValue(mConfig[args[0].asString().toString()]);
        }
    } catch (const std::out_of_range& e) {
        PrintScriptError("Error in init config");
        return Local<Value>();
    }
    return Local<Value>();
}

Local<Value> ConfigClass::has(const Arguments& args) {
    CheckArgsCountReturn(args, 1, Boolean::newBoolean(false));
    CheckArgTypeReturn(args[0], ValueKind::kString, Boolean::newBoolean(false));
    return Boolean::newBoolean(mConfig.contains(args[0].asString().toString()));
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

Local<Value> ConfigClass::getVersion(const Arguments &args) { return JsonToValue(mConfig["version"]); }