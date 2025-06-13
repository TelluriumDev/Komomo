add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("iceblcokmc https://github.com/IceBlcokMC/xmake-repo.git")
add_repositories("miracleforest https://github.com/MiracleForest/xmake-repo")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires("nodejs 22.12.0") -- iceblockmc
add_requires("levilamina 1.1.0", {configs = {target_type = "server"}})
add_requires("levibuildscript 0.3.0")
add_requires(
    "microsoft-gsl 4.0.0",
    "ilistenattentively 0.4.0",
    "demangler"
    -- "uwebsockets"
)
add_requires("gmlib")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("Komomo")
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_AMD64_",
        "KMM_EXPORT"
    )
    add_files("src/**.cc")
    add_includedirs("src")
    add_packages("nodejs")
    add_packages(
        "levilamina",
        "fmt",
        "expected-lite",
        "entt",
        "microsoft-gsl",
        "nlohmann_json",
        "glm",
        "concurrentqueue",
        "magic_enum",
        "ilistenattentively",
        "gmlib",
        "demangler"
        -- "uwebsockets"
    )
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    -- set_exceptions("none")
    set_optimize("fastest")
    add_cxxflags(
            "/EHs",
            "/utf-8",
            "/WX",
            "/sdl"
        )

    -- ScriptX
    add_includedirs("ScriptX/src/include")
    add_files(
        "ScriptX/src/**.cc",
        "ScriptX/backend/V8/**.cc"
    )
    add_defines(
        "SCRIPTX_BACKEND_V8",
        "SCRIPTX_BACKEND_TRAIT_PREFIX=../ScriptX/backend/V8/trait/Trait"
    )

    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")

    if is_mode("debug") then
        add_defines("DEBUG")
    end
