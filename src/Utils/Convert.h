#pragma once


#include <Utils/Using.h>
#include <fmt/format.h>
#include <magic_enum/magic_enum.hpp>


#include <cstddef>
#include <type_traits>
#include <unordered_map>


namespace Komomo {

// C++ -> ScriptX
// std::string、char* -> String
// int、double、float -> Number
// bool -> Boolean
// std::vector<T> -> Array<T>
// std::unordered_map<K, V> -> Object<string, V>
// enum<T> -> Number
namespace ConvertCppToScriptX {

// 基础模板
template <typename T, typename Enable = void>
struct ToScriptType {
    static_assert(sizeof(T) == 0, "Unsupported type conversion");
};

// 特化类型
template <>
struct ToScriptType<std::string> {
    using Type = String;
};

template <>
struct ToScriptType<const char*> {
    using Type = String;
};
template <size_t N>
struct ToScriptType<char[N]> {
    using Type = String;
};

template <>
struct ToScriptType<int> {
    using Type = Number;
};

template <>
struct ToScriptType<double> {
    using Type = Number;
};

template <>
struct ToScriptType<bool> {
    using Type = Boolean;
};

// 数组转换
template <typename T>
struct ToScriptType<std::vector<T>> {
    using Type = Array;
};

// map转换 (key必须是可转换成string的类型)
template <typename K, typename V>
struct ToScriptType<std::unordered_map<K, V>> {
    using Type = Object;
};

// enum
template <typename T>
struct ToScriptType<T, std::enable_if_t<std::is_enum_v<T>>> {
    using Type = Number;
};

// 实现
template <typename T>
Local<Value> ConvertToScriptImpl(const T& value) {
    using ScriptType = typename ToScriptType<T>::Type;

    if constexpr (std::is_enum_v<T>) {
        return Number::newNumber((int)value); // enum -> number
    } else if constexpr (std::is_same_v<ScriptType, String>) {
        return String::newString(value); // string -> string
    } else if constexpr (std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>) {
        return String::newString(value); // char array -> string
    } else if constexpr (std::is_same_v<ScriptType, Number>) {
        return Number::newNumber(value); // int、double、float -> number
    } else if constexpr (std::is_same_v<ScriptType, Boolean>) {
        return Boolean::newBoolean(value); // bool -> boolean
    } else if constexpr (std::is_same_v<ScriptType, Array>) {
        auto arr = Array::newArray(); // vector<T> -> array
        for (const auto& item : value) {
            arr.add(ConvertToScriptImpl(item));
        }
        return arr;
    } else if constexpr (std::is_same_v<ScriptType, Object>) {
        auto obj = Object::newObject(); // unordered_map<K, V> -> object
        for (const auto& [key, val] : value) {
            obj.set(fmt::to_string(key), ConvertToScriptImpl(val));
        }
        return obj;
    }
}

} // namespace ConvertCppToScriptX


// ScriptX -> C++
// Number -> enum<T>
// String -> std::string
// Number -> int、double、float
// Boolean -> bool
// Array<T> -> std::vector<T>
// Array<Value> -> std::vector<T>
// Object<Value> -> std::unordered_map<std::string, T>
namespace ConvertScriptXToCpp {

// 基础模板
template <typename T, typename Enable = void>
struct FromScriptType {
    static T Convert(const Local<Value>& value) {
        static_assert(sizeof(T) == 0, "Unsupported type conversion");
        return T{};
    }
};

// string
template <>
struct FromScriptType<std::string> {
    static std::string Convert(const Local<Value>& value) { return value.asString().toString(); }
};

// int
template <>
struct FromScriptType<int> {
    static int Convert(const Local<Value>& value) { return static_cast<int>(value.asNumber().toDouble()); }
};

// double
template <>
struct FromScriptType<double> {
    static double Convert(const Local<Value>& value) { return value.asNumber().toDouble(); }
};

// bool
template <>
struct FromScriptType<bool> {
    static bool Convert(const Local<Value>& value) { return value.asBoolean().value(); }
};

// vector
template <typename T>
struct FromScriptType<std::vector<T>> {
    static std::vector<T> Convert(const Local<Value>& value) {
        auto           arr = value.asArray();
        std::vector<T> result;
        result.reserve(arr.size());
        for (size_t i = 0; i < arr.size(); i++) {
            result.push_back(FromScriptType<T>::Convert(arr.get(i)));
        }
        return result;
    }
};

// map
template <typename V>
struct FromScriptType<std::unordered_map<std::string, V>> {
    static std::unordered_map<std::string, V> Convert(const Local<Value>& value) {
        auto                               obj = value.asObject();
        std::unordered_map<std::string, V> result;
        auto                               keys = obj.getKeyNames();
        for (const auto& key : keys) {
            result[key] = FromScriptType<V>::Convert(obj.get(key));
        }
        return result;
    }
};

// enum
template <typename T>
struct FromScriptType<T, std::enable_if_t<std::is_enum_v<T>>> {
    static T Convert(const Local<Value>& value) {
        auto enumValue = magic_enum::enum_cast<T>(value.asNumber().toInt64());
        if (!enumValue.has_value()) {
            throw std::runtime_error("Invalid enum value: " + std::to_string(value.asNumber().toInt64()));
        }
        return enumValue.value();
    }
};

} // namespace ConvertScriptXToCpp


template <typename T>
Local<Value> ConvertToScriptX(const T& value) {
    return ConvertCppToScriptX::ConvertToScriptImpl(value);
}

template <typename T>
T ConvertFromScriptX(const Local<Value>& value) {
    return ConvertScriptXToCpp::FromScriptType<T>::Convert(value);
}


} // namespace Komomo