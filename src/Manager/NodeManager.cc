#include "Manager/NodeManager.h"
#include "Manager/BindAPI.h"
#include "NodeManager.h"

#include <ll/api/chrono/GameChrono.h>
#include <ll/api/coro/CoroTask.h>
#include <ll/api/service/GamingStatus.h>
#include <ll/api/thread/ServerThreadExecutor.h>

#include <Windows.h>
#include <memory>
#include <shellapi.h>
#include <uv.h>


#pragma warning(disable : 4996)
#pragma comment(lib, "Shell32.lib")

namespace Komomo {
std::string wstr2str(const std::wstring& ws) {
    int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (len <= 0) return "";
    std::vector<char> buffer(len);
    int               ret = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, buffer.data(), len, nullptr, nullptr);
    if (ret != len) return "";
    return std::string(buffer.begin(), buffer.end() - 1);
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
    auto result = node::InitializeOncePerProcess(
        args,
        {node::ProcessInitializationFlags::kNoInitializeV8,
         node::ProcessInitializationFlags::kNoInitializeNodeV8Platform}
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
    node::TearDownOncePerProcess();
}


bool NodeManager::hasEngine(EngineID id) const { return mEngines.contains(id); }


EngineWrapper* NodeManager::newScriptEngine() {
    static EngineID NextEngineID = 0;
    if (!mIsInitialized) {
        return nullptr;
    }
    EngineID id = NextEngineID++;

    std::vector<string>                           errors;
    std::unique_ptr<node::CommonEnvironmentSetup> envSetup = node::CommonEnvironmentSetup::Create(
        mPlatform.get(),
        &errors,
        mArgs,
        mExecArgs,
        node::EnvironmentFlags::Flags(
            node::EnvironmentFlags::kNoRegisterESMLoader | node::EnvironmentFlags::kNoCreateInspector
            | node::EnvironmentFlags::kOwnsProcessState
        )
    );
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
    EngineScope   scope(engine);

    engine->setData(std::make_shared<EngineData>(id));
    BindAPI(engine);

    EngineWrapperPtr ptr = std::make_unique<EngineWrapper>(id, engine, std::move(envSetup));
    mEngines.emplace(id, std::move(ptr));

    node::AddEnvironmentCleanupHook(
        isolate,
        [](void* arg) {
            static_cast<ScriptEngine*>(arg)->destroy();
            Entry::getInstance().getSelf().getLogger().debug("[EnvironmentCleanupHook] Destroyed engine: {}", arg);
        },
        engine
    );

    return mEngines[id].get();
}

EngineWrapper* NodeManager::getEngine(EngineID id) {
    if (mEngines.contains(id)) {
        return mEngines[id].get();
    }
    return nullptr;
}


bool NodeManager::destroyEngine(EngineID id) {
    try {
        if (!hasEngine(id)) {
            return false;
        }

        auto& wrapper = mEngines[id];

        wrapper->mIsRunning    = false;
        wrapper->mIsDestroying = true;

        // Event Loop will stop automatically.
        // uv_stop(wrapper.mEnvSetup->event_loop());

        node::Stop(wrapper->mEnvSetup->env(), node::StopFlags::kDoNotTerminateIsolate);

        // EnvironmentCleanupHook will destroy engine automatically.
        // wrapper.mEngine->destroy();

        mEngines.erase(id);

        return true;
    } catch (...) {
        Entry ::getInstance().getSelf().getLogger().error("Failed to destroy engine: {}", id);
        return false;
    }
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

            global.__dirname = cwd
            let node = path.join(path.join(cwd,")"+Entry::getInstance().getSelf().getModDir().string()+R"("), "node.exe");

            const execute_dir = path.join(")"+npmExecuteDir+R"(");
            const npm_cli = path.join(cwd, "")"+Entry::getInstance().getSelf().getModDir().string()+R"("/npm/bin/npm-cli.js");
            require("child_process").execFileSync(node, [npm_cli, "install"], { cwd: execute_dir });

            console.log("npm install success");
        } catch (e) {
            console.error(`Failed to run npm install:\n${e}`);
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

    auto js_code = readFileContent(path);
    if (!js_code) {
        return false;
    }

    string dirname  = ReplaceStr(path.parent_path().string(), "\\", "\\\\");
    string filename = ReplaceStr(path.string(), "\\", "\\\\");
    Entry::getInstance().getSelf().getLogger().debug("dirname: {}", dirname);
    Entry::getInstance().getSelf().getLogger().debug("filename: {}", filename);

    try {
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
                    const __ModPath = __Path.join("{0}");
                    const __ModNodeModulesPath = __Path.join(__ModPath, "node_modules");

                    __dirname = __ModPath;
                    __filename = "{1}";
                    (function ReplaeRequire() {{
                        const PublicModule = require('module').Module;
                        const OriginalResolveLookupPaths = PublicModule._resolveLookupPaths;
                        PublicModule._resolveLookupPaths = function (request, parent) {{
                            let result = OriginalResolveLookupPaths.call(this, request, parent);
                            if (Array.isArray(result)) {{
                                result.push(__ModNodeModulesPath);
                                result.push(__ModPath);
                            }}
                            return result;
                        }};
                        require = PublicModule.createRequire(__ModPath);
                    }})();
                    {2}
                )",
                dirname,
                filename,
                js_code.value()
            );
        }

        auto* env     = wrapper->mEnvSetup->env();
        auto* isolate = wrapper->mEnvSetup->isolate();

        {
            EngineScope enter(wrapper->mEngine);
            node::SetProcessExitHandler(env, [id{wrapper->mID}, isolate](node::Environment*, int exit_code) {
                isolate->Exit();
                Entry::getInstance().getSelf().getLogger().debug(
                    "Node.js process exit with code: {}, id: {}",
                    exit_code,
                    id
                );
                if (exit_code == 0) NodeManager::getInstance().destroyEngine(id);
            });
        }

        {
            EngineScope               enter(wrapper->mEngine);
            v8::TryCatch              vtry(isolate);
            v8::MaybeLocal<v8::Value> loadValue = node::LoadEnvironment(env, compiler.c_str());
            if (loadValue.IsEmpty() || vtry.HasCaught()) {
                v8::String::Utf8Value error(isolate, vtry.Exception());
                v8::String::Utf8Value stack(isolate, vtry.StackTrace(wrapper->mEnvSetup->context()).ToLocalChecked());
                Entry::getInstance().getSelf().getLogger().error("{}\n{}", *error, *stack);
                // ExitEngineScope exit;
                // isolate->Exit();
                return false;
            }
        }

        wrapper->mIsRunning = true;

        ll::coro::keepThis([wrapper]() -> ll::coro::CoroTask<> {
            while (true) {
                co_await ll::chrono::ticks(2);

                auto status = ll::getGamingStatus();
                if (status == ll::GamingStatus::Stopping || !wrapper->mIsRunning || wrapper->mIsDestroying) {
                    co_return;
                }

                if (status != ll::GamingStatus::Running) {
                    continue;
                }

                EngineScope enter(wrapper->mEngine);
                try {
                    uv_run(wrapper->mEnvSetup->event_loop(), UV_RUN_NOWAIT);
                }
                CatchNotReturn;
            }
        }).launch(ll::thread::ServerThreadExecutor::getDefault());

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