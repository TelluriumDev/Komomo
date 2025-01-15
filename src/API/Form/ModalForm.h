#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/form/FormBase.h>
#include <ll/api/form/ModalForm.h>


class ModalFormClass : public ScriptClass {
private:
    ll::form::ModalForm* form;

public:
    ModalFormClass(std::string title, std::string content, std::string upperButton, std::string lowerButton);

    ~ModalFormClass();

    static Local<Object>
    newModalForm(std::string title, std::string content, std::string upperButton, std::string lowerButton);
    // LLAPI ModalForm& setTitle(std::string const& title);
    Local<Value> setTitle(const Arguments& args);

    // LLAPI ModalForm& setContent(std::string const& content);
    Local<Value> setContent(const Arguments& args);

    // LLAPI ModalForm& setUpperButton(std::string const& upperButton);
    Local<Value> setUpperButton(const Arguments& args);

    // LLAPI ModalForm& setLowerButton(std::string const& lowerButton);
    Local<Value> setLowerButton(const Arguments& args);

    // LLAPI ModalForm& sendTo(Player& player, Callback callback = Callback());
    Local<Value> sendTo(const Arguments& args);
};

extern ClassDefine<ModalFormClass> modalFormClassBuilder;