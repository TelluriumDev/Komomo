// #pragma once
// // #include "endstone/detail/plugin/plugin_description_builder.h"
// // #include "endstone/plugin/plugin.h"
// // #include "endstone/plugin/plugin_description.h"
// #include "ll/api/mod/Manifest.h"
// #include "ll/api/mod/Mod.h"
// 
// #include <cstdint>
// 
// 
// namespace Komomo {
// 
// 
// class KomomoMod : public ll::mod::Mod {
// 
// public:
//     KomomoMod(const ll::mod::Manifest& manifest) : ll::mod::Mod(std::move(manifest)) {}
//     ~KomomoMod();
// 
// public:
//     bool onLoad();
//     bool onEnable();
//     bool onDisable();
//     bool onUnload();
// 
// private:
//     uint64_t engineId_;
// };
// 
// 
// } // namespace Komomo
