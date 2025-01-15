add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("iceblcokmc https://github.com/IceBlcokMC/xmake-repo.git")

add_requires("nodejs 22.12.0") -- iceblockmc
add_requires("levilamina 1.0.0-rc.3", {configs = {target_type = "server"}})
add_requires("levibuildscript 0.2.0")
add_requires(
    "microsoft-gsl 4.0.0",
    "boost 1.85.0"
)

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("Komomo")
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_AMD64_"
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
        "boost",
        "glm",
        "concurrentqueue",
        "magic_enum"
    )
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    -- set_exceptions("none")
    add_cxxflags("/Zc:__cplusplus")
    add_cxflags(
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

    -- add_links("third-party/nodejs/win/lib/libnode.lib"

    if is_mode("debug") then
        add_defines("DEBUG")
    end

    set_basename("Komomo")
    -- after_build(function(target)end)
