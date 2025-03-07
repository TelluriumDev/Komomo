#pragma once


#include "Converter/Converter.h"

#include "nlohmann/json.hpp"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Komomo::detail {
// vector
template <typename T>
struct Converter<std::vector<T>> {
    static Local<Value> toScript(std::vector<T> const& vec) {
        auto array = Array::newArray(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            array.set(i, Converter<T>::toScript(vec[i]));
        }
        return array;
    }

    static std::vector<T> toCpp(Local<Value> const& val) {
        auto           array = val.asArray();
        std::vector<T> vec;
        vec.reserve(array.size());
        for (size_t i = 0; i < array.size(); i++) {
            vec.push_back(Converter<T>::toCpp(array.get(i)));
        }
        return vec;
    }
};


// unordered_map
template <typename K, typename V>
struct Converter<std::unordered_map<K, V>> {
    static Local<Value> toScript(std::unordered_map<K, V> const& map) {
        auto obj = Object::newObject();
        for (auto const& [key, value] : map) {
            obj.set(key, Converter<V>::toScript(value));
        }
        return obj;
    }

    static std::unordered_map<K, V> toCpp(Local<Value> const& val) {
        auto                     obj = val.asObject();
        std::unordered_map<K, V> map;
        auto                     keys = obj.getKeyNames();
        map.reserve(keys.size());
        for (auto const& key : keys) {
            map[key] = Converter<V>::toCpp(obj.get(key));
        }
        return std::move(map);
    };
};

// unordered_set
template <typename T>
struct Converter<std::unordered_set<T>> {
    static Local<Value> toScript(std::unordered_set<T> const& set) {
        auto array = Array::newArray(set.size());
        for (auto const& v : set) {
            array.add(Converter<T>::toScript(v));
        }
        return array;
    }

    static std::unordered_set<T> toCpp(Local<Value> const& val) {
        auto                  array = val.asArray();
        std::unordered_set<T> set;
        set.reserve(array.size());
        for (size_t i = 0; i < array.size(); i++) {
            set.insert(Converter<T>::toCpp(array.get(i)));
        }
        return set;
    }
};


/**
 * struct A { int x; };
 *
 * using V1 = std::variant<A, std::string>;
 *
 * V1 v1 = A{42};
 * Local<Value> scriptVal = Converter<V1>::toScript(v1);
 *
 * V1 v1Back = Converter<V1>::toCpp(scriptVal);   // 转回 C++ variant
 */
template <typename... Ts>
struct Converter<std::variant<Ts...>> {
    static Local<Value> toScript(std::variant<Ts...> const& val) {
        if (val.valueless_by_exception()) {
            return Local<Value>();
        }
        return std::visit(
            []<typename T0>(const T0& v) -> Local<Value> {
                using ValueType = std::remove_cvref_t<T0>;
                return Converter<ValueType>::toScript(v);
            },
            val
        );
    }

    template <size_t I = 0>
    static std::variant<Ts...> tryConvert(const Local<Value>& val) {
        if constexpr (I >= sizeof...(Ts)) {
            throw script::Exception("Failed to convert value to any variant type");
        } else {
            using CurrentType = std::variant_alternative_t<I, std::variant<Ts...>>;
            try {
                return Converter<CurrentType>::toCpp(val);
            } catch (...) {
                return tryConvert<I + 1>(val);
            }
        }
    }

    static std::variant<Ts...> toCpp(const Local<Value>& val) { return tryConvert(val); }
};

template <>
struct Converter<nlohmann::ordered_json> {
    static Local<Value> toScript(const nlohmann::ordered_json& val) {
        Local<Value> result;
        switch (val.type()) {
        case nlohmann::detail::value_t::null: {
            result = Local<Value>();
            break;
        }
        case nlohmann::detail::value_t::object: {
            Local<Object> object = Object::newObject();
            for (auto it = val.begin(); it != val.end(); ++it) {
                object.set(String::newString(it.key()), toScript(it.value()));
            }
            result = object;
            break;
        }
        case nlohmann::detail::value_t::array: {
            Local<Array> array = Array::newArray(val.size());
            for (size_t i = 0; i < val.size(); i++) {
                array.add(toScript(val[i]));
            }
            result = array;
            break;
        }

        case nlohmann::detail::value_t::string: {
            result = String::newString(val.get<std::string>().c_str());
            break;
        }
        case nlohmann::detail::value_t::boolean: {
            result = Boolean::newBoolean(val.get<bool>());
            break;
        }
        case nlohmann::detail::value_t::number_integer: {
            result = Number::newNumber(val.get<double>());
            break;
        }
        case nlohmann::detail::value_t::number_unsigned: {
            result = Number::newNumber(val.get<double>());
            break;
        }
        case nlohmann::detail::value_t::number_float: {
            result = Number::newNumber(val.get<double>());
            break;
        }
        case nlohmann::detail::value_t::binary: {
            // // TODO: Convert binary data to base64 string
            // result = String::newString("TODO: Convert binary data to base64 string");
            break;
        }
        case nlohmann::detail::value_t::discarded: {
            result = Local<Value>();
            break;
        }
        }
        return result;
    };

    template <typename T = nlohmann::ordered_json>
    static nlohmann::ordered_json tryConvert(const Local<Value>& val) {
        nlohmann::ordered_json result;
        switch (val.getKind()) {
        case script::ValueKind::kNull: {
            result = nlohmann::ordered_json();
            break;
        }
        case script::ValueKind::kObject: {
            Local<Object> object = val.asObject();
            result               = nlohmann::ordered_json::object();
            for (auto& keys : object.getKeys()) {
                Local<Value> value      = object.get(keys);
                result[keys.toString()] = toCpp(object.get(keys));
            }
            break;
        }

        case script::ValueKind::kString: {
            result = val.asString().toString();
            break;
        }
        case script::ValueKind::kNumber: {
            result = val.asNumber().toInt64();
            break;
        }
        case script::ValueKind::kBoolean: {
            result = val.asBoolean().value();
            break;
        }
        case script::ValueKind::kFunction: {
            break;
        }
        case script::ValueKind::kArray: {
            Local<Array> array = val.asArray();
            result             = nlohmann::ordered_json::array();
            for (size_t i = 0; i < array.size(); ++i) {
                result.push_back(toCpp(array.get(i)));
            }
            break;
        }
        case script::ValueKind::kByteBuffer: {
            // // TODO: Convert base64 string to binary data
            // result = nlohmann::json("TODO: Convert base64 string to binary data");
            break;
        }
        case script::ValueKind::kUnsupported:
            break;
        }
        return result;
    }

    static nlohmann::ordered_json toCpp(const Local<Value>& val) { return tryConvert<nlohmann::ordered_json>(val); }
};



} // namespace Komomo::detail
