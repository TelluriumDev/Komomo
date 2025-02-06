#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <nlohmann/json.hpp>

using namespace nlohmann;

class ConfigClass : public ScriptClass {
    std::string  mConfigPath;
    ordered_json mConfig;

    bool flush();
    bool reload();
    bool checkHasVerion(ordered_json json);

public:
    ConfigClass(std::string path);
    ConfigClass(std::string configPath, ordered_json config);

    static Local<Object> newConfig(const Arguments& args);

    Local<Value> get(const Arguments& args);

    Local<Value> set(const Arguments& args);

    Local<Value> init(const Arguments& args);

    Local<Value> del(const Arguments& args);

    Local<Value> has(const Arguments& args);

    Local<Value> reloadConfig(const Arguments& args);

    Local<Value> getVersion(const Arguments& args);
};

extern ClassDefine<ConfigClass> configClassBuilder;