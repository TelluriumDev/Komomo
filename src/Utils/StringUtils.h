// #pragma once
// 
// #include <algorithm>
// #include <cstddef>
// #include <cstdlib>
// #include <optional>
// #include <string>
// #include <string_view>
// #include <type_traits>
// #include <utility>
// #include <vector>
// 
// #include "fmt/color.h"
// 
// namespace ll::inline utils::string_utils {
// 
// // "2021-03-24"  ->  ["2021", "03", "24"]  (use '-' as split pattern)
// template <std::invocable<std::string_view> Fn>
// constexpr void splitByPattern(Fn&& fn, std::string_view s, std::string_view pattern, bool keepEmpty = false) {
//     if (s.empty()) return;
//     size_t pos{};
//     while ((pos = s.find(pattern)) != std::string::npos) {
//         if (keepEmpty || pos != 0) {
//             if (!std::invoke(std::forward<Fn>(fn), s.substr(0, pos))) return;
//         }
//         s = s.substr(pos + pattern.size());
//     }
//     if (keepEmpty || !s.empty()) std::invoke(std::forward<Fn>(fn), s);
// }
// template <typename T>
// [[nodiscard]] constexpr decltype(auto) splitByPattern(T&& str, std::string_view pattern, bool keepEmpty = false) {
//     using ReturnTypeElement = std::conditional_t<std::is_same_v<T&&, std::string&&>, std::string, std::string_view>;
//     std::vector<ReturnTypeElement> ret;
//     splitByPattern(
//         [&](std::string_view sv) {
//             ret.push_back(ReturnTypeElement{sv});
//             return true;
//         },
//         str,
//         pattern,
//         keepEmpty
//     );
//     return ret;
// }
// 
// /**
//  * @brief Replace all founded sub std::string and modify input str
//  * @param str       The input std::string
//  * @param oldValue  The sub string to be replaced
//  * @param newValue  The string to replace with
//  * @return std::string  The modified input std::string
//  */
// constexpr std::string& replaceAll(std::string& str, std::string_view oldValue, std::string_view newValue) {
//     for (std::string::size_type pos(0); pos != std::string::npos; pos += newValue.length()) {
//         if ((pos = str.find(oldValue, pos)) != std::string::npos) str.replace(pos, oldValue.length(), newValue);
//         else break;
//     }
//     return str;
// }
// 
// [[nodiscard]] constexpr std::string
// replaceAll(std::string const& str, std::string_view oldValue, std::string_view newValue) {
//     std::string ret = str;
//     replaceAll(ret, oldValue, newValue);
//     return ret;
// }
// 
// constexpr bool
// replaceContent(std::string& str, std::string_view before, std::string_view after, std::string_view relplaceWith) {
//     auto startOffset = str.find(before);
//     if (startOffset == std::string::npos) return false;
//     startOffset    += before.size();
//     auto endOffset  = after.empty() ? std::string::npos : str.find(after, startOffset);
//     str.replace(startOffset, endOffset - startOffset, relplaceWith);
//     return true;
// }
// 
// constexpr inline unsigned char digitFromByte[] = {
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   255, 255, 255, 255, 255, 255, 255, 10,
//     11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,
//     33,  34,  35,  255, 255, 255, 255, 255, 255, 10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,
//     23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
// };
// static_assert(sizeof(digitFromByte) == 256);
// 
// [[nodiscard]] constexpr unsigned char digitFromChar(char chr) noexcept {
//     return digitFromByte[static_cast<unsigned char>(chr)];
// }
// 
// constexpr inline char charconvDigits[2][37] = {
//     "0123456789abcdefghijklmnopqrstuvwxyz",
//     "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// };
// 
// [[nodiscard]] constexpr char charFromInt(bool upper, unsigned char i) { return charconvDigits[upper][i]; }
// /**
//  * @brief Integer to hex string.
//  *
//  * @tparam T      The integer type
//  * @param  value  The integer value
//  * @param  upper  Whether to use upper case (0x1A or 0x1a)
//  * @param  no0x   Whether to omit 0x prefix
//  * @param  noLeadingZero  Whether to omit leading zero
//  * @return std::string    The hex string
//  *
//  * @par Example
//  * @code
//  * IntToHexStr(15); // "F"
//  * IntToHexStr(16, true, true, false); // "0000000F"
//  * @endcode
//  */
// template <class T>
//     requires std::is_integral_v<T>
// [[nodiscard]] constexpr std::string
// intToHexStr(T value, bool upperCase = true, bool no0x = true, bool noLeadingZero = true) {
//     std::string result;
//     if (value < 0) result += '-';
//     if (!no0x) result += "0x";
//     bool leadingZero = true;
//     for (int i = sizeof(T) * 2; i > 0; --i) {
//         auto hex = (value >> (i - 1) * 4) & 0xF;
//         if (noLeadingZero && leadingZero && hex == 0) continue;
//         leadingZero  = false;
//         result      += charFromInt(upperCase, hex);
//     }
//     return result;
// }
// 
// [[nodiscard]] constexpr std::string strToHexStr(std::string_view value, bool upperCase = false, bool addSpace = false) {
//     std::string hex;
//     hex.reserve(value.size() * (addSpace ? 3 : 2));
//     for (unsigned char x : value) {
//         hex += charFromInt(upperCase, x / 16);
//         hex += charFromInt(upperCase, x % 16);
//         if (addSpace) hex += ' ';
//     }
//     if (addSpace && hex.ends_with(' ')) hex.pop_back();
//     return hex;
// }
// 
// [[nodiscard]] constexpr std::string applyTextStyle(fmt::text_style const& ts, std::string_view str) {
//     std::string res;
//     bool        has_style = false;
//     if (ts.has_emphasis()) {
//         has_style     = true;
//         auto emphasis = fmt::detail::make_emphasis<char>(ts.get_emphasis());
//         res.append(emphasis.begin(), emphasis.end());
//     }
//     if (ts.has_foreground()) {
//         has_style       = true;
//         auto foreground = fmt::detail::make_foreground_color<char>(ts.get_foreground());
//         res.append(foreground.begin(), foreground.end());
//     }
//     if (ts.has_background()) {
//         has_style       = true;
//         auto background = fmt::detail::make_background_color<char>(ts.get_background());
//         res.append(background.begin(), background.end());
//     }
//     res += str;
//     if (has_style) res += "\x1b[0m";
//     return res;
// }
// inline bool isu8str(std::string_view str) noexcept {
//     bool res = true;
//     fmt::detail::for_each_codepoint(str, [&](uint32_t cp, fmt::string_view) {
//         if (cp == fmt::detail::invalid_code_point) {
//             res = false;
//             return false;
//         }
//         return true;
//     });
//     return res;
// }
// 
// namespace CodePage {
// enum : unsigned int {
//     DefaultACP = 0,  // default to ANSI code page
//     ThreadACP  = 3,  // current thread's ANSI code page
//     Symbol     = 42, // SYMBOL translations
//     GB2312     = 936,
//     UTF8       = 65001,
// };
// } // namespace CodePage
// 
// 
// inline std::string toSnakeCase(std::string_view str) {
//     std::string res;
//     if (str.empty()) {
//         return res;
//     }
//     for (size_t i = 0; i < str.size(); ++i) {
//         if (isupper(str[i])) {
//             if (i > 0 && ((i + 1 < str.size() && !isupper(str[i + 1])) || !isupper(str[i - 1]))) {
//                 res.push_back('_');
//             }
//             res.push_back((char)tolower(str[i]));
//         } else {
//             res.push_back(str[i]);
//         }
//     }
//     return res;
// }
// 
// inline std::string toLowerCase(std::string_view str) {
//     std::string res{str};
//     std::transform(res.begin(), res.end(), res.begin(), [](char c) { return (char)std::tolower(c); });
//     return res;
// }
// 
// 
// [[nodiscard]] inline std::string u8str2str(std::u8string str) {
//     std::string& tmp = *reinterpret_cast<std::string*>(&str);
//     return {std::move(tmp)};
// }
// 
// [[nodiscard]] inline std::u8string str2u8str(std::string str) {
//     std::u8string& tmp = *reinterpret_cast<std::u8string*>(&str);
//     return {std::move(tmp)};
// }
// 
// [[nodiscard]] inline std::string const& u8str2strConst(std::u8string const& str) {
//     return *reinterpret_cast<const std::string*>(&str);
// }
// 
// [[nodiscard]] inline std::u8string const& str2u8strConst(std::string const& str) {
//     return *reinterpret_cast<const std::u8string*>(&str);
// }
// 
// [[nodiscard]] inline std::string_view u8sv2sv(std::u8string_view str) {
//     return {reinterpret_cast<char const*>(str.data()), str.size()};
// }
// 
// [[nodiscard]] inline std::u8string_view sv2u8sv(std::string_view str) {
//     return {reinterpret_cast<const char8_t*>(str.data()), str.size()};
// }
// 
// inline std::optional<bool> svtobool(std::string_view str) {
//     if (str.size() <= 4) {
//         auto lower = toLowerCase(str);
//         if (lower == "1" || lower == "y" || str == "yes" || lower == "true") {
//             return true;
//         } else if (lower == "0" || lower == "n" || str == "no" || lower == "false") {
//             return false;
//         }
//     }
//     return std::nullopt;
// }
// 
// } // namespace ll::inline utils::string_utils
