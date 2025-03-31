#include "API/Logger/Logger.h"

using namespace Komomo;

ClassDefine<LoggerClass> loggerClassBuilder = defineClass<LoggerClass>("Logger")
                                                  .constructor(nullptr)

                                                  .function("getLogger", &LoggerClass::newLogger)
                                                  .instanceFunction("log", &LoggerClass::log)
                                                  .instanceFunction("error", &LoggerClass::error)
                                                  .instanceFunction("warn", &LoggerClass::warn)
                                                  .instanceFunction("info", &LoggerClass::info)
                                                  .instanceFunction("debug", &LoggerClass::debug)
                                                  .instanceFunction("trace", &LoggerClass::trace)
                                                  .instanceFunction("fatal", &LoggerClass::fatal)
                                                  .instanceFunction("setLevel", &LoggerClass::setLevel)

                                                  .build();


LoggerClass::LoggerClass(std::string title) : ScriptClass(ConstructFromCpp<LoggerClass>{}) { this->title = title; }

Local<Object> LoggerClass::newLogger(const Arguments& args) {
    try {
        if (args.size() == 1 && args[0].isString()) {
            return newLoggerClass(args[0].asString().toString());
        }
    }
    CatchNotReturn;
    return newLoggerClass(ENGINE_DATA()->mMod->getName());
}

Local<Object> LoggerClass::newLoggerClass(std::string title) { return (new LoggerClass(title))->getScriptObject(); }

Local<Value> LoggerClass::log(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kNumber);

    try {
        getLogger()->log(ll::io::LogLevel(args[0].asNumber().toInt32()), LogDataHelper(args));
        return Local<Value>();
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::error(const Arguments& args) {
    CheckArgsCount(args, 1);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->error(LogDataHelper(args));
        return Local<Value>();
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::warn(const Arguments& args) {
    CheckArgsCount(args, 1);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->warn(LogDataHelper(args));
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::info(const Arguments& args) {
    CheckArgsCount(args, 1);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->info(LogDataHelper(args));
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::debug(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->debug(LogDataHelper(args));
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::trace(const Arguments& args) {
    CheckArgsCount(args, 1);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->trace(LogDataHelper(args));
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::fatal(const Arguments& args) {
    CheckArgsCount(args, 1);

    try {
        // if (args.size() >= 2) {} // TODO: format
        getLogger()->fatal(LogDataHelper(args));
    }
    CatchNotReturn;
    return Local<Value>();
}

Local<Value> LoggerClass::setLevel(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kNumber);

    try {
        getLogger()->setLevel(ll::io::LogLevel(args[0].asNumber().toInt32()));
    }
    CatchNotReturn;
    return Local<Value>();
}
