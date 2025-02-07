#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/data/KeyValueDB.h>


class KeyValueDBClass : public ScriptClass {

    std::unique_ptr<ll::data::KeyValueDB> db;


public:
    KeyValueDBClass(std::filesystem::path const& path);

    KeyValueDBClass(std::filesystem::path const& path, bool createIfMiss, bool fixIfError, int bloomFilterBit);

    static Local<Object> newKeyValueDB(const Arguments& args);

    Local<Value> get(const Arguments& args);

    Local<Value> has(const Arguments& args);

    Local<Value> empty(const Arguments& args);

    Local<Value> set(const Arguments& args);

    Local<Value> del(const Arguments& args);

    // 技术有限 直接转成 Object 处理
    Local<Value> iter(const Arguments& args);

    Local<Value> release();
};

extern ClassDefine<KeyValueDBClass> keyValueDBClassBuilder;