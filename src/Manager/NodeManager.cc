// #pragma warning(disable : 4996)
// #include "Manager/NodeManager.h"
// #include "Entry.h"
// #include "Manager/BindAPI.h"
// #include "Manager/EngineData.h"
// #include "Utils/Using.h"
// #include "Utils/Util.h"
//
//
// #include <fmt/core.h>
// #include <nlohmann/json.hpp>
// #include <node.h>
// #include <uv.h>
// #include <v8-cppgc.h>
//
// #include <filesystem>
// #include <memory>
// #include <thread>
// #include <unordered_map>
// #include <utility>
//
//
// namespace Komomo {
//
//
// NodeManager& NodeManager::getInstance() {
//     static NodeManager instance;
//     return instance;
// }
//
// void NodeManager::initNodeJs() {
//
//     if (mIsInitialized) {
//         return;
//     }
//
//     auto workingDir = fs::current_path() / "bedrock_server.exe";
//     mArgs           = {workingDir.string()};
//
//     char* cWorkingDir = const_cast<char*>(workingDir.string().c_str());
//     uv_setup_args(1, &cWorkingDir);
//     cppgc::InitializeProcess();
//     std::vector<string> errors;
//     if (node::InitializeNodeWithArgs(&mArgs, &mExecArgs, &errors) != 0) {
//         Entry::getInstance().getSelf().getLogger().error("Failed to initialize Node.js: ");
//         for (auto const& error : errors) {
//             Entry::getInstance().getSelf().getLogger().error(error);
//         }
//         return;
//     }
//
//     mPlatform = node::MultiIsolatePlatform::Create(std::thread::hardware_concurrency());
//     v8::V8::InitializePlatform(mPlatform.get());
//     v8::V8::Initialize();
//     mIsInitialized = true;
// }
//
// void NodeManager::shutdownNodeJs() {
//     for (auto& [id, wrapper] : mEngines) {
//         if (wrapper.mIsRunning) {
//             node::Stop(wrapper.mEnvSetup->env());
//             wrapper.mIsRunning = false;
//         }
//     }
//
//     // 清空引擎列表
//     mEngines.clear();
//     v8::V8::Dispose();
//     v8::V8::DisposePlatform();
// }
//
//
// bool NodeManager::hasEngine(EngineID id) const { return mEngines.contains(id); }
//
//
// EngineWrapper* NodeManager::newScriptEngine() {
//     static EngineID NextEngineID = 0;
//     if (!mIsInitialized) {
//         return nullptr;
//     }
//     EngineID id = NextEngineID++;
//
//     std::vector<string>           errors;
//     node::EnvironmentFlags::Flags flags = static_cast<node::EnvironmentFlags::Flags>(
//         node::EnvironmentFlags::kNoRegisterESMLoader | node::EnvironmentFlags::kNoCreateInspector
//     );
//     std::unique_ptr<node::CommonEnvironmentSetup> envSetup =
//         node::CommonEnvironmentSetup::Create(mPlatform.get(), &errors, mArgs, mExecArgs, flags);
//     if (!envSetup) {
//         for (auto const& err : errors)
//             Entry::getInstance().getSelf().getLogger().error("Faild to create environment setup: {}", err);
//         return nullptr;
//     }
//
//     v8::Isolate*       isolate = envSetup->isolate();
//     node::Environment* env     = envSetup->env();
//
//     v8::Locker         locker(isolate);
//     v8::Isolate::Scope isolateScope(isolate);
//     v8::HandleScope    handleScope(isolate);
//     v8::Context::Scope contextScope(envSetup->context());
//
//     ScriptEngine* engine = new ScriptEngineImpl({}, isolate, envSetup->context(), false);
//     engine->setData(std::make_shared<EngineData>(id)); // 设置引擎数据
//
//     EngineScope scope(engine);
//     BindAPI(engine);
//     // EngineWrapper warpper;
//     mEngines.emplace(id, EngineWrapper{id, engine, std::move(envSetup)});
//
//     node::AddEnvironmentCleanupHook(
//         isolate,
//         [](void* arg) {
//             static_cast<ScriptEngine*>(arg)->destroy();
//             Entry::getInstance().getSelf().getLogger().debug("Destroyed engine: {}", arg);
//         },
//         engine
//     );
//
//     return &mEngines[id];
// }
//
// EngineWrapper* NodeManager::getEngine(EngineID id) {
//     if (mEngines.contains(id)) {
//         return &mEngines[id];
//     }
//     return nullptr;
// }
//
//
// bool NodeManager::destroyEngine(EngineID id) {
//     if (!hasEngine(id)) {
//         return false;
//     }
//
//     auto& warpper      = mEngines[id];
//     warpper.mIsRunning = false;
//
//     node::Stop(warpper.mEnvSetup->env());
//
//     // TODO: Stop uv_loop
//
//     return true;
// }
//
//
// bool NodeManager::NpmInstall(string npmExecuteDir) {
//     if (!mIsInitialized) {
//         return false;
//     }
//
//     std::vector<std::string> errors;
//     auto                     setup = node::CommonEnvironmentSetup::Create(
//         mPlatform.get(),
//         &errors,
//         mArgs,
//         mExecArgs,
//         node::EnvironmentFlags::kOwnsProcessState
//     );
//     if (!setup) {
//         for (const std::string& err : errors)
//             Entry::getInstance().getSelf().getLogger().error("CommonEnvironmentSetup Error: {}", err.c_str());
//         return false;
//     }
//     npmExecuteDir = ReplaceStr(npmExecuteDir, "\\", "/");
//
//     v8::Isolate*       isolate = setup->isolate();
//     node::Environment* env     = setup->env();
//
//     v8::Locker         locker(isolate);
//     v8::Isolate::Scope isolate_scope(isolate);
//     v8::HandleScope    handle_scope(isolate);
//     v8::Context::Scope context_scope(setup->context());
//
//     // clang-format off
//     string compiler = R"(
//         const cwd = process.cwd();
//         require("process").chdir(`)"+npmExecuteDir+R"(`);
//         (async function npm() {
//             const NPM = require(`${cwd}/plugins/js_engine/node_modules/npm/lib/npm.js`);
//             const npm = new NPM();
//             try {
//                 await npm.load();
//                 await npm.exec("install", []);
//             } catch (e) {
//                 console.error(e);
//             }
//         })();
//         require("process").chdir(cwd);
//     )";
//     // clang-format on
//
//     bool success = false;
//     try {
//         node::SetProcessExitHandler(env, [&](node::Environment* env_, int exit_code) { node::Stop(env); });
//         v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
//         if (loadValue.IsEmpty()) {
//             throw std::runtime_error("Failed to load environment");
//         }
//         success = node::SpinEventLoop(env).FromMaybe(1) == 0;
//     } catch (...) {
//         Entry::getInstance().getSelf().getLogger().error("Failed to run npm install");
//     }
//
//     node::Stop(env);
//     return success;
// }
//
//
// bool NodeManager::loadFile(EngineWrapper* wrapper, fs::path const& path, bool esm) {
//     if (!wrapper) {
//         return false;
//     }
//
//     auto* env     = wrapper->mEnvSetup->env();
//     auto* isolate = wrapper->mEnvSetup->isolate();
//
//     auto js_code = readFileContent(path);
//     if (!js_code) {
//         return false;
//     }
//
// #if defined(WIN32) || defined(_WIN32)
//     string dirname  = ReplaceStr(path.parent_path().string(), "\\", "\\\\");
//     string filename = ReplaceStr(path.string(), "\\", "\\\\");
// #elif defined(__linux__)
//     string dirname  = path.parent_path().string();
//     string filename = path.string();
// #endif
//     Entry::getInstance().getSelf().getLogger().debug("dirname: {}", dirname);
//     Entry::getInstance().getSelf().getLogger().debug("filename: {}", filename);
//
//     try {
//         EngineScope enter(wrapper->mEngine);
//
//         string compiler;
//         if (esm) {
//             compiler = fmt::format(
//                 R"(
//                     import('url').then(url => {{
//                         const moduleUrl = url.pathToFileURL('{1}').href;
//                         import(moduleUrl).catch(error => {{
//                             console.error('Failed to load ESM module:', error);
//                             process.exit(1);
//                         }});
//                     }}).catch(error => {{
//                         console.error('Failed to import url module:', error);
//                         process.exit(1);
//                     }});
//                 )",
//                 dirname,
//                 filename
//             );
//         } else {
//             compiler = fmt::format(
//                 R"(
//                     __dirname = "{0}";
//                     __filename = "{1}";
//                     (function ReplaeRequire() {{
//                         const PublicModule = require('module').Module;
//                         PublicModule._resolveLookupPaths = function (request, parent) {{
//                             result = [parent.path.endsWith("plugins") ? "{0}" : parent.path];
//                             result.push(`${{result[0]}}/node_modules`);
//                             return result;
//                         }};
//                         require = PublicModule.createRequire(`{0}`);
//                     }})();
//                     {2}
//                 )",
//                 dirname,
//                 filename,
//                 js_code.value()
//             );
//         }
//
//         node::SetProcessExitHandler(env, [id{wrapper->mID}](node::Environment* env_, int exit_code) {
//             Entry::getInstance().getSelf().getLogger().debug("Node.js process exit with code: {}", exit_code);
//             NodeManager::getInstance().destroyEngine(id);
//         });
//
//         v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
//         if (loadValue.IsEmpty()) {
//             node::Stop(env);
//             uv_stop(wrapper->mEnvSetup->event_loop());
//             return false;
//         }
//
//         // TODO: uv_run
//         //  EngineScope enter(engine);
//         //  uv_run(eventLoop, UV_RUN_NOWAIT);
//         if (node::SpinEventLoop(env).FromMaybe(1) != 0) {
//             return false;
//         }
//
//         return true;
//     } catch (...) {
//         return false;
//     }
// }
//
//
// std::optional<string> NodeManager::readFileContent(const fs::path& path) {
//     std::ifstream file(path);
//     if (!file.is_open()) {
//         Entry::getInstance().getSelf().getLogger().error("Cannot open file: {}", path.string());
//         return std::nullopt;
//     }
//     string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
//     file.close();
//     return std::move(content);
// }
//
//
// std::optional<string> NodeManager::findMainScript(const fs::path& packagePath) {
//     try {
//         if (!fs::exists(packagePath)) {
//             return std::nullopt;
//         }
//
//         auto content = readFileContent(packagePath);
//         if (!content) {
//             return std::nullopt;
//         }
//
//         auto json = nlohmann::json::parse(*content);
//         return json.value("main", "");
//     } catch (...) {
//         return std::nullopt;
//     }
// }
//
// bool NodeManager::packageHasDependency(const fs::path& packagePath) {
//     try {
//         if (!fs::exists(packagePath)) {
//             return false;
//         }
//
//         auto content = readFileContent(packagePath);
//         if (!content) {
//             return false;
//         }
//
//         auto json = nlohmann::json::parse(*content);
//         return json.contains("dependencies");
//     } catch (...) {
//         return false;
//     }
// }
//
// bool NodeManager::packageIsEsm(const fs::path& packagePath) {
//     try {
//         if (!fs::exists(packagePath)) {
//             return false;
//         }
//
//         auto content = readFileContent(packagePath);
//         if (!content) {
//             return false;
//         }
//
//         auto json = nlohmann::json::parse(*content);
//         return json.contains("type") && json.value("type", "") == "module";
//     } catch (...) {
//         return false;
//     }
// }
//
//
// } // namespace Komomo


#pragma warning(disable : 4996)
#include "NodeManager.h"
#include "API/APIHelper.h"
#include "BindAPI.h"
#include "EngineData.h"
#include "Entry.h"
#include "Utils/Using.h"
#include "Utils/Util.h"
// #include "endstone/scheduler/scheduler.h"
#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "node.h"
#include "uv.h"
#include "v8-cppgc.h"
#include "v8.h"
#include <filesystem>
#include <memory>
#include <thread>
#include <unordered_map>
#include <utility>

#ifdef _WIN32
#include "Windows.h"
#include "shellapi.h"
#else
#include <cstdio>
#endif


namespace Komomo {

#ifdef _WIN32
#pragma comment(lib, "Shell32.lib")
std::string wstr2str(const std::wstring& ws) {
    auto        len = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), ws.size(), nullptr, 0, nullptr, nullptr);
    std::string res(len + 1, 0);
    WideCharToMultiByte(CP_ACP, 0, ws.c_str(), ws.size(), res.data(), len, nullptr, nullptr);
    return res;
}
std::vector<std::string> GetArgs() {
    int                      argc = 0;
    auto                     argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::vector<std::string> res(argc);
    for (int i = 0; i < argc; i++) {
        res[i] = wstr2str(argv[i]);
    }
    LocalFree(argv);
    return res;
}
#else
std::vector<std::string> GetArgs() {
    FILE*                    cmdline = fopen("/proc/self/cmdline", "rb");
    std::vector<std::string> res;
    std::string              t;
    int                      c = fgetc(cmdline);
    while (c != EOF) {
        if (c == 0) {
            if (!t.empty()) res.push_back(t);
            t.clear();
        } else {
            t += c;
        }
        c = fgetc(cmdline);
    }
    fclose(cmdline);
    return res;
}
#endif

NodeManager& NodeManager::getInstance() {
    static NodeManager instance;
    return instance;
}

void NodeManager::initNodeJs() {
    if (mIsInitialized) {
        return;
    }
    static auto args = GetArgs();
    mArgs            = args;

    char* cWorkingDir = args[0].data();
    uv_setup_args(1, &cWorkingDir);
    // cppgc::InitializeProcess();
    auto result = node::InitializeOncePerProcess(
        args,
        node::ProcessInitializationFlags::Flags(
            node::ProcessInitializationFlags::kNoInitializeV8
            | node::ProcessInitializationFlags::kNoInitializeNodeV8Platform
        )
    );
    mExecArgs = result->exec_args();
    if (result->exit_code() != 0) {
        Entry::getInstance().getSelf().getLogger().error("Failed to initialize Node.js: ");
        for (auto const& error : result->errors()) {
            Entry::getInstance().getSelf().getLogger().error(error);
        }
        return;
    }
    mPlatform = node::MultiIsolatePlatform::Create(std::thread::hardware_concurrency());
    v8::V8::InitializePlatform(mPlatform.get());
    v8::V8::Initialize();
    mIsInitialized = true;
}

void NodeManager::shutdownNodeJs() {
    for (auto& [id, wrapper] : mEngines) {
        this->destroyEngine(id);
    }

    v8::V8::Dispose();
    v8::V8::DisposePlatform();
}


bool NodeManager::hasEngine(EngineID id) const { return mEngines.contains(id); }


EngineWrapper* NodeManager::newScriptEngine() {
    static EngineID NextEngineID = 0;
    if (!mIsInitialized) {
        return nullptr;
    }
    EngineID id = NextEngineID++;

    std::vector<string>           errors;
    node::EnvironmentFlags::Flags flags = static_cast<node::EnvironmentFlags::Flags>(
        node::EnvironmentFlags::kNoRegisterESMLoader | node::EnvironmentFlags::kNoCreateInspector
        | node::EnvironmentFlags::kOwnsProcessState
    );

    std::unique_ptr<node::CommonEnvironmentSetup> envSetup =
        node::CommonEnvironmentSetup::Create(mPlatform.get(), &errors, mArgs, mExecArgs, flags);
    if (!envSetup) {
        for (auto const& err : errors)
            Entry::getInstance().getSelf().getLogger().error("Faild to create environment setup: {}", err);
        return nullptr;
    }

    v8::Isolate*       isolate = envSetup->isolate();
    node::Environment* env     = envSetup->env();

    v8::Locker         locker(isolate);
    v8::Isolate::Scope isolateScope(isolate);
    v8::HandleScope    handleScope(isolate);
    v8::Context::Scope contextScope(envSetup->context());

    ScriptEngine* engine = new ScriptEngineImpl({}, isolate, envSetup->context(), false);
    engine->setData(std::make_shared<EngineData>(id)); // 设置引擎数据

    EngineScope scope(engine);
    BindAPI(engine); // 绑定API

    // EngineWrapper warpper;
    mEngines.emplace(id, EngineWrapper{id, engine, std::move(envSetup)});

    node::AddEnvironmentCleanupHook(
        isolate,
        [](void* arg) {
            static_cast<ScriptEngine*>(arg)->destroy();
            Entry::getInstance().getSelf().getLogger().debug("Destroyed engine: {}", arg);
        },
        engine
    );

    return &mEngines[id];
}

EngineWrapper* NodeManager::getEngine(EngineID id) {
    if (mEngines.contains(id)) {
        return &mEngines[id];
    }
    return nullptr;
}


bool NodeManager::destroyEngine(EngineID id) {
    if (!hasEngine(id)) {
        return false;
    }

    auto& wrapper = mEngines[id];

    // ll::.getScheduler().cancelTask(wrapper.mUvLoopTask->getTaskId()); // TODO 取消任务
    wrapper.mEngine->destroy(); // 销毁引擎
    uv_stop(wrapper.mEnvSetup->event_loop());
    node::Stop(wrapper.mEnvSetup->env());

    mEngines.erase(id); // 删除引擎
    return true;
}


bool NodeManager::NpmInstall(string npmExecuteDir) {
    if (!mIsInitialized) {
        return false;
    }

    std::vector<std::string> errors;
    auto                     setup = node::CommonEnvironmentSetup::Create(
        mPlatform.get(),
        &errors,
        mArgs,
        mExecArgs,
        node::EnvironmentFlags::kOwnsProcessState
    );
    if (!setup) {
        for (const std::string& err : errors)
            Entry::getInstance().getSelf().getLogger().error("CommonEnvironmentSetup Error: {}", err.c_str());
        return false;
    }
    npmExecuteDir = ReplaceStr(npmExecuteDir, "\\", "/");

    v8::Isolate*       isolate = setup->isolate();
    node::Environment* env     = setup->env();

    v8::Locker         locker(isolate);
    v8::Isolate::Scope isolate_scope(isolate);
    v8::HandleScope    handle_scope(isolate);
    v8::Context::Scope context_scope(setup->context());

    Entry::getInstance().getSelf().getLogger().debug("Running npm install in {}", npmExecuteDir);
    // clang-format off
    string compiler = R"(
        try {
            const path = require("path");
            const cwd = path.join(process.cwd());

            let node;
            if (process.platform === "win32") {
                node = path.join(cwd, "node.exe");
            } else {
                node = path.join(cwd, "node");
            }

            const execute_dir = path.join(")"+npmExecuteDir+R"(");
            const npm_cli = path.join(cwd, "plugins/js_engine/node_modules/npm/bin/npm-cli.js");
            require("child_process").execFileSync(node, [npm_cli, "install"], { cwd: execute_dir });

            console.log("npm install success");
        } catch (e) {
            console.error(`Failed to run npm install:\n${e.stack}`);
        }
    )";
    // clang-format on

    bool success = false;
    try {
        node::SetProcessExitHandler(env, [&](node::Environment* env_, int exit_code) { node::Stop(env); });
        v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
        if (loadValue.IsEmpty()) {
            throw std::runtime_error("Failed to load environment");
        }
        success = node::SpinEventLoop(env).FromMaybe(1) == 0;
    } catch (...) {
        Entry::getInstance().getSelf().getLogger().error("Failed to run npm install");
    }

    node::Stop(env);
    return success;
}


bool NodeManager::loadFile(EngineWrapper* wrapper, fs::path const& path, bool esm) {
    if (!wrapper) {
        return false;
    }

    auto* env     = wrapper->mEnvSetup->env();
    auto* isolate = wrapper->mEnvSetup->isolate();

    auto js_code = readFileContent(path);
    if (!js_code) {
        return false;
    }

#if defined(WIN32) || defined(_WIN32)
    string dirname  = ReplaceStr(path.parent_path().string(), "\\", "\\\\");
    string filename = ReplaceStr(path.string(), "\\", "\\\\");
#elif defined(__linux__)
    string dirname  = path.parent_path().string();
    string filename = path.string();
#endif
    Entry::getInstance().getSelf().getLogger().debug("dirname: {}", dirname);
    Entry::getInstance().getSelf().getLogger().debug("filename: {}", filename);

    try {
        EngineScope enter(wrapper->mEngine);

        string compiler;
        if (esm) {
            compiler = fmt::format(
                R"(
                    import('url').then(url => {{
                        const moduleUrl = url.pathToFileURL('{1}').href;
                        import(moduleUrl).catch(error => {{
                            console.error('Failed to load ESM module:', error);
                            process.exit(1);
                        }});
                    }}).catch(error => {{
                        console.error('Failed to import url module:', error);
                        process.exit(1);
                    }});
                )",
                dirname,
                filename
            );
        } else {
            compiler = fmt::format(
                R"(
                    const __Path = require("path");
                    const __PluginPath = __Path.join("{0}");
                    const __PluginNodeModulesPath = __Path.join(__PluginPath, "node_modules");

                    __dirname = __PluginPath;
                    __filename = "{1}";
                    (function ReplaeRequire() {{
                        const PublicModule = require('module').Module;
                        const OriginalResolveLookupPaths = PublicModule._resolveLookupPaths;
                        PublicModule._resolveLookupPaths = function (request, parent) {{
                            let result = OriginalResolveLookupPaths.call(this, request, parent);
                            if (Array.isArray(result)) {{
                                result.push(__PluginNodeModulesPath);
                                result.push(__PluginPath);
                            }}
                            return result;
                        }};
                        require = PublicModule.createRequire(__PluginPath);
                    }})();
                    {2}
                )",
                dirname,
                filename,
                js_code.value()
            );
        }

        node::SetProcessExitHandler(env, [id{wrapper->mID}](node::Environment* env_, int exit_code) {
            Entry::getInstance().getSelf().getLogger().debug(
                "Node.js process exit with code: {}, id: {}",
                exit_code,
                id
            );
            NodeManager::getInstance().destroyEngine(id);
        });

        v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
        if (loadValue.IsEmpty()) {
            NodeManager::getInstance().destroyEngine(wrapper->mID);
            return false;
        }

        if (node::SpinEventLoop(env).FromMaybe(1) != 0) {
            NodeManager::getInstance().destroyEngine(wrapper->mID);
            return false;
        }

        // wrapper->mUvLoopTask = Entry::getInstance()->getServer().getScheduler().runTaskTimer(
        //     *Entry::getInstance(),
        //     [loop{wrapper->mEnvSetup->event_loop()}]() { uv_run(loop, UV_RUN_NOWAIT); },
        //     0,
        //     2
        // ); // TODO: fix uv_run

        return true;
    } catch (...) {
        return false;
    }
}


std::optional<string> NodeManager::readFileContent(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        Entry::getInstance().getSelf().getLogger().error("Cannot open file: {}", path.string());
        return std::nullopt;
    }
    string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return std::move(content);
}


std::optional<string> NodeManager::findMainScript(const fs::path& packagePath) {
    try {
        if (!fs::exists(packagePath)) {
            return std::nullopt;
        }

        auto content = readFileContent(packagePath);
        if (!content) {
            return std::nullopt;
        }

        auto json = nlohmann::json::parse(*content);
        return json.value("main", "");
    } catch (...) {
        return std::nullopt;
    }
}

bool NodeManager::packageHasDependency(const fs::path& packagePath) {
    try {
        if (!fs::exists(packagePath)) {
            return false;
        }

        auto content = readFileContent(packagePath);
        if (!content) {
            return false;
        }

        auto json = nlohmann::json::parse(*content);
        return json.contains("dependencies");
    } catch (...) {
        return false;
    }
}

bool NodeManager::packageIsEsm(const fs::path& packagePath) {
    try {
        if (!fs::exists(packagePath)) {
            return false;
        }

        auto content = readFileContent(packagePath);
        if (!content) {
            return false;
        }

        auto json = nlohmann::json::parse(*content);
        return json.contains("type") && json.value("type", "") == "module";
    } catch (...) {
        return false;
    }
}


} // namespace Komomo