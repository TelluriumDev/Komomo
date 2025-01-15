#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/io/LogLevel.h>
#include <ll/api/io/Logger.h>
#include <ll/api/io/LoggerRegistry.h>
#include <string>


class LoggerClass : public ScriptClass {

private:
    std::string title;

    std::shared_ptr<ll::io::Logger> getLogger() {
        auto logger = ll::io::LoggerRegistry::getInstance().tryGet(title);
        if (!logger) {
            logger = ll::io::LoggerRegistry::getInstance().getOrCreate(title);
        }
        return logger;
    };

public:
    LoggerClass(std::string title);

public:
    static Local<Object> newLoggerClass(std::string title);

    static Local<Object> newLogger(const Arguments& args);

    Local<Value> init(const Arguments& args);

    Local<Value> log(const Arguments& args);

    Local<Value> fatal(const Arguments& args);

    Local<Value> error(const Arguments& args);

    Local<Value> warn(const Arguments& args);

    Local<Value> info(const Arguments& args);

    Local<Value> debug(const Arguments& args);

    Local<Value> trace(const Arguments& args);

    // LLAPI void setLevel(LogLevel level);
    Local<Value> setLevel(const Arguments& args);

    // LLAPI void setFlushLevel(LogLevel level);
    // Local<Value> setFlushLevel(const Arguments& args);

    // LLAPI void setFormatter(Polymorphic<Formatter> formatter);
    // Local<Value> setFormatter(const Arguments& args);

    // LLAPI void flush() const;
    // Local<Value> flush(const Arguments& args);

    // LLAPI void clearSink() const;
    // Local<Value> clearSink(const Arguments& args);

    // LLAPI size_t addSink(std::shared_ptr<SinkBase> sink) const;
    // Local<Value> addSink(const Arguments& args);

    // LLAPI std::shared_ptr<SinkBase> getSink(size_t index) const;
    // Local<Value> getSink(const Arguments& args);

    // LLNDAPI coro::Generator<SinkBase&> sinks() const;
    // Local<Value> sinks(const Arguments& args);
};

extern ClassDefine<LoggerClass> loggerClassBuilder;