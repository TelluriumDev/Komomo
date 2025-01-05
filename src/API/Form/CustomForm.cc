#include "API/Form/CustomForm.h"
#include "API/APIHelper.h"
#include "API/Player/Player.h"
#include "Utils/Convert.h"
#include "Utils/Using.h"
#include <any>
#include <unordered_map>

using namespace Komomo;

ClassDefine<CustomFormClass> customFormClassBuilder =
    defineClass<CustomFormClass>("CustomForm")
        .constructor(&CustomFormClass::newForm)


        .instanceFunction("setTitle", &CustomFormClass::setTitle)
        .instanceFunction("appendLabel", &CustomFormClass::appendLabel)
        .instanceFunction("appendInput", &CustomFormClass::appendInput)
        .instanceFunction("appendToggle", &CustomFormClass::appendToggle)
        .instanceFunction("appendDropdown", &CustomFormClass::appendDropdown)
        .instanceFunction("appendSlider", &CustomFormClass::appendSlider)
        .instanceFunction("appendStepSlider", &CustomFormClass::appendStepSlider)
        .instanceFunction("appendColorPicker", &CustomFormClass::sendTo)


        .build();

CustomFormClass::CustomFormClass(ll::form::CustomForm* form) : ScriptClass(ConstructFromCpp<CustomFormClass>{}) {
    this->form = form;
}

CustomFormClass::CustomFormClass(std::string const& title) : ScriptClass(ConstructFromCpp<CustomFormClass>{}) {
    this->form = new ll::form::CustomForm(title);
}

CustomFormClass::~CustomFormClass() { delete form; }

CustomFormClass* CustomFormClass::newForm(const Arguments& args) {
    CheckArgsCountReturn(args, 1, nullptr);
    CheckArgTypeReturn(args[0], ValueKind::kString, nullptr);

    try {
        return new CustomFormClass(args[0].asString().toString());
    }
    CatchReturn(nullptr);
}

Local<Value> CustomFormClass::setTitle(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        form->setTitle(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
};

Local<Value> CustomFormClass::appendLabel(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);

    try {
        form->appendLabel(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
};

Local<Value> CustomFormClass::appendInput(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);

    try {
        if (args.size() >= 4) {
            CheckArgType(args[2], ValueKind::kString);
            CheckArgType(args[3], ValueKind::kString);

            form->appendInput(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asString().toString(),
                args[3].asString().toString()
            );
        } else if (args.size() == 3) {
            CheckArgType(args[2], ValueKind::kString);

            form->appendInput(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asString().toString()
            );
        } else {
            form->appendInput(args[0].asString().toString(), args[1].asString().toString());
        }
        elements.push_back(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> CustomFormClass::appendToggle(const Arguments& args) {
    CheckArgsCount(args, 2);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);

    try {
        if (args.size() >= 3) {
            CheckArgType(args[2], ValueKind::kBoolean);

            form->appendToggle(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asBoolean().value()
            );
        } else {

            form->appendToggle(args[0].asString().toString(), args[1].asString().toString());
        }
        elements.push_back(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> CustomFormClass::appendDropdown(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    CheckArgType(args[2], ValueKind::kArray);

    std::vector<std::string> options;
    for (int i = 0; i < args[2].asArray().size(); i++) {
        CheckArgType(args[2].asArray().get(i), ValueKind::kString);
        options.push_back(args[2].asArray().get(i).asString().toString());
    }

    try {
        if (args.size() >= 4) {
            CheckArgType(args[3], ValueKind::kNumber);
            form->appendDropdown(
                args[0].asString().toString(),
                args[1].asString().toString(),
                options,
                args[3].asNumber().toInt32()
            );
        } else {
            form->appendDropdown(args[0].asString().toString(), args[1].asString().toString(), options);
        }
        elements.push_back(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> CustomFormClass::appendSlider(const Arguments& args) {
    CheckArgsCount(args, 4);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    CheckArgType(args[2], ValueKind::kNumber);
    CheckArgType(args[3], ValueKind::kNumber);

    try {
        if (args.size() >= 6) {
            CheckArgType(args[4], ValueKind::kNumber);
            CheckArgType(args[5], ValueKind::kNumber);
            form->appendSlider(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asNumber().toInt64(),
                args[3].asNumber().toInt64(),
                args[4].asNumber().toInt64(),
                args[5].asNumber().toInt64()
            );
        } else if (args.size() == 5) {
            CheckArgType(args[4], ValueKind::kNumber);
            form->appendSlider(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asNumber().toInt64(),
                args[3].asNumber().toInt64(),
                args[4].asNumber().toInt64()
            );
        } else {
            form->appendSlider(
                args[0].asString().toString(),
                args[1].asString().toString(),
                args[2].asNumber().toInt64(),
                args[3].asNumber().toInt64()
            );
        }
        elements.push_back(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> CustomFormClass::appendStepSlider(const Arguments& args) {
    CheckArgsCount(args, 3);
    CheckArgType(args[0], ValueKind::kString);
    CheckArgType(args[1], ValueKind::kString);
    CheckArgType(args[2], ValueKind::kArray);

    std::vector<std::string> options;
    for (int i = 0; i < args[2].asArray().size(); i++) {
        CheckArgType(args[2].asArray().get(i), ValueKind::kString);
        options.push_back(args[2].asArray().get(i).asString().toString());
    }

    try {
        if (args.size() >= 4) {
            CheckArgType(args[3], ValueKind::kNumber);
            form->appendStepSlider(
                args[0].asString().toString(),
                args[1].asString().toString(),
                options,
                args[3].asNumber().toInt64()
            );
        } else {
            form->appendStepSlider(args[0].asString().toString(), args[1].asString().toString(), options);
        }
        elements.push_back(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> CustomFormClass::sendTo(const Arguments& args) {
    CheckArgsCount(args, 1);
    try {
        if (!IsInstanceOf<PlayerClass>(args[0])) return Boolean::newBoolean(false);
        if (args.size() >= 2) {
            CheckArgType(args[1], ValueKind::kFunction);
            auto engine      = EngineScope::currentEngine();
            auto playerClass = engine->getNativeInstance<PlayerClass>(args[0]);
            form->sendTo(
                *playerClass->mPlayer,
                [e{EngineScope::currentEngine()}, callback{script::Global(args[1].asFunction())}, this](
                    Player&                           player,
                    ll::form::CustomFormResult const& customFormResult,
                    ll::form::FormCancelReason        reason
                ) {
                    try {
                        EngineScope scope(e);
                        // TODO: Implement CustomFormResult
                        callback.get().call({}, PlayerClass::newPlayer(&player), ConvertToScriptX(reason.value()));
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
    Catch(Boolean::newBoolean(false));
}