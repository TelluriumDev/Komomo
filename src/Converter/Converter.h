#pragma once

#include "Utils/Using.h"


#include <ll/api/reflection/Reflection.h>

#include <fmt/format.h>
#include <concepts>
#include <cstddef>
#include <string>
#include <type_traits>
#include <magic_enum.hpp>


namespace Komomo {
    template<typename T>
    constexpr bool IsReflectable = std::is_class_v<T> && // 只处理类
                                   std::is_aggregate_v<T> && // 可聚合初始化
                                   !std::is_array_v<T> && // 不是数组
                                   !requires(T &a) { a.operator[]; } && // 没有重载 operator[]
                                   !requires { typename T::value_type; }; // 不是容器类型

    namespace detail {
        template<typename T, typename Enable = void>
        struct Converter {
            static Local<Value> toScript() {
                static_assert(sizeof(T) == 0, "Unsupported type conversion");
                return {};
            }

            static T toCpp(Local<Value> const &) {
                static_assert(sizeof(T) == 0, "Unsupported type conversion");
                return T{};
            }
        };

        template<size_t N>
        struct Converter<char[N]> {
            static Local<Value> toScript(const char (&str)[N]) { return String::newString(str); }

            static std::string toCpp(Local<Value> const &val) { return val.asString().toString(); }
        };

        template<size_t N>
        struct Converter<const char[N]> {
            static Local<Value> toScript(const char (&str)[N]) { return String::newString(str); }

            static std::string toCpp(Local<Value> const &val) { return val.asString().toString(); }
        };

        template<std::integral T>
        struct Converter<T> {
            static Local<Value> toScript(T const &val) { return Number::newNumber(static_cast<double>(val)); }

            static T toCpp(Local<Value> const &val) { return static_cast<T>(val.asNumber().toInt64()); }
        };

        template<std::floating_point T>
        struct Converter<T> {
            static Local<Value> toScript(T const &val) { return Number::newNumber(val); }

            static T toCpp(Local<Value> const &val) { return val.asNumber().toDouble(); }
        };

        template<>
        struct Converter<bool> {
            static Local<Value> toScript(bool const &val) { return Boolean::newBoolean(val); }

            static bool toCpp(Local<Value> const &val) { return val.asBoolean().value(); }
        };

        template<typename T>
        struct Converter<T, std::enable_if_t<std::is_enum_v<T> > > {
            static Local<Value> toScript(T const &val) {
                return Number::newNumber(static_cast<std::underlying_type_t<T>>(val));
            }

            static T toCpp(Local<Value> const &val) {
                auto enumValue = magic_enum::enum_cast<T>(
                    static_cast<std::underlying_type_t<T>>(val.asNumber().toInt64()));
                if (!enumValue.has_value()) {
                    throw script::Exception("Invalid enum value: " + std::to_string(val.asNumber().toInt64()));
                }
                return enumValue.value();
            };
        };

        template<>
        struct Converter<std::string> {
            static Local<Value> toScript(std::string const &str) { return String::newString(str); }

            static std::string toCpp(Local<Value> const &val) { return val.asString().toString(); }
        };

        template<>
        struct Converter<const char *> {
            static Local<Value> toScript(const char *str) { return String::newString(str); }

            static std::string toCpp(Local<Value> const &val) { return val.asString().toString(); }
        };


        // pfr reflection
        template<typename T>
        struct Converter<T, std::enable_if_t<IsReflectable<T> > > {
            static Local<Value> toScript(T const &value) {
                auto obj = Object::newObject();
                boost::pfr::for_each_field(value, [&](auto const &field, std::size_t index) {
                    using FieldType = std::remove_cvref_t<decltype(field)>;
                    try {
                        obj.set(boost::pfr::names_as_array<T>()[index], Converter<FieldType>::toScript(field));
                    } catch (const script::Exception &e) {
                        throw script::Exception(fmt::format(
                            "Failed to convert field '{}' in type '{}': {}",
                            boost::pfr::names_as_array<T>()[index],
                            typeid(T).name(),
                            e.what()
                        ));
                    }
                });
                return obj;
            }

            static T toCpp(Local<Value> const &val, T res = {}) {
                auto obj = val.asObject();
                boost::pfr::for_each_field(res, [&](auto &field, std::size_t index) {
                    using FieldType = std::remove_cvref_t<decltype(field)>;
                    try {
                        field = Converter<FieldType>::toCpp(obj.get(boost::pfr::names_as_array<T>()[index]));
                    } catch (const script::Exception &e) {
                        throw script::Exception(fmt::format(
                            "Failed to convert field '{}' in type '{}': {}",
                            boost::pfr::names_as_array<T>()[index],
                            typeid(T).name(),
                            e.what()
                        ));
                    }
                });
                return res;
            }
        };
    } // namespace detail


    namespace internal {
        // c++ -> scriptx
        template<typename T, typename = void>
        struct is_convertible_to_script : std::false_type {
        };

        template<typename T>
        struct is_convertible_to_script<
                    T,
                    std::void_t<
                        decltype(detail::Converter<std::remove_cvref_t<T> >::toScript(std::declval<const T &>())),
                        decltype(detail::Converter<std::remove_cvref_t<T> >::toScript(std::declval<T &>()))> >
                : std::true_type {
        };

        template<typename T>
        constexpr bool is_convertible_to_script_v = is_convertible_to_script<T>::value;

        // scriptx -> c++
        template<typename T, typename = void>
        struct is_convertible_from_script : std::false_type {
        };

        template<typename T>
        struct is_convertible_from_script<
                    T,
                    std::void_t<decltype(detail::Converter<T>::toCpp(std::declval<const Local<Value> &>()))> >
                : std::true_type {
        };

        template<typename T>
        constexpr bool is_convertible_to_cpp_v = is_convertible_from_script<T>::value;

        // c++ <-> scriptx
        template<typename T>
        constexpr bool is_convertible_v = is_convertible_to_script_v<T> && is_convertible_to_cpp_v<T>;
    } // namespace internal
} // namespace Komomo
