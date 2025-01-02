// #pragma once
// 
// #include <filesystem>
// #include <fstream>
// #include <optional>
// #include <string>
// 
// 
// #include "StringUtils.h"
// 
// namespace ll::inline utils::file_utils {
// using namespace string_utils;
// namespace fs = std::filesystem;
// 
// inline std::filesystem::path u8path(std::string_view src) { return std::filesystem::path{sv2u8sv(src)}; }
// 
// inline std::optional<std::string> readFile(std::filesystem::path const& filePath, bool isBinary = false) {
//     if (!fs::exists(filePath)) return std::nullopt;
//     std::ifstream           fRead;
//     std::ios_base::openmode mode = std::ios_base::in;
//     if (isBinary) mode |= std::ios_base::binary;
//     fRead.open(filePath, mode);
//     if (!fRead.is_open()) return std::nullopt;
//     std::string data((std::istreambuf_iterator<char>(fRead)), {});
//     fRead.close();
//     return data;
// }
// 
// inline bool writeFile(std::filesystem::path const& filePath, std::string_view content, bool isBinary = false) {
//     std::ofstream           fWrite;
//     std::ios_base::openmode mode = std::ios_base::out;
//     if (isBinary) mode |= std::ios_base::binary;
//     std::error_code ec;
//     fs::create_directories(filePath.parent_path(), ec);
//     fWrite.open(filePath, mode);
//     if (!fWrite.is_open()) return false;
//     fWrite << content;
//     fWrite.close();
//     return true;
// }
// 
// inline std::vector<std::string> getFileList(std::filesystem::path const& directoryPath) {
//     std::vector<std::string> result;
//     try {
//         for (auto const& entry : fs::directory_iterator{directoryPath}) {
//             result.push_back(ll::string_utils::u8str2str(entry.path().filename().u8string()));
//         }
//     } catch (...) {}
//     return result;
// }
// 
// } // namespace ll::inline utils::file_utils
