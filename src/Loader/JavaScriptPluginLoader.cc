// #include "JavaScriptPluginLoader.h"
// #include "Entry.h"
// #include "JavaScriptPlugin.h"
// #include "Manager/EngineData.h"
// #include "Manager/NodeManager.h"
// #include "Utils/Using.h"
// #include <filesystem>
// #include <memory>
// #include <string>
// #include <vector>
// 
// 
// namespace jse {
// 
// JavaScriptPluginLoader::JavaScriptPluginLoader(endstone::Server& server) : PluginLoader(server) {}
// std::vector<std::string> JavaScriptPluginLoader::getPluginFileFilters() const { return {".js"}; }
// 
// endstone::Plugin* JavaScriptPluginLoader::loadPlugin(std::string file) {
//     auto& manager = NodeManager::getInstance();
//     auto  wrapper = manager.newScriptEngine();
// 
//     EngineScope scope(wrapper->mEngine);
//     auto        data = ENGINE_DATA();
//     try {
//         auto path = fs::path(file);
// 
//         data->mFileName = path.filename().string();
// 
//         fs::path package = path.parent_path() / "package.json";
// 
//         // 安装依赖
//         if (NodeManager::packageHasDependency(package)
//             && !NodeManager::packageHasDependency(path.parent_path() / "node_modules")) {
//             Entry::getInstance()->getLogger().info("Installing dependencies for plugin: {}", path.filename());
//             manager.NpmInstall(path.parent_path().string());
//         }
// 
//         if (!NodeManager::loadFile(wrapper, file, NodeManager::packageIsEsm(package))) {
//             Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
//             return nullptr;
//         }
// 
//         // 解析注册数据
//         JsPluginDescriptionBuilder builder{};
//         builder.description        = data->tryParseDescription();
//         builder.load               = data->tryParseLoad();
//         builder.authors            = data->tryParseAuthors();
//         builder.contributors       = data->tryParseContributors();
//         builder.website            = data->tryParseWebsite();
//         builder.prefix             = data->tryParsePrefix();
//         builder.provides           = data->tryParseProvides();
//         builder.depend             = data->tryParseDepend();
//         builder.soft_depend        = data->tryParseSoftDepend();
//         builder.load_before        = data->tryParseLoadBefore();
//         builder.default_permission = data->tryParseDefaultPermission();
//         data->tryParseCommands(builder);
//         data->tryParsePermissions(builder);
// 
//         // 创建插件实例
//         auto plugin   = new JavaScriptPlugin(data->mID, builder.build(data->tryParseName(), data->tryParseVersion()));
//         data->mPlugin = plugin;
// 
//         return plugin;
//     } catch (script::Exception& e) {
//         Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
//         Entry::getInstance()->getLogger().error("JavaScript error: {}", e.what());
//         Entry::getInstance()->getLogger().error("Stack trace: {}", e.stacktrace());
//     } catch (std::exception& e) {
//         Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
//         Entry::getInstance()->getLogger().error("Unknown error: {}", e.what());
//     } catch (...) {
//         Entry::getInstance()->getLogger().error("Failed to load plugin: {}", file);
//         Entry::getInstance()->getLogger().error("Unknown error");
//     }
// 
//     manager.destroyEngine(data->mID);
//     return nullptr;
// }
// 
// 
// std::vector<std::string> JavaScriptPluginLoader::filterPlugins(const fs::path& directory) {
//     std::vector<std::string> plugins;
//     if (!fs::exists(directory)) {
//         return plugins;
//     }
// 
//     for (const auto& entry : fs::directory_iterator(directory)) {
//         if (!entry.is_directory()) {
//             continue;
//         }
// 
//         fs::path package = entry.path() / "package.json";
//         if (!fs::exists(package)) {
//             continue;
//         }
// 
//         auto main = NodeManager::findMainScript(package);
//         if (!main) {
//             continue;
//         }
// 
//         plugins.push_back((entry.path() / *main).string());
//     }
// 
//     return plugins;
// }
// 
// 
// } // namespace jse
