#pragma once
#include "fmt/format.h"
#include <algorithm>
#include <optional>
#include <string>
#include <vector>


namespace Komomo {

template <typename T>
inline bool FindVector(std::vector<T> const& vec, T const& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

inline std::string ReplaceStr(const std::string& str, std::string const& from, std::string const& to) {
    std::string result    = str;
    size_t      start_pos = 0;
    while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length(); // +1 for the advance
    }
    return result;
}


template <typename... Args>
inline std::optional<std::string> RuntimeFormat(std::string const& fmt, Args... args) {
    try {
        return fmt::vformat(fmt, fmt::make_format_args(args...));
    } catch (...) {
        return std::nullopt;
    }
}


} // namespace Komomo