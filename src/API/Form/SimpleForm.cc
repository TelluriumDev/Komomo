#include "API/Form/SimpleForm.h"
#include "API/APIHelper.h"
#include "API/Player/Player.h"
#include "Utils/Convert.h"


using namespace Komomo;

ClassDefine<SimpleFormClass> simpleFormClassBuilder =
    defineClass<SimpleFormClass>("SimpleForm")
        .constructor(&SimpleFormClass::newForm)

        .instanceFunction("setTitle", &SimpleFormClass::setTitle)
        .instanceFunction("setContent", &SimpleFormClass::setContent)
        .instanceFunction("appendButton", &SimpleFormClass::appendButton)
        .instanceFunction("sendTo", &SimpleFormClass::sendTo)

        .build();

SimpleFormClass::SimpleFormClass(ll::form::SimpleForm* form) : ScriptClass(ConstructFromCpp<SimpleFormClass>{}) {
    this->form = form;
}

SimpleFormClass::SimpleFormClass(std::string const& title, std::string const& content)
: ScriptClass(ConstructFromCpp<SimpleFormClass>{}) {
    this->form = new ll::form::SimpleForm(title, content);
}

SimpleFormClass::~SimpleFormClass() { delete form; }

SimpleFormClass* SimpleFormClass::newForm(const Arguments& args) {
    CheckArgsCountReturn(args, 2, nullptr);
    CheckArgTypeReturn(args[0], ValueKind::kString, nullptr);
    CheckArgTypeReturn(args[1], ValueKind::kString, nullptr);

    try {
        return new SimpleFormClass(args[0].asString().toString(), args[1].asString().toString());
    }
    CatchReturn(nullptr);
}

Local<Value> SimpleFormClass::setTitle(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        form->setTitle(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> SimpleFormClass::setContent(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        form->setContent(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> SimpleFormClass::appendButton(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);

    try {
        if (args.size() >= 4) {
            CheckArgType(args[1], ValueKind::kString);
            CheckArgType(args[2], ValueKind::kString);
            CheckArgType(args[3], ValueKind::kFunction);

            form->appendButton(
                args[1].asString().toString(),
                args[2].asString().toString(),
                args[3].asString().toString(),
                [engine{EngineScope::currentEngine()}, callback{script::Global(args[3].asFunction())}](Player& player) {
                    EngineScope scope(engine);
                    try {
                        Local<Value> result = callback.get().call({}, PlayerClass::newPlayer(&player));
                    }
                    Catch;
                    return Local<Value>();
                }
            );
        } else {
            CheckArgType(args[1], ValueKind::kFunction);
            form->appendButton(
                args[0].asString().toString(),
                [engine{EngineScope::currentEngine()}, callback{script::Global(args[1].asFunction())}](Player& player) {
                    EngineScope scope(engine);
                    try {
                        Local<Value> result = callback.get().call({}, PlayerClass::newPlayer(&player));
                    }
                    Catch;
                    return Local<Value>();
                }
            );
        }
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> SimpleFormClass::sendTo(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!IsInstanceOf<PlayerClass>(args[0])) {
            PrintWrongArgType();
            return Boolean::newBoolean(false);
        };
        if (args.size() >= 2) {
            CheckArgType(args[1], ValueKind::kFunction);
            auto engine      = EngineScope::currentEngine();
            auto playerClass = engine->getNativeInstance<PlayerClass>(args[0]);
            form->sendTo(
                *playerClass->mPlayer,
                [&engine,
                 callback{script::Global(args[1].asFunction())
                 }](Player& player, int id, ll::form::FormCancelReason reason) {
                    try {
                        EngineScope scope(engine);
                        if (reason.has_value()) {
                            callback.get().call(
                                {},
                                PlayerClass::newPlayer(&player),
                                Number::newNumber(id),
                                ConvertToScriptX(reason.value())
                            );
                        } else {
                            callback.get().call({}, PlayerClass::newPlayer(&player), Number::newNumber(id));
                        }
                    }
                    Catch;
                    return Local<Value>();
                }
            );
            return Boolean::newBoolean(true);
        } else {
            auto engine      = EngineScope::currentEngine();
            auto playerClass = engine->getNativeInstance<PlayerClass>(args[0]);
            form->sendTo(*playerClass->mPlayer);
            return Boolean::newBoolean(true);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
}
