#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/form/FormBase.h>
#include <ll/api/form/SimpleForm.h>


class SimpleFormClass : public ScriptClass {
private:
    ll::form::SimpleForm* form;

public:
    SimpleFormClass(std::string title, std::string content = {});

    ~SimpleFormClass();

    static Local<Object> newSimpleForm(std::string title, std::string content = {});
    // LLAPI SimpleForm& setTitle(std::string const& title);
    Local<Value> setTitle(const Arguments& args);

    // LLAPI SimpleForm& setContent(std::string const& content);
    Local<Value> setContent(const Arguments& args);

    // LLAPI SimpleForm& appendButton(
    //     std::string const& text,
    //     std::string const& imageData,
    //     std::string const& imageType,
    //     ButtonCallback     callback = {}
    // );
    // LLAPI SimpleForm& appendButton(std::string const& text, ButtonCallback callback = {});
    Local<Value> appendButton(const Arguments& args);

    // LLAPI SimpleForm& sendTo(Player& player, Callback callback = Callback());
    Local<Value> sendTo(const Arguments& args);
};

extern ClassDefine<SimpleFormClass> simpleFormClassBuilder;