#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <ll/api/form/CustomForm.h>
#include <ll/api/form/FormBase.h>

#include <string>

class CustomFormClass : public ScriptClass {
private:
    ll::form::CustomForm* form;

public:
    CustomFormClass(std::string const& title);

    // ~CustomFormClass();

    static Local<Object> newCustomForm(std::string title);
    // LLAPI CustomForm& setTitle(std::string const& title);
    Local<Value> setTitle(const Arguments& args);

    // LLAPI CustomForm& appendLabel(std::string const& text);
    Local<Value> appendLabel(const Arguments& args);

    // LLAPI CustomForm& appendInput(
    //     std::string const& name,
    //     std::string const& text,
    //     std::string const& placeholder = {},
    //     std::string const& defaultVal  = {}
    // );
    Local<Value> appendInput(const Arguments& args);

    // LLAPI CustomForm& appendToggle(std::string const& name, std::string const& text, bool defaultVal = false);
    Local<Value> appendToggle(const Arguments& args);

    // LLAPI CustomForm& appendDropdown(
    //     std::string const&              name,
    //     std::string const&              text,
    //     std::vector<std::string> const& options,
    //     size_t                          defaultVal = 0
    // );
    Local<Value> appendDropdown(const Arguments& args);

    // LLAPI CustomForm& appendSlider(
    //     std::string const& name,
    //     std::string const& text,
    //     double             min,
    //     double             max,
    //     double             step       = 0.0,
    //     double             defaultVal = 0.0
    // );
    Local<Value> appendSlider(const Arguments& args);

    // LLAPI CustomForm& appendStepSlider(
    //     std::string const&              name,
    //     std::string const&              text,
    //     std::vector<std::string> const& steps,
    //     size_t                          defaultVal = 0
    // );
    Local<Value> appendStepSlider(const Arguments& args);

    // LLAPI CustomForm& sendTo(Player& player, Callback callback = Callback());
    Local<Value> sendTo(const Arguments& args);
};

extern ClassDefine<CustomFormClass> customFormClassBuilder;