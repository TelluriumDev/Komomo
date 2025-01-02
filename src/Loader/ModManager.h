#pragma once

#include <ll/api/Expected.h>
#include <ll/api/base/Macro.h>
#include <ll/api/mod/Manifest.h>
#include <ll/api/mod/ModManager.h>


#include <string_view>

namespace Komomo {

class KomomoModManager final : public ll::mod::ModManager {
public:
    KomomoModManager();
    ~KomomoModManager() override;

    [[nodiscard]] std::vector<std::string> getPluginFileFilters() const;


    static std::vector<std::string> filterMods(const std::filesystem::path& directory); // 过滤指定目录下的所有JS插件

private:
    ll::Expected<> load(ll::mod::Manifest manifest) override;
    ll::Expected<> unload(std::string_view name) override;
};

} // namespace Komomo