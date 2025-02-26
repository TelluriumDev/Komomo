#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep
#include "nlohmann/json_fwd.hpp"

#include <nlohmann/json.hpp>

using namespace nlohmann;

class ConfigClass : public ScriptClass {
    std::string  mConfigPath;
    ordered_json mConfig;

    bool flush();
    bool reload();

    bool checkHasVersion(ordered_json json);

    void
    setNestedValue(ordered_json& j, const std::vector<std::string>& keys, const std::string& value, size_t index = 0) {
        if (index == keys.size() - 1) {
            j[keys[index]] = value;
        } else {
            if (!j.contains(keys[index])) {
                j[keys[index]] = json::object();
            }
            setNestedValue(j[keys[index]], keys, value, index + 1);
        }
    }

    bool hasNestedValue(const json& j, const std::vector<std::string>& keys, size_t index = 0) {
        if (index >= keys.size()) {
            return false;
        }
        const std::string& key = keys[index];
        if (!j.contains(key)) {
            return hasNestedValue(j[key], keys, index + 1);
        } else return true;
        return false;
    }

    void delNestedValue(ordered_json& j, const std::vector<std::string>& keys, size_t index = 0) {
        if (index == keys.size() - 1) {
            j.erase(keys[index]);
        } else {
            if (!j.contains(keys[index])) {
                return;
            }
            delNestedValue(j[keys[index]], keys, index + 1);
        }
    }

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
