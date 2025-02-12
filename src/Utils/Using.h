#pragma once

#include <ScriptX/ScriptX.h>

using script::Arguments;
using script::Array;
using script::Boolean;
using script::ByteBuffer;
using script::ClassDefine;
using script::defineClass;
using script::EngineScope;
// using script::Exception;
using script::ExitEngineScope;
using script::Function;
using script::Global;
using script::Local;
using script::Number;
using script::Object;
using script::ScriptClass;
using script::ScriptEngine;
using script::ScriptEngineImpl;
using script::selectOverloadedFunc;
using script::String;
using script::Unsupported;
using script::Value;
using script::ValueKind;

// stl
#include <filesystem> // IWYU pragma: keep
#include <string>

using string   = std::string;
namespace fs   = std::filesystem;
using EngineID = uint64_t;