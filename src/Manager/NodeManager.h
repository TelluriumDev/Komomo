#pragma once

#include "Utils/Using.h"

#include <node.h>

#include <filesystem>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>


namespace Komomo {


struct EngineWrapper {
    EngineID                                      mID; // 引擎ID
    ScriptEngine*                                 mEngine;
    std::unique_ptr<node::CommonEnvironmentSetup> mEnvSetup;
    bool                                          mIsRunning{false};
    bool                                          mIsDestroying{false};

public:
    EngineWrapper() = default;
    EngineWrapper(EngineID id, ScriptEngine* engine, std::unique_ptr<node::CommonEnvironmentSetup> envs)
    : mID(id),
      mEngine(engine),
      mEnvSetup(std::move(envs)) {}

    operator ScriptEngine*() const { return mEngine; }
};

using EngineWrapperPtr = std::unique_ptr<EngineWrapper>;

class NodeManager final {
private:
    NodeManager()                              = default;
    NodeManager(const NodeManager&)            = delete;
    NodeManager& operator=(const NodeManager&) = delete;

    bool                                           mIsInitialized{false}; // 是否初始化
    std::vector<string>                            mArgs;                 // 参数
    std::vector<string>                            mExecArgs;             // 执行参数
    std::unique_ptr<node::MultiIsolatePlatform>    mPlatform;             // v8 平台
    std::unordered_map<EngineID, EngineWrapperPtr> mEngines;              // 引擎列表

public:
    static NodeManager& getInstance();

    void initNodeJs();

    void shutdownNodeJs();

public:
    bool hasEngine(EngineID id) const;

    EngineWrapper* newScriptEngine();

    EngineWrapper* getEngine(EngineID id);

    bool destroyEngine(EngineID id);

    bool NpmInstall(string npmExecuteDir);

public:
    static bool loadFile(EngineWrapper* wrapper, fs::path const& file, bool esm = false);

    static std::optional<string> readFileContent(const fs::path& file);

    static std::optional<string> findMainScript(const fs::path& packagePath);
    static bool                  packageHasDependency(const fs::path& packagePath);
    static bool                  packageIsEsm(const fs::path& packagePath);
};


} // namespace Komomo
