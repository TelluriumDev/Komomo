#include "API/Form/ModalForm.h"
#include "API/APIHelper.h"
#include "API/Player/Player.h"
#include "Utils/Convert.h"


using namespace Komomo;

ClassDefine<ModalFormClass> modalFormClassBuilder =
    defineClass<ModalFormClass>("ModalForm")
        .constructor(nullptr)

        .instanceFunction("setTitle", &ModalFormClass::setTitle)
        .instanceFunction("setContent", &ModalFormClass::setContent)
        .instanceFunction("setUpperButton", &ModalFormClass::setUpperButton)
        .instanceFunction("appendButton", &ModalFormClass::setLowerButton)
        .instanceFunction("sendTo", &ModalFormClass::sendTo)

        .build();


ModalFormClass::ModalFormClass(std::string title, std::string content, std::string upperButton, std::string lowerButton)
: ScriptClass(ConstructFromCpp<ModalFormClass>{}) {
    this->form = new ll::form::ModalForm(title, content, upperButton, lowerButton);
}

ModalFormClass::~ModalFormClass() { delete form; }

Local<Object>
ModalFormClass::newModalForm(std::string title, std::string content, std::string upperButton, std::string lowerButton) {
    return (new ModalFormClass(title, content, upperButton, lowerButton))->getScriptObject();
}

Local<Value> ModalFormClass::setTitle(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        form->setTitle(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> ModalFormClass::setContent(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);
    try {
        form->setContent(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> ModalFormClass::setUpperButton(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        form->setUpperButton(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> ModalFormClass::setLowerButton(const Arguments& args) {
    CheckArgsCount(args, 1);
    CheckArgType(args[0], ValueKind::kString);

    try {
        form->setLowerButton(args[0].asString().toString());
        return this->getScriptObject();
    }
    Catch;
}

Local<Value> ModalFormClass::sendTo(const Arguments& args) {
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
                *playerClass->get(),
                [&engine,
                 callback{script::Global(args[1].asFunction())
                 }](Player& player, ll::form::ModalFormResult modalFormResult, ll::form::FormCancelReason reason) {
                    try {
                        EngineScope scope(engine);
                        if (reason.has_value()) {
                            callback.get().call({}, PlayerClass::newPlayer(&player), ConvertToScriptX(reason.value()));
                        } else {
                            callback.get()
                                .call({}, PlayerClass::newPlayer(&player), ConvertToScriptX(modalFormResult.value()));
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
            form->sendTo(*playerClass->get());
            return Boolean::newBoolean(true);
        }
    }
    CatchReturn(Boolean::newBoolean(false));
}
