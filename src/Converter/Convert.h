#pragma once

#include "Converter/Convert.h"
#include "Converter/StlConverter.h"

// #include "ProjectConverters.hpp" // circular reference, please include manually

namespace Komomo {
    template<typename T>
    [[nodiscard]] Local<Value> ConvertToScriptX(T const &value) {
        if constexpr (std::is_enum_v<T>) {
            return detail::Converter<T>::toScript(value);
        } else {
            return detail::Converter<std::remove_cvref_t<T> >::toScript(value);
        }
    }

    template<typename T>
    [[nodiscard]] T ConvertFromScriptX(Local<Value>
                                       const &value) {
        if constexpr (std::is_enum_v<T>) {
            return
                    detail::Converter<T>::toCpp(value);
        } else {
            return detail::Converter<std::remove_cvref_t<T> >
            ::toCpp(value);
        }
    }

    template<typename T>
    [[nodiscard]] std::vector<T> ConvertFromScriptX(Arguments const &args) {
        std::vector<T> result;
        result.reserve(args.size());
        for (size_t i = 0; i < args.size(); i++) {
            result.push_back(ConvertFromScriptX<T>(args[i]));
        }
        return result;
    }
} // namespace Komomo
