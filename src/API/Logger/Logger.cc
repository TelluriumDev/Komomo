#include "API/Logger/Logger.h"
#include "Utils/Convert.h"
#include "ll/api/io/Logger.h"
#include "ll/api/io/LoggerRegistry.h"
#include <memory>

using namespace Komomo;

ClassDefine<LoggerClass> loggerClassBuilder = defineClass<LoggerClass>("Logger")
                                                  .constructor(&LoggerClass::newLogger)

                                                  .instanceFunction("log", &LoggerClass::log)
                                                  .instanceFunction("error", &LoggerClass::error)
                                                  .instanceFunction("warn", &LoggerClass::warn)
                                                  .instanceFunction("info", &LoggerClass::info)
                                                  .instanceFunction("debug", &LoggerClass::debug)
                                                  .instanceFunction("trace", &LoggerClass::trace)
                                                  .instanceFunction("fatal", &LoggerClass::fatal)

                                                  .build();


LoggerClass::LoggerClass(std::string title) : ScriptClass(ConstructFromCpp<LoggerClass>{}) { this->title = title; }

LoggerClass* LoggerClass::newLogger(const Arguments& args) {
    CheckArgsCountReturn(args, 1, nullptr);
    CheckArgTypeReturn(args[0], ValueKind::kString, nullptr);
    try {
        return new LoggerClass(args[0].asString().toString());
    }
    CatchReturn(nullptr);
}

Local<Value> LoggerClass::log(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);
    CheckArgType(args[1], ValueKind::kString);

    try {
        getLogger()->log(ConvertFromScriptX<ll::io::LogLevel>(args[0]), args[1].asString().toString());
        return Local<Value>();
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::error(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->error(args[0].asString().toString());
        return Local<Value>();
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::warn(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->warn(args[0].asString().toString());
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::info(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->info(args[0].asString().toString());
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::debug(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->debug(args[0].asString().toString());
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::trace(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->trace(args[0].asString().toString());
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::fatal(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->fatal(args[0].asString().toString());
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::setLevel(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);

    try {
        getLogger()->setLevel(ConvertFromScriptX<ll::io::LogLevel>(args[0]));
    }
    CatchNotReturn;
    return Local<Value>();
}